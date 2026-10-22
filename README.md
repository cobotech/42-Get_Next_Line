*This project has been created as part of the 42 curriculum by ykomori.*

# get_next_line

## Description

`get_next_line` は、ファイルディスクリプタから **1行ずつ** 読み込む C の関数です。

```c
char	*get_next_line(int fd);
```

呼ぶたびに `fd` から次の1行を返します。返す行には末尾の `\n` を含みます(ただし、ファイルが `\n` で終わらない場合の最後の行は除きます)。もう読むものがないとき、またはエラーが起きたときは `NULL` を返します。

この課題の目的は、C の **static 変数** の仕組みを学ぶことです。`read()` は一度に決まったバイト数(`BUFFER_SIZE`)しか返さないので、関数は呼び出しと呼び出しの間で「どこまで読んだか」を覚えておく必要があります。

通常のファイルだけでなく、標準入力(`fd = 0`)からも読めます。

## Instructions

### ファイル構成

| ファイル | 中身 |
|---|---|
| `get_next_line.c` | `get_next_line` 本体と、処理を3つに分けた補助関数 |
| `get_next_line_utils.c` | 文字列の補助関数:`gnl_strlen`、`gnl_find_newline`、`gnl_strjoin`、`gnl_substr` |
| `get_next_line.h` | プロトタイプと、`BUFFER_SIZE` のデフォルト値(42) |

### コンパイル

ファイルを開いて `get_next_line` をくり返し呼ぶ `main.c` を用意し、次のようにコンパイルします。

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` には 1 以上の任意の値を指定できます(1、4、42、9999、10000000 で動作確認済み)。`-D BUFFER_SIZE` を省略した場合は、ヘッダのデフォルト値が使われます。

### 使用例

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

返される行はすべて `malloc` で確保されているので、呼び出し側で `free` する必要があります。

## Algorithm

### 考え方

`read()` は行の終わりで止まってくれません。最大 `BUFFER_SIZE` バイトを返すので、`\n` の **先まで** 読んでしまうことがよくあります。その余った部分は次の行の一部なので、捨てるわけにはいきません。

そこで、余りを **static** なポインタ `leftover`(あまり)に取っておきます。static をつけたローカル変数は、関数が終わっても値が残ります。そのため、次の `get_next_line` の呼び出しは、前回の余りの続きから始められます。

### 1回の呼び出しの流れ

```
get_next_line(fd)
 1. read_to_leftover : leftover に '\n' がない間、BUFFER_SIZE バイトを
                       chunk に読み込み、leftover の後ろにくっつける
 2. extract_line     : leftover の先頭から '\n' まで('\n' を含む)を
                       コピーする('\n' がなければ最後まで)→ これを返す
 3. update_leftover  : '\n' より後ろだけを新しい leftover にする
                       (古い leftover は free。何も残らなければ NULL)
```

`BUFFER_SIZE = 4` で、ファイル `"ab\ncd\nef"` を読む例です。

| 回 | `read()` の結果 | 切る前の leftover | 返す行 | 呼び出し後の leftover |
|---|---|---|---|---|
| 1 | `"ab\nc"` | `"ab\nc"` | `"ab\n"` | `"c"` |
| 2 | `"d\nef"` | `"cd\nef"` | `"cd\n"` | `"ef"` |
| 3 | `0`(終わり) | `"ef"` | `"ef"` | `NULL` |
| 4 | `0`(終わり) | `NULL` | `NULL` | `NULL` |

### 特別なケース

- `fd < 0` または `BUFFER_SIZE <= 0`:すぐに `NULL` を返す。
- `read()` が `0`(ファイルの終わり)を返した:読むのをやめる。`leftover` に残りがあればそれを返し、空なら `NULL` を返す。
- `read()` が `-1`(エラー)を返した:`chunk` と `leftover` を free して `NULL` を返す。
- `malloc` が失敗した:確保したものをすべて free し、`leftover` を `NULL` にして `NULL` を返す。
- 行を切り取った後に何も残らないときは、`leftover` を `""` ではなく `NULL` にする。こうすることで、次の呼び出しで「ファイルが終わった」と判断できる。

### この方法を選んだ理由

- **必要な分だけ読む。** ファイル全体を読み込むのではなく、`\n` が見つかった時点で読むのをやめます。これは課題の要求どおりで、終わりが決まっていない標準入力でも動きます。
- **どんな `BUFFER_SIZE` でも動く。** 1行より小さいバッファなら、`\n` が出るまでループでくっつけ続けます。大きいバッファなら、複数の行が `leftover` に残り、次からの呼び出しでは新しく読まずに1行ずつ返します。
- **バッファをヒープに確保する。** `chunk` はローカル配列ではなく `malloc(BUFFER_SIZE + 1)` で作ります。10,000,000 バイトのローカル配列はスタックからあふれてしまいますが、ヒープなら確保できます。
- **メモリリークがない。** `leftover` を置き換える関数は、古い文字列を必ず free します(`gnl_strjoin` は第1引数を、`update_leftover` は古い `leftover` を free)。リークがないことは `valgrind --leak-check=full` で確認しました。
- **小さく分けてテストしやすい。** 処理を3つの小さな関数に分けたので、それぞれが Norm の25行以内に収まり、1段階ずつ動作を確認できました。

## Resources

- `man 2 read`、`man 2 open`、`man 3 malloc`、`man 3 free`
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptor — Wikipedia](https://en.wikipedia.org/wiki/File_descriptor)
- [Valgrind Quick Start Guide](https://valgrind.org/docs/manual/quick-start.html)
- テスター:[Francinette](https://github.com/xicodomingues/francinette)(gnlTester と fsoares のテスト)

### AI の使い方

この課題では、Claude(Anthropic)を家庭教師のように使いました。

- **概念の理解:** ファイルディスクリプタ、`read()` の戻り値、`read()` の後に `'\0'` を入れる理由、`static` 変数、`""` と `NULL` の違いについて説明を受けました。理解した内容は、小さな実験で自分で確かめました(`read()` をループで呼ぶ、`static` あり・なしのカウンタ関数を比べる)。

- **コードレビューとデバッグ:** 自分のコードの間違い(`if` の `{ }` 忘れ、`==` を `=` と書いたこと、テスト用 main での double free、ループのたびに `gnl_strlen` を呼んでいて遅かったこと、`malloc` 失敗時のリーク)を見つけてもらい、テスターや norminette の出力の読み方を教わりました。
