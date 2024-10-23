## 一、介绍

ninja是一个构建系统，与Make类似，ninja的主要设计目标是速度。

安装: sudo apt-get install ninja-build

输入：描述将源文件处理为目标文件的过程。

输出：保持目标处于最新的状态。

在高层视角下，任何构建系统主要执行三项任务：加载和分析构建目标，计算出达到构建目标所需的步骤，执行这些步骤。

一些名词的概念

| 概念   | 译名（非官方） | 解释                                                         |
| ------ | -------------- | ------------------------------------------------------------ |
| edge   | 边             | 即build语句，指定目标、规则和输入，是编译过程中拓扑图中的一条edge。 |
| target | 目标           | 编译过程中产生的目标，由build指定。                          |
| output | 输出           | build语句的前半段，是target的另一种称呼。                    |
| input  | 输入           | build语句的后半段，是依赖的另一种称呼。                      |
| rule   | 规则           | 通过指定command与一些内置变量，决定如何从输入产生输出。      |
| pool   | 池             | 一组rule 或 edge，通过指定depth，可以控制并行的上限。        |
| scope  | 作用域         | 变量的作用范围，有rule与build语句的范围，也有文件级别的。rule也有作用域。 |

## 二、运行

默认情况下，ninja会在当前目录查找build.ninja运行，并生成所有过期的目标。

可以在命令行指定目标。

输出显示格式为 [%f/ %t]，即[完成的边数/完成目标必要的总边数]。

```
usage: ninja [options] [targets...]

if targets are unspecified, builds the 'default' target (see manual).

options:
  --version      print ninja version ("1.10.0")
  -v, --verbose  show all command lines while building

  -C DIR   change to DIR before doing anything else
  -f FILE  specify input build file [default=build.ninja]

  -j N     run N jobs in parallel (0 means infinity) [default=10 on this system]
  -k N     keep going until N jobs fail (0 means infinity) [default=1]
  -l N     do not start new jobs if the load average is greater than N
  -n       dry run (don't run commands but act like they succeeded)

  -d MODE  enable debugging (use '-d list' to list modes)
  -t TOOL  run a subtool (use '-t list' to list subtools)
    terminates toplevel options; further flags are passed to the tool
  -w FLAG  adjust warnings (use '-w list' to list warnings)

```

example ：

 指定target执行 ninja f1 或 ninja clean 时，只会单独执行一条edge

```
[1/1] gcc f1.c -o f1
[1/1] rm f1
```

不指定目标时，会执行所有的build，执行从上而下执行，执行过程是并行的，默认的并行数为10，若需要保证执行的先后顺序，可以使用 ninja -j 1 单进程执行。

若要忽略执行的错误可以在command后面添加 || exit 0强制返回成功，ninja不支持在command前添加 -。

```
[1/2] rm f1
FAILED: clean 
rm f1
rm: 无法删除 'f1': 没有那个文件或目录
[2/2] gcc f1.c -o f1
ninja: build stopped: subcommand failed.
```



```shell
# file : build.ninja
ninja_required_version = 1.0

target = f1

rule compile
    command = gcc ${in} -o ${out}

rule clean
    command = rm ${target}

build ${target} : compile f1.c

build clean : clean     
```



## 三、变量

变量有两种，内置变量与自定义变量，两者都可以通过 var = str的方式定义，通过 $var 或 ${var} 的方式引用。

变量的类型只有一种，就是字符串。

### 3.1 内置变量

builddir  指定一些文件的输出目录。

ninjia_required_version 指定ninja命令的最低版本。

```
builddir = /tmp/
ninja_required_version = 1.5
```

### 3.2 环境变量

```
环境变量
%s started edges的数量
%t 完成构建必要的edges总数
%p started edges的百分比
%r 当前正在运行的edges数
%u 要开始的剩余edges数
%f 完成的edges数
%o 每秒完成edges数的总体效率
%c 每秒完成edges数的当前效率
%e 经过的时间，单位秒
%% 一个普通的%字符
```

### 3.3 符号

```
$  行末尾的$是转义字符，并未真正的换行
#  单行注释
|  后面跟输入输出时，表示隐式依赖或隐式输出，不会出现在 ${in} ${out}中
|| 后面跟输入时，表示 order-only依赖，不会出现在${in}中。order-only字面意思仅仅顺序需要的，在首次编译时，和其他依赖表现相同，再次编译时，如果order-only依赖缺失，ninja会更新它们，但不会执行对应的build edge更新输出。简单说即输出不会与order-only依赖的更新时间做比较。
```



## 四、语法

包含描述依赖关系的基本功能，但缺乏语法结构如分支、循环等，无法表达复杂的决策。

本质上是纯粹的配置文件，所以比Makefile简单得多。

| 关键字   | 作用                                       |
| -------- | ------------------------------------------ |
| build    | 定义一个edge                               |
| rule     | 定义一个rule                               |
| pool     | 定义一个pool                               |
| default  | 指定默认的一个或多个target                 |
| include  | 添加一个ninja文件到当前的scope             |
| subninja | 添加一个ninja文件，其scope与当前文件不同。 |
| phony    | 一个内置的特殊规则，指定非文件的target     |

### 4.1 rule 

rule 是通过输入列表${in}生成输出列表${out}的规则，目标一般是文件，phony可以指定非文件目标。

```shell
rule name
	command = echo ${in} > ${out}
	description = this is a rule of name
	var = str
```

| rule中的内置变量         | 作用                                                         |
| ------------------------ | ------------------------------------------------------------ |
| command                  | 定义rule必须得变量，指定实际执行的命令。                     |
| description              | 说明，会替代command在无 -v 选项时的打印。                    |
| generator                | 指定后，这条rule生成的文件不会被默认清理。                   |
| in                       | 空格分割的输入列表                                           |
| in_newline               | 换行分割的输入列表                                           |
| out                      | 空格分割的输出列表                                           |
| depfile                  | 指定一个Makefile文件作为额外的显式依赖                       |
| deps                     | 指定gcc或msvc方式的依赖处理                                  |
| msvc_deps_prefix         | 在 deps = msvc情况下，指定需要去除的msvc输出前缀             |
| restat                   | 在command执行结束后，如果output时间戳不变，则当作未执行      |
| rspfile, rspfile_content | 同时指定，在执行command前，把rspfile_content写入rspfile文件，执行成功后删除 |

### 4.2 build edge

build代码块是编译过程中的一个edge，

如下: foo是output，bar是input，phony是rule ，var是自定义变量。

在build块中，也可以对rule块中的变量进行扩展（复写）。 

```
build foo : phony bar
	var = str
```

### 4.3 pool

pool的意义在于限制一些非常浪费硬件资源的edge同时执行。

目前Ninja只有一个内置的pool，名为console。 这个pool的depth等于1，只能同时执行1个edge。 它的特点是，可以直接访问stdin、stdout、stderr三个特殊stream。

如下： 定义一个pool example，在 rule 中引用example，限制 edge a b c 同时只能执行两个。

```
pool example
    depth = 2

rule echo_var
    command = echo ${var} >> ${out}
    pool = example

build a: echo_var
    var = a

build b: echo_var
    var = b

build c: echo_var
    var = c
```

