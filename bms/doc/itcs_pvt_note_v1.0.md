# PVT相关接口说明

## 头文件

```c
#include <pvt.h>
```

## 接口说明

* pvt通道初始化

  ```c 
    pvt_device_t *itcs_pvt_init(uint32_t channel)
  ```

  | 参数名  | 参数说明                       |
  | ------- | ------------------------------ |
  | channel | pvt通道号0~7                   |

  | 返回值         | 返回值说明       |
  | -------------- | ---------------- |
  | pvt_device_t * | 返回通道句柄 |

* 读取pvt的data_out值

  ```c 
    uint32_t itcs_pvt_read(pvt_device_t *dev);
  ```

  | 参数名 | 参数说明               |
  | ------ | ---------------------- |
  | dev    | 通道句柄               |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | int    | 返回pvt的数值可读状态         |

* pvt通道模式配置

  ```c 
    void itcs_pvt_mode_config(pvt_device_t *dev, uint32_t mode, uint32_t prmode);
  ```

  | 参数名  | 参数说明                        |
  | ------- | ------------------------------ |
  | dev     | 通道句柄                       |
  | mode    | pvt的Temperature、Voltage、Process模式(0、1、2)                |
  | prmode  | pvt process下LVT、ULVT、SVT模式(0、1、2)   |

  | 返回值         | 返回值说明       |
  | -------------- | ---------------- |
  | none           | --         |

* 获取pvt可读性

  ```c 
    int itcs_pvt_get_status(pvt_device_t *dev);
  ```

  | 参数名 | 参数说明               |
  | ------ | ---------------------- |
  | dev    | 通道句柄               |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | int   | 返回读取到的data_out值         |

* 读取pvt的data_out值

  ```c 
    uint32_t itcs_pvt_read(pvt_device_t *dev);
  ```

  | 参数名 | 参数说明               |
  | ------ | ---------------------- |
  | dev    | 通道句柄               |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | uint32_t   | 返回读取到的data_out值         |

* 开启pvt通道

  ```c 
    void itcs_pvt_start(pvt_device_t *dev);
  ```

  | 参数名 | 参数说明          |
  | ------ | ----------------- |
  | dev    | 通道句柄          |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |

* 关闭pvt通道

  ```c 
    void itcs_pvt_stop(pvt_device_t *dev)
  ```

  | 参数名 | 参数说明 |
  | ------ | -------- |
  | dev    | 通道句柄 |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |

* 去初始化

  ```c 
    void itcs_pvt_deinit(pvt_device_t *dev);
  ```

  | 参数名 | 参数说明 |
  | ------ | -------- |
  | dev    | 通道句柄 |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |