# TTC

## Interval模式, 计数器递增
----
`FPGA` `RTL` `P0`

**Description**
1. 在Interval模式下，计数器配置成递增，设置1s后产生中断
1. Lorem ipsum dolor sit amet

**Expectation**
1. 能正常中断，打印Test Interval Timing, Incrementing count Pass
1. Lorem ipsum dolor sit amet

**FPGA&RTL Params**
```
ttc -c 0 -m 0 -r 1  # can add some comment in line
ttc -c 1 -m 0 -r 1
ttc -c 2 -m 0 -r 1
```

## Interval模式, 计数器递减
----
`RTL` `P1`

**Description**
1. 在Interval模式下，计数器配置成递增，设置1s后产生中断
1. Lorem ipsum dolor sit amet

**Expectation**
1. 能正常中断，打印Test Interval Timing, Incrementing count Pass
1. Lorem ipsum dolor sit amet

**FPGA&RTL Params**
```
ttc -c 0 -m 0 -r 1
ttc -c 1 -m 0 -r 1
ttc -c 2 -m 0 -r 1
```

