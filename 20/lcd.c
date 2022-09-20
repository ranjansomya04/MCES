#include <lpc214x.h>
#define PLOCK 0x00000400
#define LED_OFF (IO0SET = 1U << 31)
#define LED_ON (IO0CLR = 1U << 31)
#define RS_ON (IO0SET = 1U << 20)
#define RS_OFF (IO0CLR = 1U << 20)
#define EN_ON (IO1SET = 1U << 25)
#define EN_OFF (IO1CLR = 1U << 25)
void SystemInit(void);
static void delay_ms(unsigned int j);
static void delay_us(unsigned int count);
static void LCD_SendCmdSignals(void);
static void LCD_SendDataSignals(void);
static void LCD_SendHigherNibble(unsigned char dataByte);
static void LCD_CmdWrite( unsigned char cmdByte);
static void LCD_DataWrite( unsigned char dataByte);
static void LCD_Reset(void);
static void LCD_Init(void);
void LCD_DisplayString(const char *ptr_stringPointer_u8);
int main()
{
	SystemInit();
	IO0DIR |= 1U << 31 | 0x00FF0000 ;
	IO1DIR |= 1U << 25;
	LED_ON; delay_ms(500); LED_OFF; delay_ms(500);
	LCD_Reset();
	LCD_Init();
	delay_ms(100);
	LCD_CmdWrite(0x80); LCD_DisplayString("RV College Of Engrng");
	LCD_CmdWrite(0xc0); LCD_DisplayString(" Computer Sciene");
	LCD_CmdWrite(0x94); LCD_DisplayString(" 4th Semester");
	LCD_CmdWrite(0xD4); LCD_DisplayString(" B Section");
	while (1);
}
static void LCD_CmdWrite( unsigned char cmdByte)
{
	LCD_SendHigherNibble(cmdByte);
	LCD_SendCmdSignals();
	cmdByte = cmdByte << 4;
	LCD_SendHigherNibble(cmdByte);
	LCD_SendCmdSignals();
}

LPC 2148 Microcontroller Interfacing - ©Copyrights, Dr K Badari Nath, RVCE, Feb2020 Page 24
static void LCD_DataWrite( unsigned char dataByte)
{
	LCD_SendHigherNibble(dataByte);
	LCD_SendDataSignals();
	dataByte = dataByte << 4;
	LCD_SendHigherNibble(dataByte);
	LCD_SendDataSignals();
}
static void LCD_Reset(void)
{
	LCD_SendHigherNibble(0x30);
	LCD_SendCmdSignals();
	delay_ms(100);
	LCD_SendHigherNibble(0x30);
	LCD_SendCmdSignals();
	delay_us(200);
	LCD_SendHigherNibble(0x30);
	LCD_SendCmdSignals();
	delay_us(200);
	LCD_SendHigherNibble(0x20);
	LCD_SendCmdSignals();
	delay_us(200);
}
static void LCD_SendHigherNibble(unsigned char dataByte)
{
	IO0CLR = 0X000F0000; IO0SET = ((dataByte >> 4) & 0x0f) << 16;
}
static void LCD_SendCmdSignals(void)
{
	RS_OFF;
	EN_ON; delay_us(100); EN_OFF;
}
static void LCD_SendDataSignals(void)
{
	RS_ON;
	EN_ON; delay_us(100); EN_OFF;
}
static void LCD_Init(void)
{
	delay_ms(100);
	LCD_Reset();
	LCD_CmdWrite(0x28u);
	LCD_CmdWrite(0x0Eu);
	LCD_CmdWrite(0x01u);
	LCD_CmdWrite(0x80u);
}

LPC 2148 Microcontroller Interfacing - ©Copyrights, Dr K Badari Nath, RVCE, Feb2020 Page 25
void LCD_DisplayString(const char *ptr_string)
{
	while ((*ptr_string) != 0)
		LCD_DataWrite(*ptr_string++);
}
static void delay_us(unsigned int count)
{
	unsigned int j = 0, i = 0;
	for (j = 0; j < count; j++)
	{
		for (i = 0; i < 10; i++);
	}
}
void SystemInit(void)
{
	PLL0CON = 0x01;
	PLL0CFG = 0x24;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	while ( !( PLL0STAT & PLOCK ))
	{ ; }
	PLL0CON = 0x03;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	VPBDIV = 0x01;
}
void delay_ms(unsigned int j)
{
	unsigned int x, i;
	for (i = 0; i < j; i++)
	{
		for (x = 0; x < 10000; x++);
	}
}