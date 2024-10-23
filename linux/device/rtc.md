## rtc 

real time clock，实时时钟，是用来计时的硬件。

事件：闹铃、溢出

当设置闹铃时间和对应寄存器使能时，当rtc时间到达，则产生alarm中断。特别的，若alarm enable register只使能了min，则在每个小时的对应分都会产生中断。

溢出 rolls over，当每个时间分量进位（59s -- > 0s），则会产生一次对应的中断。

## bms 运行流程

设置时钟模式

0x30 Keep Rtc ，在复位时不复位时间和日历，及其相关的寄存器。

0x0  rtc  ctrl , 低电平有效，rtc使能， 即时间和日历开始自增。

0x4  hour mode, 设置时间模式，12h/24h



申请时钟中断

rtc--事件中断，即响铃和rolls over，事件类型可参考中断使能寄存器。申请的中断也需要再对应的事件enable之后触发。

rtc_change -- 时间改变中断，芯片设计1s触发一次，不需要寄存器控制，在enable_irq 即可触发。



设置rtc时间、日历

在设置时间之前，需要禁止所有的中断0x24 int disable，设置rtc ctrl对应为禁止（使时钟停止自增）。

设置时间 0x4 time . 0x8 calr

判断时间是否设置成功 0x2c status 

清空事件产生标志 0x1c event flags ,设置中断使能0x20 int enable

重新使能 0x0 rtc ctrl



获取时间、日历

读0x8 0xc寄存器，判断时间模式12h/24h，是否需要+12h，

测试过程中可以先将时钟计数停止， 减少影响。



设置alarm

设置alarm之前，应该先禁止中断，设置的时间应当有效（12h、24h应该模式对应）

