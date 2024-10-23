介绍编译工具的选项和作用

编译的过程

hello.c -->预处理cpp--->hello.i -->编译cc1--> hello.s --> 汇编as-->hello.o-->链接ld--->hello.elf 

### 一、gcc

1.1 调试符号

在使用gdb调试时，需要可执行文件中含有调试信息，包括符号表、行号信息、类型信息、源代码文件、宏定义等。

可以使用 "-g"选项使编译生成的文件中包含这些信息。

但有一些选项会影响调试信息，造成不能正常调试

```
-O2/3 优化等级,可能改变代码执行的顺序
-mno-dwarf2-asm 、-mdwarf2-asm
 Don't (or do) generate assembler code for the DWARF line number debugging info.  This may be useful when not using the GNU assembler.
 
ld选项:
-s
--strip-all
   Omit all symbol information from the output file.
-S
--strip-debug
   Omit debugger symbol information (but not all symbols) from the output file.
   
--strip-discarded
-no-strip-discarded
   Omit (or do not omit) global symbols defined in discarded sections.  Enabled by default.
```

三、objdump

四、objcopy

objcopy用来复制一个目标文件内容到另一个文件中，可以使用不同于源文件的格式来输出目的文件。

用法： objcopy [option] input_file [output_file]

eg : objcopy -O binary test.elf test.bin

elf文件是可执行文件，包含了 elf 头格式 、汇编、调试信息，使用objcopy提起其中的纯汇编信息构成bin文件，可以在没有os系统的机器上使用。

```
option:
  -I --input-target <bfdname>      Assume input file is in format <bfdname>
  -O --output-target <bfdname>     Create an output file in format <bfdname>
  -B --binary-architecture <arch>  Set output arch, when input is arch-less
  -F --target <bfdname>            Set both input and output format to <bfdname>
     --debugging                   Convert debugging information, if possible
  -p --preserve-dates              Copy modified/access timestamps to the output
  -D --enable-deterministic-archives
                                   Produce deterministic output when stripping archives (default)
  -U --disable-deterministic-archives
                                   Disable -D behavior
  -j --only-section <name>         Only copy section <name> into the output
     --add-gnu-debuglink=<file>    Add section .gnu_debuglink linking to <file>
  -R --remove-section <name>       Remove section <name> from the output
     --remove-relocations <name>   Remove relocations from section <name>
  -S --strip-all                   Remove all symbol and relocation information
  -g --strip-debug                 Remove all debugging symbols & sections
     --strip-dwo                   Remove all DWO sections
     --strip-unneeded              Remove all symbols not needed by relocations
  -N --strip-symbol <name>         Do not copy symbol <name>
     --strip-unneeded-symbol <name>
                                   Do not copy symbol <name> unless needed by
                                     relocations
     --only-keep-debug             Strip everything but the debug information
     --extract-dwo                 Copy only DWO sections
     --extract-symbol              Remove section contents but keep symbols
     --keep-section <name>         Do not strip section <name>
  -K --keep-symbol <name>          Do not strip symbol <name>
     --keep-file-symbols           Do not strip file symbol(s)
     --localize-hidden             Turn all ELF hidden symbols into locals
  -L --localize-symbol <name>      Force symbol <name> to be marked as a local
     --globalize-symbol <name>     Force symbol <name> to be marked as a global
  -G --keep-global-symbol <name>   Localize all symbols except <name>
  -W --weaken-symbol <name>        Force symbol <name> to be marked as a weak
     --weaken                      Force all global symbols to be marked as weak
  -w --wildcard                    Permit wildcard in symbol comparison
  -x --discard-all                 Remove all non-global symbols
  -X --discard-locals              Remove any compiler-generated symbols
  -i --interleave[=<number>]       Only copy N out of every <number> bytes

```
