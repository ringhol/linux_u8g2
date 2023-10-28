
# 在linux上的u8g2

在旭日派上成功驱动ssd1306，其他oled屏幕驱动都可以同理移植。

port_u8g2.cpp中实现了iic的通信和linux上延时函数，硬件iic只需要完成这两部即可，main.cpp中有一个示例
