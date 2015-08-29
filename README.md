# OpenTel_Mavlink
Mavlink C


；-----------------------------------------------------------------------------------------------------------
1、Mavlink keil MDK c 版本。
2、主控为stm32f0xx，当前占用flash 约6k。
3、底层串口使能收发中断。Mavlink message 直接读写串口收发缓冲区。

4、目前实现功能:
  1)接收校验Mavlink数据包。
  2)发送Heardbeat、AHRS、Attitude数据包。
  
Note
  1)添加新数据包前，需更新CRC数组。

