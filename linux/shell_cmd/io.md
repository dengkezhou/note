### 输入输出重定向

一般的输入输出默认是标准输入和标准输出，可以使用重定向使输入输出的目标改为文件。

格式： 

```
command < file   #重定位输入到file
command > file   #重定位输出到file，会先清空该文件，错误和警告信息不包含在内，仍会打印在屏幕。
command >> file  #以追加方式重定位输出到file
```

使用文件描述符做重定位

``` 
cmd > file  fd_1>&fd_2  将fd_1和fd_2重定向到file，
eg ls > t2  2>&1        将错误和标准输出重定向到t2
```

特别的使用 0-标准输入STDIN、1-标准输出STDOUT、2标准出错

### tee

tee命令也用来做输出重定向操作，将屏幕上的打印同时保存在文件中。

```shell
cmd | tee file
```

### xargs

 eXtended ARGuments 是给命令行传递参数的一个过滤器，也是组合多个命令的工具。

xargs 可以将管道或标准输入stdin数据转换为命令行参数，也能够从文件的输出中读取数据。

xargs可以转换输入格式

### dd

dd命令用于读取、转换并输出数据。

dd 可以从标准输入或文件中读取数据，根据指定的格式来转换数据，再输出到文件、设备或标准输出中。

```
格式:
dd [操作数] ... 或  dd option

参数：
if=in_file  :输入文件，默认为标准输入,使用标准输入时，输入字符串后+回车+ctrl D 结束。
of=out_file :输出文件，默认为标准输出

数据格式：
ibs=bytes : 一次输入bytes个字节，即指定块的大小
obs=bytes : 一次输出bytes个字节，即指定块的大小
bs=bytes  ： 同时设置输入、输出
cbs=bytes : 一次转换bytes个字节，即指定缓冲区大小
skip=blocks ：从输入文件开头跳过blocks个块后开始复制
seek=blocks : 从输出文件开头跳过blocks个块后开始复制
count=blocks : 复制blocks个块，块大小由ibs指定

格式转换
conv=
	ascii   :转换ebcdic为ascii
	ebcduc  :转换ascii为ebcdic
	ibm     :转换ascii为alternate ebcdic
    unblock :使每一行长度都为cbs，不足的用空格填填充。（长度中包含原有空格与换行，即文件中所有字符当做一行来处理）
    lcase   :大写转换为小写
    ucase   :小写转换为大写 
    sync    ：将每个输入块填充到ibs个字节，不足部分用空nul字符补齐。
```

### read

用于从标准输入中读取单行数据，默认读取键盘输入，当使用重定向或-u选项时，可以从文件中读取一行数据。

```shell
read：用法： 
read [-ers] [-a 数组] [-d 分隔符] [-i 缓冲区文字] [-n 读取字符数] 
     [-N 读取字符数] [-p 提示符] [-t 超时] [-u 文件描述符] [名称 ...]

    选项：
      -a array	将词语赋值给 ARRAY 数组变量的序列下标成员，从零开始
      -d delim	持续读取直到读入 DELIM 变量中的第一个字符，而不是换行符
      -e	使用 Readline 获取行
      -i text	使用 TEXT 文本作为 Readline 的初始文字
      -n nchars	读取 nchars 个字符之后返回，而不是等到读取换行符。
    		但是分隔符仍然有效，如果遇到分隔符之前读取了不足 nchars 个字符。
      -N nchars	在准确读取了 nchars 个字符之后返回，除非遇到文件结束符或者读超时，
    		任何的分隔符都被忽略
      -p prompt	在尝试读取之前输出 PROMPT 提示符并且不带
    		换行符
      -r	不允许反斜杠转义任何字符
      -s	不回显终端的任何输入
      -t timeout	如果在 TIMEOUT 秒内没有读取一个完整的行则超时并且返回失败。
    		TMOUT 变量的值是默认的超时时间。TIMEOUT 可以是小数。
    		如果 TIMEOUT 是 0，那么仅当在指定的文件描述符上输入有效的时候，
    		read 才返回成功；否则它将立刻返回而不尝试读取任何数据。
    		如果超过了超时时间，则返回状态码大于 128
      -u fd	从文件描述符 FD 中读取，而不是标准输入

eg :
read [-a] array -p "read a world into array: " && echo $array 

```

