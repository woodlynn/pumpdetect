
#ifndef __lcd_h
#define __lcd_h


extern void InitLCD(void);
extern void ConvertNum(uint8_t InputNum) ;
extern void LCD_Write(uint8_t Position ,uint8_t Num) ;
extern void Display();
extern void data_convertor(unsigned long adc_value) ;
extern void Display_lcd_dot(void) ;
#endif