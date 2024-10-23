## **makefile概述**

makefile规定了整个工程的编译规则。

一个工程的源文件不计其数，按类型、功能、模块分别放置在不同的目录下，makefile定义了一系列规则来指定，哪些文件需要编译，哪些文件先编译，哪些文件不编译。

makefile也可以像shell一样执行系统命令。

这里对GNU的makefile进行描述：

**编译**（compile）：将源文件编译成中间代码文件（.o/.obj）,只检查语法的正确和函数、变量的声明正确。

**链接**（link）：主要是链接全局变量和函数，所以可以用中间文件来链接应用程序。链接时，需要明确指出每个文件的路径，若所需要的中间文件太多，可以将这些中间文件打包（生成库文件 .lib / .a）。

**执行**：make过程中，会一层又一层的去找文件的依赖性，直到最终编译出第一个目标文件

## **makefile编写规范**

### 格式

```
target：prerequisites
    command
    
target目标文件，可以是.o文件，也可以是执行文件。
prerequisites依赖文件，要生成target所需要的文件或目标。
command命令，make时执行的命令，可以是任何shell命令，必须以[Tab]健开始。

在make过程中，make只需要执行定义的command命令。 执行过程中，make会比较target 和 prerequisites的修改时间，若prerequisites较新或 target不存在，make才会执行command命令。make执行过程中，会一层一层找依赖关系，直到编译出第一个targe。

若目标没有被依赖，make则不会执行command命令，若要强制执行，可以在shell中指定目标执行命令make target。用这样的方法，我们可以规定一些辅助命令，如删除、打包、备份等。

eg:
a.out: test.o main.o
    gcc -o a.out test.o main.o

或
OBJECT = test.o\
         main.o
         
a.out:$(OBJECT)  
    gcc -o a.out $(OBJECT)



.PHONY表示target是一个伪目标文件，
.PHONY:clean
clean: 
    command
```

### 自动推导

当依赖项为x.o文件时，当能够找到对应的 x.c时， make 会自动推导出一个目标x.o

格式为

```makefile
x.o : x.c
	$(CC) -c -o $@ $
```

### 引用其他文件

include filename

若不理会include过程中的错误，使用 -include，

同C语言一样，为预处理指令，在执行过程中，会将filename中所有数据复制到makefile中。

搜索文件过程，

在当前路径或绝对路径下寻找，但当嵌套包含时相对路径只依赖于主makefile，所以要注意包含时的路径关系

如果make执行时，有“-I”或“--include-dir”参数，那么make就会在这个参数所指定的目录下去寻找。

如果目录<prefix>/include（一般是：/usr/local/bin或/usr/include）存在的话，make也会去找。 

### 文件搜索

make查找依赖文件时，一般只在当前目录下查找，

当需要依赖多个目录下文件时，可以添加路径，或使用VPATH变量，目录之间以“冒号：”隔开。

### 伪目标

伪目标只是一个标签而不是文件，所以make无法生成它的依赖关系和决定它是否要执行。只有通过显示地指明这个“目标”才能让其生效。

伪目标可以有依赖关系，也可以作为最终目标（将目标放在第一位）。

因为伪目标不是文件，所以make时，伪目标的command总是被执行的。

```makefile
.PHONY: clean  #显示声明伪目标
clean:
    rm *.o     #command中不能生成 clean 文件
```

### 多目标

当多个目标依赖同一个文件时，并且生成的命令相似，可以使用变量 @ 将其合并起来。

```makefile
target_1 target_2 : log.txt
	cat log.txt > $@

#上述规则等价于如下展开，但target_1是第一个目标，若makefile中只有该规则，make只会执行到生成target_1。
#@变量是当前target的结合，如同数组集合，$@会依次取出目标
target_1 : log.txt
	cat log.txt > target_1
	
target_2 : log.txt
	cat log.txt > target_2
```

### 静态模式

静态模式可以更加容易的定义多个目标的规则，可以让规则变得更弹性和灵活

```
格式：
targets : target-pattern : prereq-patterns
    commands
```

targets - 定义了一系列目标文件，可以有通配符，是目标的集合；

target-pattern - 指明了targets的模式，是目标集的模式；

prereq-patterns - 目标的依赖模式，它对target-pattern形成的模式再进行一次依赖目标的定义。

```makefile
objects = foo.o bar.o
$(objects) : %.o : %.c
    $(CC) -c $(CFLAGS) $< -o $@

#上述规则中指明了
#目标是从objects 中截取所有.o后缀的文件，即foo.o bar.o，
#依赖为%.c，其中依赖模式的 % 取自目标的 %，即对目标 foo.o而言，%为foo，对目标bar.o而言, %为bar。
#所以上述规则可以展开为
objects = foo.o bar.o
foo.o : foo.c
    $(CC) -c $(CFLAGS) $< -o $@

bar.o : bar.c
    $(CC) -c $(CFLAGS) $< -o $@
```

### 自动生成依赖性

在Makefile的依赖关系中，目标 %.o应该依赖 %.c和其include的头文件。要手动维护这个依赖会比较困难。

gcc中 -MM选项可以根据 include关键字自动生成依赖性（-M：生成的依赖包含系统头文件，-MM：生成的依赖中不包含系统头文件）。

如: main.c 中包含了 defs.h

那么 gcc -MM main.c 的输出为：main.o : main.c defs.h。

GNU建议将编译器为每一个源文件的自动生成的依赖关系放到一个文件中，为每一个name.c生成一个name.d的Makefile文件，保存c文件的依赖关系，并在Makefile中include。

```makefile
#生成.d文件
obj = f1.o 
obj : %.o : %.c
	cc $< -MM > $@.d
    cc $< -o $@
#gcc -MM  name.c > name.o.d，-MM会屏蔽gcc的-c -o选项，不能同时使用。
```



### 显示命令

make执行时，会先在屏幕上显示命令行，

在命令行前加 @，make执行时将不会显示命令。

make执行时，可以添加参数 -n 或 --just-print，只显示命令行，但不执行；参数 -s 或 --slient，禁止命令的显示。

```makefile
#如
@$(cc) - c $(CFLAGS) $< -O $@
```

### 命令执行

makefile的每一行命令都是一个进程，命令之间的变量是不能互通的。若想要上一个命令的结果在下一个命令中使用，需要将两个命令写在一行，并用 “分号;”隔开“。

命令中的变量会在执行命令前完成替换，无法使用同一行中上一个命令中定义的变量。

当执行命令出错（返回值不为0）时，make就会终止退出；当我们不需要判断命令出错如mkdir，错误表示目录已存在，可以在命令行前加上 “减号 - ",忽略命令的返回值判断。

实际上，"@、- 、+"这些符号是make的功能，“@”：取消命令的回显；“-”：命令行的非零返回将会被忽略，即忽略make执行时的错误；“+”：命令行始终执行，不受参数 -n、-q、-t的影响。

也可以用

make -i   (忽略所有命令返回值)  

make -k（错误时终止当前目标的所有命令，继续执行下一目标的命令）

当一行有多个命令时，make执行时只会判断该行最后一个命令的返回值，忽略其他命令的返回值。

当target 以 .IGNORE 声明，make时不判断该目标所有命令的返回值。

```makefile
all:
	cd ../; pwd   #打印上一级目录
	pwd           #打印当前目录

var1 = "yyy"
target:
    var="xxx"; echo {var}; echo {$(var)}  #输出{var} 和 {}
    var1="xxx"; echo {$(var1)}            #输出{yyy}
```

### 嵌套执行make

若一个工程中有多个目录，我们可以为每一个目录都写一个makefie，这样更加简洁且易于维护。

在主目录下写一个总控的makefile，依次对子目录进行make。

嵌套执行makefile时，总控的makefile变量会传递到子makefile，但不会覆盖子makefile的变量。可以使用显示的声明 export var 或 unexport var；也可以用export不带变量，表示传递所有的变量。

嵌套执行时 -w（--print-directory）参数时非常有用的，在切换目录时打印目录信息。

```makefile
MAKE = make [-i]

TARGET:
	cd subdir; $(MAKE)   #到subdir目录下执行make -i,
#等价于
    $(MAKE) -C subdir
```

### 定义命令包

当makefile需要多次使用同一些命令序列时，可以将这些序列定义为一个变量，功能类似c语言的函数。命令包以define 开始 ，以 endef 结束。

```makefile
#定义一个命令包,注意时endef,不是endif
define cmd_func
    cmd1
    cmd2
	......
endef

#使用，和其他变量一样，在make时自动完成替换。
TARGET:
    $(cmd_func)
    
#该方法和宏一样，只是单纯的展开，所以也可以定义多行的变量，函数，命令等。只是注意cmd需要以TAB开头。
```



## 变量与符号

Makefile中的变量类似于c语言的宏，在make执行目标之前完成字符串的替换。

### 变量的定义

```makefile
#定义变量为一个字符串，可以先使用字符串然后再定义，其值为最后一个定义的值。
#但是当出现递归的形式 如 var = $(var)，或相互包含如 a =$(b)  b=$(a)时，该过程执行时将陷入循环展开中，当然该种方式在make时会检查报错。
#在任何位置echo $(var)，都会输出 yyy
var = xxx
var = $(foo)
foo = yyy

#依据顺序定义变量，在之后定义的foo的值不再展开到此处。 但该定义不影响var展开到之前或之后的使用中。
#var := xxx 同 var = xxx，因为xxx不是变量，不会被展开。
var := $(foo)

#定义一个空格
nullstring :=
space := $(nullstring) #end of the line
#在=右边很难描述一个空格，所以使用空的变量作为构建的开始，使用 # 作为结束，表示一个空格变量 space。
#由此可见，在定义变量时不要在其后添加 #注释，这会导致变量后面多出一些空格,如：
dir := foo  #目录
#此时dir是 “foo   ”，若使用 ls $(dir)/bar ---->make -n输出为ls foo   /bar，而不是 ls foo/bar。 
#添加注释并不是变量中附带空格的原因，真正的原因是编辑时确实写入了空格，和#无关，#只是更明显的描述出来。

#若var没有被定义，则var = xxx，否则不做执行
var ?= xxx 

#追加变量值
var += yyy

#override指示符
#当命令行make时指定变量参数，那么makefile中同名的变量将会被替换。若不希望变量被替换，就可以使用override指示符。
override var = xxx
override var := xxx
override var += xxx
#当变量定义时使用了 override，那么使用+=时也需要带override
#但override并不主要是为了调整Makefile和执行时命令参数的冲突，而是为了使用户在命令行修改变量时追加Makefile中变量的值。
#如，想在编译时必须打开 -g 选项，那么可以定义
override CFLAGS += -g

#目标变量--仅在目标的作用范围内生效，不影响其他规则，也不受其他规则影响。
#格式 target : [override] variable-assignment 带有override时屏蔽make命令行带入的变量或环境变量
#如下，不管其他位置CFLAGS怎么改变，该target的cmd一直使用-g
target : CFLAGS = -g
target : foo.c
	cc $(CFLAGS) $< -O $@
#模式变量--使目标变量应用在相同模式的目标中
%.o : CFLAGS = -g

```

变量值的替换

```makefile
#替换变量中的共有部分，格式 $(var:x=y)，将var中x字符串替换为y字符串，但x需要是一个字符串的结尾（结尾：后接空格或结束符）
foo := a.o b.o c.o
bar := $(foo:%.o=%.c)
#结果： bar为 a.c b.c c.c，
```

默认的变量

```
@ -指目标文件target    ^ -指所有的依赖文件    < -指第一个依赖文件 
CC -自动推导时使用的编译器，默认为cc
MAKECMDGOALS 最终目标，即make命令行的目标



```

环境变量

make运行时将系统的环境变量载入Makeifle文件中，但如果Makefile中已经定义了这个变量，或者由命令行代入，则这个环境变量将会被覆盖。等同于C中的全局变量被局部变量遮蔽。

在make嵌套调用时，上层定义的变量会以系统环境变量的方式传递给下层，默认情况下只会传递export声明的变量和命令行带入的变量。

make -e参数将选择用环境变量覆盖Makefile中的变量。

隐含规则中使用的变量

```
AR
    函数库打包程序。默认命令是“ar”。
AS
    汇编语言编译程序。默认命令是“as”。
CC
    C语言编译程序。默认命令是“cc”。
CXX
    C++语言编译程序。默认命令是“g++”。
CO
    从 RCS文件中扩展文件程序。默认命令是“co”。
CPP
    C程序的预处理器（输出是标准输出设备）。默认命令是“$(CC) –E”。
FC
    Fortran 和 Ratfor 的编译器和预处理程序。默认命令是“f77”。
GET
    从SCCS文件中扩展文件的程序。默认命令是“get”。
LEX
    Lex方法分析器程序（针对于C或Ratfor）。默认命令是“lex”。
PC
    Pascal语言编译程序。默认命令是“pc”。
YACC
    Yacc文法分析器（针对于C程序）。默认命令是“yacc”。
YACCR
    Yacc文法分析器（针对于Ratfor程序）。默认命令是“yacc –r”。
MAKEINFO
    转换Texinfo源文件（.texi）到Info文件程序。默认命令是“makeinfo”。
TEX
    从TeX源文件创建TeX DVI文件的程序。默认命令是“tex”。
TEXI2DVI
    从Texinfo源文件创建军TeX DVI 文件的程序。默认命令是“texi2dvi”。
WEAVE
    转换Web到TeX的程序。默认命令是“weave”。
CWEAVE
    转换C Web 到 TeX的程序。默认命令是“cweave”。
TANGLE
    转换Web到Pascal语言的程序。默认命令是“tangle”。
CTANGLE
    转换C Web 到 C。默认命令是“ctangle”。
RM
    删除文件命令。默认命令是“rm –f”。

2、关于命令参数的变量

下面的这些变量都是相关上面的命令的参数。如果没有指明其默认值，那么其默认值都是空。

ARFLAGS
    函数库打包程序AR命令的参数。默认值是“rv”。
ASFLAGS
    汇编语言编译器参数。（当明显地调用“.s”或“.S”文件时）。
CFLAGS
    C语言编译器参数。
CXXFLAGS
    C++语言编译器参数。
COFLAGS
    RCS命令参数。
CPPFLAGS
    C预处理器参数。（ C 和 Fortran 编译器也会用到）。
FFLAGS
    Fortran语言编译器参数。
GFLAGS
    SCCS “get”程序参数。
LDFLAGS
    链接器参数。（如：“ld”）
LFLAGS
    Lex文法分析器参数。
PFLAGS
    Pascal语言编译器参数。
RFLAGS
    Ratfor 程序的Fortran 编译器参数。
YFLAGS
    Yacc文法分析器参数。
```

通配符

```
~ 家目录
* 匹配若干个字符
```

### 条件分支

```makefile
ifeq/ifneq ($(var1), $(var2))
	cmd
eles
	cmd
endif

ifdef / ifndef  var_name
else
endif
```

### 函数

格式 ${func args} 或 $(func args)，多个参数以逗号','分隔，执行结果可作为变量看待

参数可使用变量，括号的使用上最好和变量统一

### 字符串处理函数

```makefile
#字符串替换函数，将字符串text中的from替换为to,注意不要再to前加空格。
#返回结果为替换后的字符串，但变量的值并未改变。
$(subst <from>,<to>,<text>)
$(subst :, ,$(VPATH))  #VPATH中的":"替换为空格。

#模式字符串替换函数，pattern 和 replacement可含有通配符，且是单词的尾部（以空格、换行等隔开）
#返回结果为替换后的字符串
$(patsubst <pattern>,<replacement>,<text>)

#去空格函数，去掉字符串开头和结尾的空字符，并将多个连续的空字符合为一个
#返回去掉空格后的字符串
$(strip <string>)

#查找字符串函数，在in中查找find字符串
#找到返回find，否则返回空字符串(空字符串为“”)
$(findstring <find>,<in>)

#过滤函数，以<pattern>模式过滤<text>字符串中的单词，保留符合模式的单词，可以有多个模式
#返回符合模式<pattern>的字串
#反过滤函数，保留不符合模式的单词。
$(filter <pattern ...> ,<text>)
$(filter-out <pattern ...>, <text>)

#排序函数，给list中的单词排序（升序）
#返回排序后的字符串
$(sort <list>)

#取单词函数
#返回text中的第n单词（从一开始计数），若n大于单词数，则返回空字符串
$(word <n>,<text>)

#取第一个单词函数
$(firstword <text>)

#取字符串函数，
#返回text中第s到e的单词串（从一开始计数），若s>单词数，返沪空字符串，若e>单词数，返回s到结尾的字符串。
$(wordlist <s>,<e>,<text>)

#统计单词个数
$(words <text>)
```

### 文件名操作函数

以下每个函数的字符串参数都会被当作文件名来对待。

```makefile
#取目录名函数，参数可以有多个文件名
#返回names的目录部分(最后一个"/"之前的字符串，如果没有反斜杠，则返回 "./")。
$(dir <names ...>)

#取文件名函数
#返回names的文件名部分(最后一个"/"之后字符串)
$(notdir <names ...>)

#取后缀函数，没有后缀则返回空字符串
$(suffix <names ...>)

#取前缀函数，包括目录部分
$(basename <names ...>)

#加后缀函数
$(addsuffix <suffix>,<names ...>)

#加前缀函数
$(addprefix <prefix>,<names ...>)

#连接函数，按单词对应的将list2加到list1后
$(jion <list1>,<list2>)

#展开通配符函数，在变量的定义和函数引用时，通配符会失效，所以需要使用wildcard函数展开
$(wildcard PATTERN)
$(wildcard *.c)  # 获取c文件列表，使用空格隔开。
```

### 其他函数

```makefile
#循环函数，把list中单词逐一取出放到参数var中所执行的变量中，然后执行text的表达式。
#每次text都会返回一个字符串，这些字符串连接在一起以空格分隔，作为最终的返回值
#text可以是一个命令，也可以单纯是一个字符串，var是一个局部的变量，仅在foreach函数中生效。
$(foreach <var>,<list>,<text>)
names := a b c d
files := $(foreach var,$(names),$(var).o)
#files 为 a.o b.o c.o d.o

#条件函数,返回part执行的结果，若没有part，则返回空字符串。
$(if <condition>,<then-part>)
$(if <condition>,<then-part>,<else-part>)

#call函数，为函数创建新的参数列表,当make执行这个函数时，expression参数中的变量，如$(1) $(2)会被新的参数列表依次取代。
#返回expression执行的结果
$(call <expression>,<parm1>,<parm2>,...)
reverse = $(2) $(1)
foo = $(call reverse,a,b)
#则 foo = b a

#origin函数，返回变量variable的来源属性,下列时可能的返回值
#"undefined"   : 变量未定义
#"default"     : 默认定义，如 CC
#"environment" : 环境变量，且make执行时没有打开-e参数
#"file"        : 定义在Makefile中
#"command line": 定义在命令行中
#"override"    : 被override指示符重新定义
#"automatic"   : 命令运行中的自动化变量
$(origin <variable>)

#shell函数，新生成一个shell程序执行命令，并将结果返回
$(shell <cmd> <parm>)

#控制make的函数，根据makefile运行中的信息决定make继续执行还是停止
#产生一个错误/警告，该函数不会在一被使用就产生错误/警告，所以如果将其定义在某个变量中，并在后续的脚本中使用这个变量也是可以的。
$(error <text ...>)
$(warning <text ...>)
ifdef ERROR_001
$(error error is $(ERROR_001))
endif

ERR = $(error found an error!)
.PHONY : err
err: ;$(ERR)

#eval 将text当作makefile中的一部分执行
$(eval text)
```

## make执行

make会在当前目录下按顺序查找 makefile 、Makefile的文件，若要执行指定文件，make -f filename。

命令选项 参考 make -h

```
一些伪目标规范
all:编译所有的目标
clean:删除所有被make创建的文件
install:安装已编译好的程序，即把目标文件拷贝到指定的目录下
print:列出改变过的源文件
tar:把源程序打包备份
dist:创建一个压缩文件，一般是把tar文件压缩成z、gz文件
TAGS:更新所有的目标，以备完整的重新编译使用
check、test:用来测试makefile的流程。
```

**模块编译**

```makefile
#模块的编译需要指明内核文件路径，和待编译文件的路径
KERNEL_VER = $(shell uname -r)
KERNEL_DIR = /lib/modules/$(KERNEL_VER)/build/
PWD = $(shell pwd)  #文件路径，不一定是PWD。

#cc 和 ARCH 根据编译器和CPU类型定义，且一般定义在srcipt文件中，使用source加载。

MODULE = drvname            #目标文件

obj-m := $(MODULE).o        #-m 表明是modules编译
$(MODULE)-objs := f1.o\
                  f2.o      #需要编译的文件
         
all:
    make -C $(KERNEL_DIR) M=$(PWD) modules  #编译指令
    
install:
	sudo insmod ./$(MODULE).ko
	sudo chmod 666 /dev/$(MODULE)           
	#加载ko生成的设备文件权限为600，且一般是root所有，应用程序使用open接口时，可能没有权限。
	#生成的设备文件名，和 makefile中MODULE宏无关，设备文件是驱动注册设备时使用device_create创建或在命令行使用mknod创建的。MODULE宏是生成的ko文件名称，一般情况下，设备文件名和生成的ko文件名定义一致。
	
.PHONY:clean
clean:
    rm -rf *.ko *.o  *.mod *.mod.c *.symvers *.order
```

## makefile .config kconfig

 参考 https://zhuanlan.zhihu.com/p/28461589 

```
Makefile : 编译源文件的方法
Kconfig: 内核的配置菜单
.config：用户配置菜单后生成的文件，是编译内核配置的依据，决定了哪些模块需要编译

子目录的Makefile被顶层的Makefile包含。
子目录的Makefile包含当前目录的Kconfig。
```

```
Makefile
直接编译进内核
obj-y += xxx.o

条件编译，根据.config文件的CONFIG_XXX来决定文件是否编译进内核
obj-$(CONFIG_HELLO) += XXX.0

模块编译，即执行make 或 make modules 时被编译为ko文件。
obj-m += xxx.0

Kconfig 
每个config菜单项都有类型定义：bool、tristata（三态：内建、模块、移除）、string字符串、hex十六进制、integer整型。
作用：决定make menuconfig时展示的菜单项
格式：
config DRV_NAME
    bool "说明"
    default n
    help:
        enable drv name
生成.config时，会有一个 CONFIG_DRV_NAME=y（或m）的配置项。
        
bool:在menuconfig中显示为[]，可以选择是否编译进内核
tristate:在menuconfig中显示为<>，可以选择编译进内核，模块，不编译。
"说明" :在menuconfig中显示在选择后面
dependon:该选项依赖于另一个选项，只有当依赖被选中时，当前配置项的提示才会出现。
select:反向依赖关系，该选项选中时，同时选中select后面的选项。
help:帮助信息
目录层次迭代：Kconfig中会有类似语句，source "driver/xxx/Kconfig" 用来嵌套新的Kconfig文件。

Kconfig决定在menuconfig中的位置
menu "菜单名"
	config x_1
	config x_2
	
source "xxx/Kconfig"

endmenu

.config
内核编译的参考文件，
修改内核配置的方式有3种: make menuconfig、make xxx_defconfig、直接修改.config,但因为配置项的依赖关系，直接修改.config可能无效。
```



## 内核编译中的Makefile

1 执行make help查看参数列表(部分)

```
leaning targets:
  clean       - Remove most generated files but keep the config and
                    enough build support to build external modules
  mrproper    - Remove all generated files + config + various backup files
  distclean   - mrproper + remove editor backup and patch files

Configuration targets:
  config      - Update current config utilising a line-oriented program
  nconfig         - Update current config utilising a ncurses menu based program
  menuconfig      - Update current config utilising a menu based program
  oldconfig   - Update current config utilising a provided .config as base
  defconfig   - New config with default from ARCH supplied defconfig
  savedefconfig   - Save current config as ./defconfig (minimal config)
  helpnewconfig   - List new options and help text
  olddefconfig    - Same as oldconfig but sets new symbols to their
                    default value without prompting
                    
Other generic targets:
  all         - Build all targets marked with [*]
* vmlinux     - Build the bare kernel
* modules     - Build all modules

```

scripts目录下的控制文件

scripts/目录下有相当多的脚本对整个内核编译进行控制

Kbuild.include ：定义了常用的一系列通用变量与函数，在top Makefile开始时就被include,作用于整个内核的编译过程。

Makefile.build ： 根据用户传入的参数完成真正核心的编译工作，包括编译目标的确定、递归进入子目录的编译工作等等，作用于整个内核的编译过程。

Makefile.lib：负责根据用户配置或者top Makefile传入的参数，对各类待编译文件进行分类处理，以确定最后需要被编译的文件、需要递归编译的子目录，将结果赋值给相应的变量以供真正的编译程序使用。

link-vmlinux.sh：对于每一个递归进入的编译目录，编译完成之后，都将在该目录下生成一个build-in.a文件，这些文件由需要编译进内核的模块打包而成，link-vmlinux.sh将这些文件统一链接起来，生成对应的镜像。

Makefile.host：这个文件主要控制生成主机程序，严格来说，主机程序并不主导编译过程，它只是作为一种辅助软件，比如menuconfig在编译主机上的界面实现，fixdep检查工具等。

各级子目录下的Kconfig 和 Makefile

Kconfig负责该模块的配置共工作，Makefile提供当前目录下需要编译的目标文件或者需要递归进入的目录（arch目录除外)，交由scripts/Makefile.build 和 scripts/Makefile.lib统一处理。

## shell

set 

根据不同需求来设置当前shell的执行方式

set -e; cmd  # 当cmd返回非0时，立即退出当前shell

set  -x; cmd #在执行每一行shell时，会输出执行的内容

## 问题记录

### include的隐式规则：

​	include包含一个文件时，若该文件同时被定义为一个目标，在make过程中会首先执行该目标。

### 函数中变量替换的问题

在Makefile执行前，会将其中所有的变量进行处理和替换，是Makefile预处理过程中的一部分，但对于调用自定义函数和调用Makefile内部函数的处理有很大区别。

调用自定义函数为$(call func, param)，预处理过程完成func中变量的替换，最终的结果等同于将print函数放在cmd的位置，函数的执行在make过程中，使用shell执行该命令。

调用内部函数使用$(func param)，整个函数是一个变量，在预处理过程中就完成了函数的执行，并将返回值放在cmd的位置，因为该返回值大多数是一个字符串，所以在make过程中并不处理。

关联：call函数本身就是Makefile内部函数，其返回值是处理过后的cmd，所以函数的调用可以看做只有调用内部函数一种，而在例子中，Makefile将自定义函数看做变量，call函数就返回该变量。

变量的写法：shell中的变量格式为$var， Makefile中变量的格式为$(var)，所以为了执行正确，要分清楚变量替换的位置是在预处理过程(Makefile语法)，还是在shell执行cmd过程。

可以使用make target -n 来观察预处理过程。（-n 选项只显示命令而不运行）

```makefile
VARIABLES =a b c
.PHONY: printvars
printvars:
    $(call print)
    
define print
    for var in $(VARIABLES); do \
        if test "b" = "$$var"; then \
            echo $$var ; \
        fi; \
    done
endef

# make printvars 结果
# for var in a b c; do if test "b" = "$var"; then echo $var ; fi; done
# b
# 上述Makefile中有两个变量 $(VARIABLES) 和 $(call print),在预处理过程中完成替换，所以可以看到make执行的cmd为上述结果。
# for函数为shell命令，变量使用$var格式，$$是Makelife语法，转义为字符$。



printa:
    $(foreach V, $(.VARIABLES), \
        $(if $(filter file,$(origin $(V))), \
            $(info $(V)=$($(V))) \
        ) \
    )
# make printa 和 make printa -n 结果相同
# CURDIR=/home/intchains/test/make_1
# SHELL=/bin/sh
# MAKEFILE_LIST= Makefile
# print=	for var in a b c; do if test "b" = "$var"; then echo $var ; fi; done
# .DEFAULT_GOAL=printvars
# MAKEFLAGS=
# VARIABLES=a b c
# 整个函数在Makefile预处理过程中执行，变量使用$(var)格式，所以$($(V))中括号不能缺少。

```

