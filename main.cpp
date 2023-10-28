#include "port_u8g2.h"
#include <iostream>
u8g2_t display;
int main(int argc,char* argv[]){
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&display,U8G2_R0,u8x8_byte_i2c,u8g2_gpio_and_delay);
  u8g2_InitDisplay(&display);
  u8g2_ClearDisplay(&display);
  u8g2_SetPowerSave(&display,0);
  u8g2_SetFont(&display,u8g2_font_wqy12_t_chinese1);
  if(argc==1){
    return 0;
  }
  u8g2_DrawUTF8(&display,0,20,argv[1]);
  u8g2_SendBuffer(&display);
}