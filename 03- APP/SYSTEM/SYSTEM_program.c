#include "TYPES.h"
#include "ERROR_STATE.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SWITCH_config.h"
#include "SWITCH_interface.h"

#include "ADC_interface.h"

#include "TIMER_interface.h"

#include "EXTI_config.h"
#include "EXTI_interface.h"


#include "GIE_interface.h"


//#include "I2C_interface.h"
#include "EEPROM_interface.h"

#include "SEVENSEGMENT_config.h"
#include "SEVENSEGMENT_interface.h"

#include "LCD_interface.h"

#include "LED_SYSTEM_interface.h"

#include "HEAT_COOL_Elements_interface.h"

#include "TEMP_SENSOR_interface.h"

#include "interrupt.h"

#include "SYSTEM_private.h"
#include "SYSTEM_interface.h"

#include "util/delay.h"


extern EXTI_t EXTI_AstrEXTIConfig[INT_NUM];
extern SSG_t SEVENSEGMENT_AstrSevenSegmentConfig [SSG_NUMBER];
extern SW_t SWITCH_AstrSwitchConfig [SW_NUM];
extern U32 Global_32_tTIMER1_CTCA_SecondsCounter;
extern U16 Global_U16Timer0CTC_OneSecondCounter;
U16 Global_U16TempRead,Global_U16Five_SecondToggleFlag,Global_U16One_SecondToggleFlag, Global_U16AverageTemp,Global_U16DesiredTemp,Global_U16Five_SecondCounter=0;
U16 Global_AU16TempArr[NUM_OF_TEMP_MEASURES];
U8  Global_U8CurrentState,Global_U8TempMeasureFlag,Global_U8ReadData,Global_U8ArrCounter,Global_U8UPSwitchFlag,Global_U8DOWNSwitchFlag;


ES_t SYSTEM_enuGetTemp(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	U8 Local_U8Iterator;
	U16 Local_U16FirstTempReading;

	TempSensor_enuGetTempReading(&Local_U16FirstTempReading);

	for (Local_U8Iterator = 0; Local_U8Iterator<NUM_OF_TEMP_MEASURES; Local_U8Iterator++)
	{
		Global_AU16TempArr[Local_U8Iterator]= Local_U16FirstTempReading;
	}

	Global_U8ArrCounter=0;

	return Local_enuErrorState;
}


ES_t SYSTEM_enuCalculateAverateTemp(U16 * Copy_pU16AstrTempReadings, U16 * Copy_U16ReturnTempValue)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	U16 Local_U16SumOfReadings = ZERO_VALUE;
	U16 Local_U16AverageOfReadings;
	U8 Local_U8Iterator;

	for(Local_U8Iterator=0; Local_U8Iterator<NUM_OF_TEMP_MEASURES; Local_U8Iterator++){
		Local_U16SumOfReadings = Local_U16SumOfReadings + Copy_pU16AstrTempReadings[Local_U8Iterator];

	}
	Local_U16AverageOfReadings = (U16) Local_U16SumOfReadings / NUM_OF_TEMP_MEASURES;
	* Copy_U16ReturnTempValue=Local_U16AverageOfReadings;
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}

ES_t SYSTEM_enuAddNewTemp(U16 * Copy_pU16AstrTempReadings, U16 Copy_U16AddedTempValue)
{
	ES_t Local_enuErrorState = ES_NOK;
	U8 Local_U8Iterator;
	for(Local_U8Iterator=ZERO_VALUE;Local_U8Iterator<NUM_OF_TEMP_MEASURES;Local_U8Iterator++)
	{
		Copy_pU16AstrTempReadings [Global_U8ArrCounter] =Copy_U16AddedTempValue;
		_delay_ms(100);
		Global_U8ArrCounter++;
		if(Global_U8ArrCounter==NUM_OF_TEMP_MEASURES)
			{
				Global_U8ArrCounter=ZERO_VALUE;
			}
	}

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}



ES_t SYSTEM_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuInit();
	EXTI_enuInit(EXTI_AstrEXTIConfig);
	SevenSegment_enuInit( SEVENSEGMENT_AstrSevenSegmentConfig);
	SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[0]);
	SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[1]);
	SWITCH_enuIniti(SWITCH_AstrSwitchConfig);
	LCD_enuInit();
	HEAT_COOL_ELEMENTS_enuIniti();
	LED_SYSTEM_enuIniti();
	TIMER0_enuInit();
	TIMER1_enuInit();
	TIMER2_enuInit();


	TempSensor_enuInit();
	GIE_enu_Init();
	EXTI_enuEnableInterrupt(TEMP_UP_SWITCH);
	EXTI_enuEnableInterrupt(TEMP_DOWN_SWITCH);
	EXTI_enuEnableInterrupt(ON_OFF_SWITCH);
	TIMER0_enuInterruptEnable();
	TIMER1_enuInterruptEnable();
	TIMER2_enuInterruptEnable();

	GIE_enu_Enable();
	TIMER0_enuStartTimer();
	TIMER1_enuStartTimer();
	TIMER2_enuStartTimer();

	DIO_enuSetPinDirection(DIO_U8PORT_B,DIO_U8PIN3,DIO_U8OUTPUT);
	DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN4,DIO_U8OUTPUT);

	DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN5,DIO_U8OUTPUT);
	DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN7,DIO_U8OUTPUT);


	Global_U8CurrentState = OFF_STATE;
	Global_U8UPSwitchFlag = NOT_RISED;
	Global_U8DOWNSwitchFlag = NOT_RISED;

	SYSTEM_enuGetTemp();

	/*---------- PROJECT Message ----------*/
	LCD_enuSendCommand(FIRST_LINE);
	LCD_enuSendpcString("      AMON      ");
	LCD_enuSendCommand(SECOND_LINE);
	LCD_enuSendpcString("      GROUP     ");
	_delay_ms(15000);
	LCD_enuSendCommand(FIRST_LINE);
	LCD_enuSendpcString("Welcome to AMIT");
	LCD_enuSendCommand(SECOND_LINE);
	LCD_enuSendpcString("graduation Proj.");
	_delay_ms(15000);
	LCD_enuSendCommand(FIRST_LINE);
	LCD_enuSendpcString("ELECTRIC WATER");
	LCD_enuSendCommand(SECOND_LINE);
	LCD_enuSendpcString("HEATER SYSTEM   ");
	_delay_ms(15000);
	/*---------- PROJECT Message ----------*/


	//setting initial temp. and fill array
	EEPROM_enuReadByteFromAddress(0x0000,&Global_U8ReadData);
	if(Global_U8ReadData != 0xFF)
		{
			Global_U16DesiredTemp = Global_U8ReadData;
		}
	else
		{
			Global_U16DesiredTemp = 60;
		}
	// Save desired temp in EEPROM, which is the INITIAL_DESIRED_TEMP.

	EEPROM_enuWriteByteToAddress(0x0000,Global_U16DesiredTemp);

	/*---------- Welcome Message ----------*/

	//LCD_enuSendCommand(SECOND_LINE+13);
	//LCD_enuDisplayIntegerNum(Global_U16DesiredTemp);
	LCD_enuSendCommand(FIRST_LINE);
	LCD_enuSendpcString("                   ");
	LCD_enuSendCommand(SECOND_LINE);
	LCD_enuSendpcString("SAVED Temp =   C");
	LCD_enuSendCommand(SECOND_LINE +13);
	LCD_enuDisplayIntegerNum(Global_U16DesiredTemp);
	_delay_ms(15000);
	return Local_enuErrorState;
}


void SYSTEM_vTogSevenSeg (void)
{
	SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[0]);
	SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[1]);

}


ES_t LED_SYSTEM_enuSystemToggle(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */

	if (Global_U8CurrentState==ON_STATE && (Global_U16DesiredTemp > Global_U16AverageTemp - FIVE_TEMP_DEGREE))
	{
		LED_SYSTEM_enuLedToggle();
		if  (Global_U16DesiredTemp < Global_U16AverageTemp + FIVE_TEMP_DEGREE)
		{
			LED_SYSTEM_enuLedStop();

		}
	}
	else if(Global_U8CurrentState==SETTINT_STATE)
	{
		SYSTEM_vTogSevenSeg();

	}
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;

}

ES_t SYSTEM_enuChangeTemp(void){
	ES_t Local_enu_ErrorState = ES_NOK;
	/*SYSTEM IN IDLE STATE NO NEED FOR ACTION*/
	if( (Global_U16DesiredTemp < Global_U16AverageTemp + FIVE_TEMP_DEGREE) && (Global_U16DesiredTemp > Global_U16AverageTemp - FIVE_TEMP_DEGREE) )
	{
		// Actual Temperature is in ten degree range of the Desired set Temperature
		// Neither Heating or Cooling Systems are needed
		HEAT_COOL_ELEMENTS_enuHeaterStop();
		HEAT_COOL_ELEMENTS_enuCoolerStop();
		LED_SYSTEM_enuLedStop();
	}

	else if(Global_U16DesiredTemp < Global_U16AverageTemp + FIVE_TEMP_DEGREE)
	{
		// Actual Temperature is Higher than the saved desired temperature
		// The Cooling system is needed

		HEAT_COOL_ELEMENTS_enuHeaterStop();
		HEAT_COOL_ELEMENTS_enuCoolerStart();
		LED_SYSTEM_enuLedStart();

	}
	else if (Global_U16DesiredTemp > Global_U16AverageTemp - FIVE_TEMP_DEGREE)
	{
		// Actual Temperature is Lower than the saved desired temperature
		// The Heating system is needed

		HEAT_COOL_ELEMENTS_enuCoolerStop();
		HEAT_COOL_ELEMENTS_enuHeaterStart();
		
		/*------------------ TOGGLE THE LED EVERY ONE SECOND -----------------*/
		TIMER0_enuSetCallBackDelay(( void (*) (void))LED_SYSTEM_enuSystemToggle,TIMER0_CTC_INDEX,TIMER0_DELAY_ONE_SECOND);

	
	}
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}


ES_t SYSTEM_enuOnState(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	U16 Local_U16NewTempReading;

	SevenSegment_enuEnableCommon(SEVENSEGMENT_AstrSevenSegmentConfig);

	TempSensor_enuGetTempReading(&Local_U16NewTempReading);

	SYSTEM_enuAddNewTemp(Global_AU16TempArr,Local_U16NewTempReading);
	SYSTEM_enuCalculateAverateTemp(Global_AU16TempArr, &Global_U16AverageTemp);

	LCD_enuSendCommand(FIRST_LINE);
	LCD_enuSendpcString("NORMAL MODE ON  ");
	LCD_enuSendCommand(SECOND_LINE);
	LCD_enuSendpcString("Actual Temp=   C");
	LCD_enuSendCommand(SECOND_LINE +13);
	LCD_enuDisplayIntegerNum(Global_U16AverageTemp);
	SevenSegment_Write(Global_U16AverageTemp);
	SYSTEM_enuChangeTemp();

	/*------------------- Listen for the UP|DOWN SWITCHES IF CHANGE OCCURES
	 *------------------- THEN, CHANGE THE CURRENT STATE MODE -------------------------*/

	if(Global_U8UPSwitchFlag==RISED||Global_U8DOWNSwitchFlag ==RISED)
	{

		Global_U8CurrentState= SETTINT_STATE;
		Global_U8UPSwitchFlag=NOT_RISED;
		Global_U8DOWNSwitchFlag=NOT_RISED;
		LCD_enuSendCommand(FIRST_LINE);
		LCD_enuSendpcString("                ");
		LCD_enuSendCommand(SECOND_LINE);
		LCD_enuSendpcString("                ");

		LCD_enuSendCommand(FIRST_LINE);
		LCD_enuSendpcString("Welcome to the  ");
		LCD_enuSendCommand(SECOND_LINE);
		LCD_enuSendpcString("Setting Mode    ");
		_delay_ms(15000);
	}

	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;

}

void SYSTEM_vFiveSecondsInSettingMode(void)
{
		if (Global_U16Five_SecondToggleFlag ==1 && Global_U8CurrentState == SETTINT_STATE)
		{
			Global_U8CurrentState = ON_STATE;
			Global_U16Five_SecondToggleFlag=0;
		}
		
}
ES_t SYSTEM_enuSettingState(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	HEAT_COOL_ELEMENTS_enuCoolerStop();
	HEAT_COOL_ELEMENTS_enuHeaterStop();
	LED_SYSTEM_enuLedStop();
	LCD_enuSendCommand(FIRST_LINE);
	LCD_enuSendpcString("Setting Mode On   ");
	LCD_enuSendCommand(SECOND_LINE);
	LCD_enuSendpcString("Desired Temp=   C ");
	LCD_enuSendCommand(SECOND_LINE+13);
	LCD_enuDisplayIntegerNum(Global_U16DesiredTemp);
	SevenSegment_Write(Global_U16DesiredTemp);
	_delay_ms(15000);

	if (Global_U8UPSwitchFlag == RISED && (Global_U16DesiredTemp < MAXIMUM_TEMP))
	{
		Global_U16DesiredTemp = Global_U16DesiredTemp + FIVE_TEMP_DEGREE;
		SevenSegment_Write(Global_U16DesiredTemp);
		Global_U8UPSwitchFlag=NOT_RISED;

	}

	else if (Global_U8DOWNSwitchFlag == RISED && (Global_U16DesiredTemp > MINIMUM_TEMP))
		{
			Global_U16DesiredTemp = Global_U16DesiredTemp - FIVE_TEMP_DEGREE;
			SevenSegment_Write(Global_U16DesiredTemp);
			Global_U8DOWNSwitchFlag= NOT_RISED;
		}
	if (Global_U8DOWNSwitchFlag == NOT_RISED && Global_U8UPSwitchFlag == NOT_RISED)
	{
		TIMER1_enuSetCallBackDelay((void (*)(void))SYSTEM_vFiveSecondsInSettingMode, TIMER_CTC1A_INTERRUPT_INDEX, TIMER1_DELAY_FIVE_SECONDS);

	}

	EEPROM_enuWriteByteToAddress(0x0000,Global_U16DesiredTemp);

	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;

}


ES_t SYSTEM_enuSleepMode(void){
	ES_t Local_enu_ErrorState = ES_NOK;
	/*Sleep Mode Select --> IDLE STATE*/
	MCUCR&=~(1<<MCUCR_SM0);
	MCUCR&=~(1<<MCUCR_SM1);
	MCUCR&=~(1<<MCUCR_SM2);
	/* Sleep mode Enable */
	MCUCR|=(1<<MCUCR_SE);

	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}

ES_t SYSTEM_enuOffState(void)
{
	ES_t Local_enuErrorState =ES_NOK;

		SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[0]);
		SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[1]);
		LCD_enuClearDisplay();
		LED_SYSTEM_enuLedStop();
		HEAT_COOL_ELEMENTS_enuHeaterStop();
		HEAT_COOL_ELEMENTS_enuCoolerStop();
		SYSTEM_enuSleepMode();

	Local_enuErrorState=ES_OK;
	return Local_enuErrorState;
}


ISR(VECT_INT0) //TEMP_UP_SWITCH
{
	if (Global_U8UPSwitchFlag==NOT_RISED)
	{
		Global_U8UPSwitchFlag=RISED;
	}

}

ISR(VECT_INT1)	//TEMP_DOWN_SWITCH
{
	if (Global_U8DOWNSwitchFlag==NOT_RISED)
	{
		Global_U8DOWNSwitchFlag=RISED;
	}


}
ISR(VECT_INT2)	//ON_OFF_SWITCH
{
	if(Global_U8CurrentState==OFF_STATE)
	{
		Global_U8CurrentState = ON_STATE;
		EEPROM_enuReadByteFromAddress(0x0000,&Global_U8ReadData);
		Global_U16DesiredTemp = Global_U8ReadData;
	}
	else if (Global_U8CurrentState==ON_STATE || Global_U8CurrentState==SETTINT_STATE){
		Global_U8CurrentState = OFF_STATE;
	}
}


ISR (VECT_TIMER2_CTC)
{

	if(Global_U8CurrentState==SETTINT_STATE || Global_U8CurrentState== ON_STATE)
	{
		Global_U16Five_SecondCounter ++;
		if (Global_U16Five_SecondCounter == FIVE_SECONDS)
		{

			Global_U16Five_SecondToggleFlag=1;
		}
	}

}
