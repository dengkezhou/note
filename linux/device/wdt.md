wdt

## 概述

wdt, watchdog timer，看门狗，是一个定时器电路，一般用做防止系统锁死。

正常情况下，用户应该周期性的复位wdt，保证wdt 计时器不会减到0。

**Watchdog Interface**: wdt计时器减到0时，会产生一个或一组信号（Watchdog Interface Out）： 系统复位wd_rst_n、中断wd_irq、外部信号ex_wdz_n。 (Watchdog Interface In)cpu_debug ，当cpu delay时，也停止计数。



