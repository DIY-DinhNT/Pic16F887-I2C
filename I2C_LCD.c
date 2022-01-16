#DEFINE PCF_ADDRES_WRITE   0x7E //dia chi pcf8574 (pcf8574A 7E) or 4e

#DEFINE LCD_BACKLIGHT      0x08 // bat den nen
#DEFINE LCD_NO_BACKLIGHT   0x00

#DEFINE FUNCTION_SET       0X28  // GIAO TIEP 4 BIT 2 HANG
#DEFINE DISPLAY_CONTROL    0X0C
#DEFINE CLEAR_DISPLAY      0X01 // XOÁ MÀN HÌNH LCD
#DEFINE ENTRY_MODE         0X06  //CHO PHEP XUAT NHAP DU LIEU

#DEFINE ADDR_LINE1         0X80 
#DEFINE ADDR_LINE2         0XC0 
void LCD_I2C_COMMAND(char MDK) 
{
   int MS_BIT_E, LS_BIT_E, MS_DATA, LS_DATA;
   
   MS_DATA = MDK & 0xF0;      // lay 4 bit cao
   LS_DATA = MDK & 0x0F;      // lay 4 bit thap

   SWAP(LS_DATA);                   

   MS_BIT_E =  MS_DATA | 0x04;  // tao xung clock cap vao chan E
   LS_BIT_E =  LS_DATA | 0x04;    
   
   I2C_START();
   I2C_WRITE(PCF_ADDRES_WRITE); 
     
   I2C_WRITE(MS_BIT_E);        // LUC NAY SE XUAT CAR MS_DATA VA 3 GIA TRI E=1,RW=0,RS=0    
   I2C_WRITE(MS_DATA);         //LUC NAY CHI XUAT MS_DATA, E=0,RW=0,RS=0    
   
   I2C_WRITE(LS_BIT_E );            
   I2C_WRITE(LS_DATA);             
   I2C_WRITE(LCD_BACKLIGHT);    
   I2C_STOP();
   DELAY_US(440); 
}
void LCD_I2C_DATA(char MHT) 
{
   int MS_BIT_E, LS_BIT_E, MS_DATA, LS_DATA;
   MS_DATA = MHT & 0xF0;      
   LS_DATA = MHT & 0x0F;   

   SWAP(LS_DATA);    
   MS_DATA++;             // luôn du cho rs o muc 1   
   LS_DATA++; 
   MS_BIT_E = MS_DATA | 0x05;   
   LS_BIT_E = LS_DATA | 0x05;    
   
   I2C_START();
   I2C_WRITE(PCF_ADDRES_WRITE);
     
   I2C_WRITE(MS_BIT_E);        // LUC NAY SE XUAT CAR MS_DATA VA 3 GIA TRI E=1,RW=0,RS=1    
   I2C_WRITE(MS_DATA);               
   
   I2C_WRITE(LS_BIT_E );            
   I2C_WRITE(LS_DATA);                
   i2c_write(LCD_BACKLIGHT);    
   I2C_STOP();
   DELAY_US(440); 
}
void SETUP_I2C_LCD()
{
   I2C_START();
   I2C_WRITE(PCF_ADDRES_WRITE);
   I2C_WRITE(0x2C);                 
   I2C_WRITE(0x28); 
   LCD_I2C_COMMAND(0x28);DELAY_MS(1);
   LCD_I2C_COMMAND(0x0C);DELAY_MS(2);
   LCD_I2C_COMMAND(0x06);DELAY_MS(2);
   I2C_STOP();
   DELAY_US(440);  
}
VOID LCD_GOTO_XY(SIGNED INT8 X, SIGNED INT8 Y)
{ 
   CONST UNSIGNED INT8 LCD_VITRI[]={0x80,0xC0,0x94,0xD4};
   lcd_i2c_command(LCD_VITRI[X]+Y);
   delay_us(440); 
}


