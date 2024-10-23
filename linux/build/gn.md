三、变量

gn的变量类型有bool 、64位有符号整数、字符串、列表，变量的类型不需要声明，使用时直接使用变量名而不需要$转义。

3.1 作用域

变量的值会按执行顺序生效，如下，test的依赖为test.c ， world的依赖为 hello.c，而不是以最后的定义生效。

```makefile
# file: BUILD.gn
src = "test.c"
executable("test") {
    sources = [
        src
        ]
}

src = "hello.c"
executable("world") {
    sources = [
        src
        ]
}

# file: 生成的ninja文件
build obj/test.test.o: cc ../test.c
build obj/world.hello.o: cc ../hello.c
```

3.2 运算符

