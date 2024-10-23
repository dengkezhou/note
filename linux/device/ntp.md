参考文档：https://cloud.tencent.com/developer/article/2361936

NTP，Network Time Protocol 网络时间协议，是一种用于计算机网络同步设备时钟协议。

NTP主要目标是确保网络中的各个设备都有一致的时间参考，以便它们可以协同工作，进行时间戳记录、数据同步和各种计算任务。

NTP采用分层结构来确保时间同步，使网络中所有设备都能获取准确的时间信息。

### 一、配置NTP服务器

https://blog.csdn.net/qq943618691/article/details/132223843

以 ubuntu 为例

```shell
sudo apt update
sudo apt install ntp
```

