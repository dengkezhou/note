incbin ，汇编伪指令，将二进制文件完整的编译进目标文件中。

格式 

```c
.incbin "filename"
```

例子：

```c
/*data.S
* 定义一个.my_data段，段内容是文件data的数据，文件名使用相对地址
* g_data 声明一个全局指针，表示该段的起始地址。
*/
.section .my_data,"a"
.balign 16
.global g_data
g_data:
.incbin "data"
.balign 16
    
/* f1.c
* 打印 g_data的内容  
*/
#include <stdio.h>
extern long g_data[]; /*当g_data声明为long时，发现 &g_data才是my_data段的起始地址*/
int main()
{
    int *a = g_data;
    printf("addr = %p\n",a);
    printf("data = 0x%x\n", *a);
    return 0;
}

/*data
* 普通文件
*/
12345678

/*输出结果
 addr = 0x5623e9b56040
 data = 0x34333231    (4321的ASCII码)
 */
```

