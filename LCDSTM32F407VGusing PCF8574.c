#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "i2c_lcd.h"
#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"

void gpioInit(void);
void i2cInit(void);
void delay(uint32_t t);
void lcd_PrintC(const uint8_t *str);

const uint8_t mes[] = "STM32F4 KALILOS";

int main(void)
{

	gpioInit();
	i2cInit();
	lcd_Init();
	lcd_PrintC(mes);
	lcd_Goto(2, 0);
	lcd_PrintC("LCD4x20 PCF8574");

    while(1) {}
}

void delay(uint32_t t) {
	uint32_t i = 0;
	for (; i < t; i++);
}

void gpioInit(void)
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &gpio);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
}

void i2cInit(void)
{
	I2C_InitTypeDef i2c;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	i2c.I2C_ClockSpeed = 100000;
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c.I2C_OwnAddress1 = 0x00;
	i2c.I2C_Ack = I2C_Ack_Enable;
	i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE);
}
