#ifndef _HAL_LCD_CONFIG_H_
#define _HAL_LCD_CONFIG_H_
/*------------------------- MODE OF OPERATION ---------------------------------*/
#define LCD_MODE						FOUR_BIT

/**************** Control Pins ***************/
#define	RS_PORT							DIO_U8PORT_A
#define RS_PIN							DIO_U8PIN3
#define NAME_LENGHT						60
#define	RW_PORT							DIO_U8PORT_A
#define RW_PIN							DIO_U8PIN2

#define	EN_PORT							DIO_U8PORT_A
#define EN_PIN							DIO_U8PIN1
/*************** Data Pins *****************/

#define DB7_PORT				DIO_U8PORT_A
#define DB7_PIN					DIO_U8PIN7

#define DB6_PORT				DIO_U8PORT_A
#define DB6_PIN					DIO_U8PIN6

#define DB5_PORT				DIO_U8PORT_A
#define DB5_PIN					DIO_U8PIN5

#define DB4_PORT				DIO_U8PORT_A
#define DB4_PIN					DIO_U8PIN4

#define DB3_PORT				DIO_U8PORT_A
#define DB3_PIN					DIO_U8PIN3

#define DB2_PORT				DIO_U8PORT_A
#define DB2_PIN					DIO_U8PIN2

#define DB1_PORT				DIO_U8PORT_A
#define DB1_PIN					DIO_U8PIN1

#define DB0_PORT				DIO_U8PORT_A
#define DB0_PIN					DIO_U8PIN0

#define FIRST_LINE											 0x80
#define SECOND_LINE									 		 0xc0
#define END_FIRST_LINE									     0x8f
#define END_SECOND_LINE										 0xcf
#define FIRST_CGRAM_PATTERN  								 0x40
#define RIGHT_TO_LEFT_DIRECTION 							 0x04
#define PATTERMS_NUMBER_BITS  								 64



#endif /* _HAL_LCD_CONFIG_H_ */
