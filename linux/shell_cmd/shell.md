1 查看内核的符号表
nm -A vmlinux 
nm -l vmlinux

2 动态记录命令行执行过程

```shell
sudo apt-get install asciinema

#录制命令执行过程到output文件，默认在/tmp/目录下
asciinema rec [output] 
#结束
exit 或 ctrl D + ctrl c
#演示
asciinema play output
```

