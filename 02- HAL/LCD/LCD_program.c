#include "ERROR_STATE.h"
#include "TYPES.h"

#include "DIO_interface.h"

#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD_interface.h"

#include "util/delay.h"



ES_t LCD_enuInit(void)
{
ES_t Local_enu_ErrorState = ES_NOK;

DIO_enuSetPinDirection(RS_PORT,RS_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(RW_PORT,RW_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(EN_PORT,EN_PIN,DIO_U8OUTPUT);

DIO_enuSetPinDirection(DB7_PORT,DB7_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(DB6_PORT,DB6_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(DB5_PORT,DB5_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(DB4_PORT,DB4_PIN,DIO_U8OUTPUT);

_delay_ms(POWER_ON_DELAY);
#if LCD_MODE ==FOUR_BIT
DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/
LCD_enuWriteNLatch(FUNCTION_SET_FOUR_BIT);
_delay_ms(FUNCTION_SET_DELAY);

#elif LCD_MODE == EIGHT_BIT
DIO_enuSetPinDirection(DB3_PORT,DB3_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(DB2_PORT,DB2_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(DB1_PORT,DB1_PIN,DIO_U8OUTPUT);
DIO_enuSetPinDirection(DB0_PORT,DB0_PIN,DIO_U8OUTPUT);

DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/
LCD_enuWriteNLatch(FUNCTION_SET_EIGHT_BIT);
_delay_ms(FUNCTION_SET_DELAY);
#endif

_delay_ms(FUNCTION_SET_DELAY);
DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/
LCD_enuWriteNLatch(DISPLAY_ON_OFF_BIT);

_delay_ms(FUNCTION_SET_DELAY);
DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/
LCD_enuWriteNLatch(DISPLAY_CLEAR_BIT);

_delay_ms(DISPLAY_CLEAR_DELAY);
DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/
LCD_enuWriteNLatch(ENTERY_MODE_BIT);
Local_enu_ErrorState= ES_OK;
return Local_enu_ErrorState;
}

ES_t LCD_enuSendData(U8 Copy_U8Data)
{
	ES_t Local_enu_ErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8HIGH ); /*Send data*/
	LCD_enuWriteNLatch(Copy_U8Data);


	return Local_enu_ErrorState;
}

ES_t LCD_enuSendCommand(U8 Copy_U8Command)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/

	LCD_enuWriteNLatch(Copy_U8Command);

	return Local_enu_ErrorState;
}


ES_t LCD_enuSendPosition(U8 Copy_U8Line, U8 Copy_U8Position)
{
	//U8 Copy_U8Iterator;
	ES_t Local_enu_ErrorState = ES_NOK;
	DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/
	switch (Copy_U8Line)
	{
	case 0 : LCD_enuWriteNLatch(FIRST_LINE+Copy_U8Position);
	break;

	case 1: LCD_enuWriteNLatch(SECOND_LINE+Copy_U8Position);
	break;

//	default:
	//#warning The LCD line position is incorrect
	}



/*	for(Copy_U8Iterator=1;Copy_U8Iterator<Copy_U8Position;Copy_U8Iterator++)
	{
		LCD_enuWriteNLatch(DISPLAY_POSITION_SHIFT);

	}
*/
	return Local_enu_ErrorState;
}



ES_t LCD_enuSendCustomCharacter(U8 * Copy_U8PArrCustomCharacter, U8 Copy_U8PatternsNumber,U8 Copy_U8XPosition, U8 Copy_U8YPosition, U8 Copy_U8Direction)
{
	ES_t Local_enu_ErrorState = ES_NOK;

	/****************DRAW THE CUSTOM CHARACTOR ON CGRAM*****************/

	U8 Local_U8Iterator;
	DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/

	LCD_enuWriteNLatch(FIRST_CGRAM_PATTERN); //First Pattern location in CGRAM


	for(Local_U8Iterator=0; Local_U8Iterator<PATTERMS_NUMBER_BITS;Local_U8Iterator++)
		{
			//LCD_enuWriteNLatch((Copy_U8PArrCustomCharacter[Local_U8Iterator]));

			//LCD_enuWriteNLatch((*Copy_U8PArrCustomCharacter+Local_U8Iterator));

			//LCD_enuWriteNLatch((U8*)(Copy_U8PArrCustomCharacter+Local_U8Iterator));

		DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8HIGH); /*Send data*/

			LCD_enuWriteNLatch(*(Copy_U8PArrCustomCharacter+Local_U8Iterator));

	}
/*****************************POSITION & DIRECTION****************************/

	DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8LOW); /*Send command*/

	if(Copy_U8XPosition>1||Copy_U8YPosition>16||Copy_U8PatternsNumber>8||Copy_U8Direction>1)
	{
		Local_enu_ErrorState=ES_NOK;
	}
	else
	{
		if (Copy_U8Direction) /*****************WRITING FROM LIFT TO RIGHT*******************/
		{
			switch  (Copy_U8XPosition)
			{
			case 0 : LCD_enuWriteNLatch(FIRST_LINE+Copy_U8YPosition);
			break;

			case 1: LCD_enuWriteNLatch(SECOND_LINE+Copy_U8YPosition);
			break;
			}
		}
		else /*****************WRITING FROM RIGHT TO LIFT*******************/
		{
			switch  (Copy_U8XPosition)
			{
			case 0 : LCD_enuWriteNLatch(END_FIRST_LINE-Copy_U8YPosition);
						LCD_enuWriteNLatch(RIGHT_TO_LEFT_DIRECTION);

			break;

			case 1: LCD_enuWriteNLatch(END_SECOND_LINE-Copy_U8YPosition);
						LCD_enuWriteNLatch(RIGHT_TO_LEFT_DIRECTION);

			break;
			}
		}
	}

	/*******************************PRINTING THE CUSTOM CHARACTERS*********************************/
	DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8HIGH ); /*Send data*/
	LCD_enuWriteNLatch(Copy_U8PatternsNumber);


	return Local_enu_ErrorState;

}

ES_t LCD_enuSendpcString(const char * Copy_pcString)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	while(*Copy_pcString) //true value as false =0 =='/0' Null character.
	{
		DIO_enuSetPinValue(RS_PORT,RS_PIN, DIO_U8HIGH ); /*Send String data*/
		LCD_enuWriteNLatch(* Copy_pcString++); //Adding incrementing operation.
	}
	return Local_enu_ErrorState;
}


static ES_t LCD_enuWriteNLatch(U8 Copy_U8Data) /*Static local function to make falling edge high then low*/
{
	ES_t Local_enu_ErrorState = ES_NOK;


DIO_enuSetPinValue(RW_PORT,RW_PIN, DIO_U8LOW ); /*Write data*/
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8LOW);/*Enable is low*/

/***********************DATA WRITE******************/
/*******************Condition for function set step*********/
if (Copy_U8Data == FUNCTION_SET_FOUR_BIT)
{
	U8 Local_U8RS_Value;
	DIO_enuGetPinValue(RS_PORT,RS_PIN,&Local_U8RS_Value);

if(Local_U8RS_Value==DIO_U8LOW)
{
	/*******************************Pins from 7 to 4*********************/

	DIO_enuSetPinValue(DB7_PORT, DB7_PIN,((Copy_U8Data>>BIT_NUMBER_7)&BIT_MASK_MOVE));
	DIO_enuSetPinValue(DB6_PORT, DB6_PIN,((Copy_U8Data>>BIT_NUMBER_6)&BIT_MASK_MOVE));
	DIO_enuSetPinValue(DB5_PORT, DB5_PIN,((Copy_U8Data>>BIT_NUMBER_5)&BIT_MASK_MOVE));
	DIO_enuSetPinValue(DB4_PORT, DB4_PIN,((Copy_U8Data>>BIT_NUMBER_4)&BIT_MASK_MOVE));

	/*******************************LATCH *************************/
	DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8HIGH);/*Enable is HIGH*/
	_delay_ms(LATCH_DELAY);
	//_delay_us();
	DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8LOW);/*Enable is low*/
	_delay_ms(LATCH_DELAY);

	/*******************************LATCH  END*********************/

}
}
/********************Check the LCD MODE**************/
#if LCD_MODE == FOUR_BIT
/***************************************************************/

/*******************************Pins from 7 to 4*********************/

DIO_enuSetPinValue(DB7_PORT, DB7_PIN, ((Copy_U8Data>>BIT_NUMBER_7)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB6_PORT, DB6_PIN, ((Copy_U8Data>>BIT_NUMBER_6)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB5_PORT, DB5_PIN, ((Copy_U8Data>>BIT_NUMBER_5)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB4_PORT, DB4_PIN, ((Copy_U8Data>>BIT_NUMBER_4)&BIT_MASK_MOVE));

/*******************************LATCH *************************/
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8HIGH);/*Enable is HIGH*/
_delay_ms(LATCH_DELAY);
//_delay_us();
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8LOW);/*Enable is low*/
_delay_ms(LATCH_DELAY);

/*******************************LATCH  END*********************/
/*******************************Pins from 3 to 0*********************/

DIO_enuSetPinValue(DB7_PORT, DB7_PIN,((Copy_U8Data>>BIT_NUMBER_3)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB6_PORT, DB6_PIN,((Copy_U8Data>>BIT_NUMBER_2)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB5_PORT, DB5_PIN,((Copy_U8Data>>BIT_NUMBER_1)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB4_PORT, DB4_PIN,((Copy_U8Data>>BIT_NUMBER_0)&BIT_MASK_MOVE));

/*******************************LATCH *************************/
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8HIGH);/*Enable is HIGH*/
_delay_ms(LATCH_DELAY);
//_delay_us();
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8LOW);/*Enable is low*/
_delay_ms(LATCH_DELAY);

/*******************************LATCH  END*********************/


#elif LCD_MODE == EIGHT_BIT
/****************************************************/
/*******************************Pins from 7 to 0*********************/

DIO_enuSetPinValue(DB7_PORT, DB7_PIN,((Copy_U8Data>>BIT_NUMBER_7)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB6_PORT, DB6_PIN,((Copy_U8Data>>BIT_NUMBER_6)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB5_PORT, DB5_PIN,((Copy_U8Data>>BIT_NUMBER_5)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB4_PORT, DB4_PIN,((Copy_U8Data>>BIT_NUMBER_4)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB3_PORT, DB3_PIN,((Copy_U8Data>>BIT_NUMBER_3)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB2_PORT, DB2_PIN,((Copy_U8Data>>BIT_NUMBER_2)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB1_PORT, DB1_PIN,((Copy_U8Data>>BIT_NUMBER_1)&BIT_MASK_MOVE));
DIO_enuSetPinValue(DB0_PORT, DB0_PIN,((Copy_U8Data>>BIT_NUMBER_0)&BIT_MASK_MOVE));

/*******************************LATCH *************************/
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8HIGH);/*Enable is HIGH*/
_delay_ms(LATCH_DELAY);
//_delay_us();
DIO_enuSetPinValue(EN_PORT,EN_PIN, DIO_U8LOW);/*Enable is low*/
_delay_ms(LATCH_DELAY);

/*******************************LATCH  END*********************/



#else
#error "LCD_MODE you have entered is wrong, please correct it."
#endif


return Local_enu_ErrorState;
}

ES_t LCD_enuDisplayIntegerNum(S32 Copy_S32Num)
{
	ES_t Local_enuErrorState = ES_NOK;

	S32 Local_S32Reverse=0;
	U8 Local_u8Remainder=0 , Local_u8NumDigit=0;

	if(Copy_S32Num <0)
	{
		DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_U8HIGH);
		LCD_enuWriteNLatch('-');
		Copy_S32Num *= -1 ;
	}
	while (Copy_S32Num)
	{
		Local_u8Remainder = Copy_S32Num % 10;
		Local_S32Reverse = Local_S32Reverse * 10 + Local_u8Remainder;
		Copy_S32Num /=10;
		Local_u8NumDigit ++;
	}

	while (Local_u8NumDigit)
	{
		Local_u8Remainder = Local_S32Reverse % 10;
		DIO_enuSetPinValue(RS_PORT , RS_PIN , DIO_U8HIGH);
		LCD_enuWriteNLatch(Local_u8Remainder + '0');
		Local_S32Reverse /= 10;
		Local_u8NumDigit --;
	}

	return Local_enuErrorState;
}
ES_t LCD_enuClearDisplay( void )
{

	ES_t Local_enuerrorStates = ES_NOK;

		Local_enuerrorStates = DIO_enuSetPinValue(RS_PORT, RS_PIN , DIO_U8LOW);
		LCD_enuWriteNLatch(0x01);

	return Local_enuerrorStates;

}
