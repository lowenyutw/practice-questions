## file_make
256Byte～64MByte のファイルを作成します。
* ファイルの間隔サイズは n*4 <= 67108864。
* 16 ～ 255 文字の間隔で改行 '\n' が追加されます。

## 測定方法
1つのファイルをテストすることも、すべてのファイルをテストすることもできます。
コマンドが src.txt を追加しない場合、すべてのファイルがテストされます。

`$ ./file dst.txt [src.txt]`

## 測定結果
#### 実行時間の違い
基準は fgetc fputc。
実行時間基準は 64MBytes ファイルに設定されています。

> char *fgets(char *str, int n, FILE *stream)  
> size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)  
> ssize_t read(int fd, void *buf, size_t len)  
> 
> n は 256 に設定されています  
> nmemb は 65536 に設定されています  
> len は 65536 に設定されています

|            |実行速度|
|:-----------|:-----:|
|fgetc fputc |  100% |
|fgets fputs |  20%  |
|fread fwrite|  10%  |
|read write  |  20000%  |

#### 考察
1. fgetc fputc は、 1 文字ずつ読み取ります。
2. fgets fput は、'\n' または '\0' が検出されるまで文字列として読み取られます。fgetcfputc に比べて、文字列を読み込むため、はるかに高速になります。
3. fread fwrite は、ファイルの最後までサイズに従って読み取ります。 データはサイズに従って読み込まれるため、'\n' および '\0' の影響を受けません。
4. read write は文字を 1 文字ずつ読み取るように設定されているため、システム IO を繰り返し呼び出す必要があり、処理速度が非常に遅くなります。
