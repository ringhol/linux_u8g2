#include "port_u8g2.h"
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>

unsigned char base_i2c_write(unsigned char device_addr, unsigned char *buff, int ByteNo){
    const char *i2c_dev = "/dev/i2c-0";
    int fd = open(i2c_dev, O_RDWR);
    struct i2c_rdwr_ioctl_data data;
    struct i2c_msg msgs_str[1];
    data.msgs = msgs_str;
    unsigned char sendbuf[255] = {0};
    data.nmsgs = 1;
    data.msgs[0].len = ByteNo;
    data.msgs[0].addr = device_addr;
    data.msgs[0].flags = 0;
    data.msgs[0].buf = sendbuf;
    memset(sendbuf, 0, 255);
    memcpy( sendbuf, buff, ByteNo);
    ioctl(fd,I2C_RDWR,&data);
    close(fd);
    return 1;
}


//延迟函数实现
uint8_t u8g2_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    const timespec t{0,100};
    timespec tm;
    switch(msg){
        //实现延迟函数
        case U8X8_MSG_DELAY_MILLI:
            usleep(arg_int*1000);
            break;
        case U8X8_MSG_DELAY_10MICRO:
            usleep(10);
            break;
        case U8X8_MSG_DELAY_100NANO:
            nanosleep(&t,&tm);
            break; 
        default:
            return 0;
    }
	return 1;
}


//硬件iic
uint8_t u8x8_byte_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *data;
  switch(msg)
  {
    case U8X8_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;      
      while( arg_int > 0 )
      {
        buffer[buf_idx++] = *data;
        data++;
        arg_int--;
      }      
      break;
    case U8X8_MSG_BYTE_INIT:
      /* add your custom code to init i2c subsystem */
      break;
    case U8X8_MSG_BYTE_SET_DC:
      /* ignored for i2c */
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:
      buf_idx = 0;
      break;
    case U8X8_MSG_BYTE_END_TRANSFER:
      //使用7位从机地址
      base_i2c_write(u8g2_GetI2CAddress(u8x8)>>1,buffer,buf_idx);
      break;
    default:
      return 0;
  }
  return 1;
}
