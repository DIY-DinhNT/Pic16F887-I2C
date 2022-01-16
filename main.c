#include <main.h>
#include "math.h"
#include "I2C_LCD.c"

void main()
{

   while(TRUE)
   {
     SETUP_I2C_LCD();
     LCD_I2C_COMMAND(0x80) ;
     LCD_I2C_DATA(" DinhNT DIY ") ;
     LCD_I2C_COMMAND(0xC0) ;
     LCD_I2C_DATA(" Electronic ") ;
     LCD_GOTO_XY(2,0);
     LCD_I2C_DATA(" Dinh Nguyen ") ;
     delay_ms(50);
    }

}
