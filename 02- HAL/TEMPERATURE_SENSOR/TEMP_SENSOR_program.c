#include "ERROR_STATE.h"
#include "TYPES.h"

#include "interrupt.h"

#include "TEMP_SENSOR_interface.h"
#include "TEMP_SENSOR_private.h"
#include "TEMP_SENSOR_config.h"

#include "DIO_interface.h"

#include "ADC_config.h"
#include "ADC_interface.h"

#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "TIMER_interface.h"

#include "GIE_interface.h"

extern EXTI_t EXTI_AstrEXTIConfig[TEMP_SENSOR_EXTERNAL_INTERRUPT_SOURCES];

 static  U8 TempSensor_U8Flag =TEMP_SENSOR_FLAG_NOT_RISED;

/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Local Function:
 * Responsible for rising a local static flag.
 * --------------------------------------------------------------------------------------------------------------------------------------------------------*/
void TempSensor_RiseFlag (void)
{
	TempSensor_U8Flag =TEMP_SENSOR_FLAG_RISED;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Initialization Function:
 * - Set the direction and value of the Sensor reading voltage to the microcontroller.
 * --------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* ------ADDING THE TIMER1 COMPARE MATCH INTERRUPT ON CHANNEL B TO TRIGGER THE ADC 21/3 ------------- */

ES_t TempSensor_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	U32 Local_U32ErrorState=TEMPSENSOR_INITIALVALUE ;
	if (TEMP_SENSOR_PIN<= DIO_U8PIN7)
	{
		/*--------------------------------------------------------------------------------------------------------------------------------------------------------
		 *Identify the Temperature sensor pin Direction and value Among the ADC CHANNELS PORT A from PIN 0 to PIN 7
		 *
		 * --------------------------------------------------------------------------------------------------------------------------------------------------------*/

		Local_U32ErrorState  = DIO_enuSetPinDirection(TEMP_SENSOR_PORT,TEMP_SENSOR_PIN,TEMP_SENSOR_DIRECTION);
		/*There was a bug in the next line. that was solved on 26/2/2022*/
		Local_U32ErrorState |= (DIO_enuSetPinValue(TEMP_SENSOR_PORT,TEMP_SENSOR_PIN,TEMP_SENSOR_STATE)<<TWO_BITS_SHIFT);

		Local_U32ErrorState |= (ADC_enuChannelSelect(ADC_CHANNEL_SELECTION)<<FOUR_BITS_SHIFT);
/* ------------------------------- ADDING THE TIMER COMPARE MATCH AUTO TRIGGERING 21/3 -----------------------*/
	#if ADC_AUTO_TRIGGERING_SOURCE	== ADC_U8ExternalInterruptRequest_0
		DIO_enuSetPinDirection(DIO_U8PORT_D, DIO_U8PIN2, DIO_U8INPUT);
		DIO_enuSetPinValue(DIO_U8PORT_D, DIO_U8PIN2, DIO_U8FLOAT);
		EXTI_enuInit(EXTI_AstrEXTIConfig);
		/*--------------------------------------------------------------------------------------------------------------------------------------------------------
		 * External Interrupt Direction and value selection:
		 * Responsible for rising a local static flag.
		 * --------------------------------------------------------------------------------------------------------------------------------------------------------*/

		Local_U32ErrorState |= (		ADC_enuAutoTriggerSource(ADC_AUTO_TRIGGERING_SOURCE)<<SIX_BITS_SHIFT);
	#elif  ADC_AUTO_TRIGGERING_SOURCE== ADC_U8TimerInterrupt_CompareMatchB
		/*AS PD4 OC1B is connected to the SSD, then it will be disconnected */
		//DIO_enuSetPinDirection(DIO_U8PORT_D, DIO_U8PIN4, DIO_U8OUTPUT);
		TIMER1_enuInit();
		//DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN4,DIO_U8OUTPUT);
		TIMER1_enuInterruptEnable();
		TIMER1_enuStartTimer();
		Local_U32ErrorState |= (		ADC_enuAutoTriggerSource(ADC_AUTO_TRIGGERING_SOURCE)<<SIX_BITS_SHIFT);

	#elif  ADC_AUTO_TRIGGERING_SOURCE	== ADC_U8SingleConversion
		Local_U32ErrorState |= (		ADC_enuAutoTriggerDisable()<<SIX_BITS_SHIFT);
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 		Local_U32ErrorState |= (		ADC_enuStartConversion()<<EIGHTEEN_BITS_SHIFT);
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	#elif ADC_AUTO_TRIGGERING_SOURCE	== ADC_U8FreeRunningMode
		Local_U32ErrorState |= (		ADC_enuAutoTriggerSource(ADC_AUTO_TRIGGERING_SOURCE)<<SIX_BITS_SHIFT);
		Local_U32ErrorState |= (		ADC_enuStartConversion()<<EIGHTEEN_BITS_SHIFT);
	#else
		Local_U32ErrorState |= (		ADC_enuAutoTriggerSource(ADC_AUTO_TRIGGERING_SOURCE)<<TWENTY_BITS_SHIFT);
	#endif
	}

	Local_U32ErrorState |= (ADC_enuEnableADC_Intrrupt()<<EIGHT_BITS_SHIFT);
	Local_U32ErrorState |= (TIMER1_enuSetCallBackDelay((volatile void (*) (void) ) ADC_enuEnableADC,TIMER_CTC1B_INTERRUPT_INDEX,TIMER1_100_MILE_SECOND) /*ADC_enuEnableADC()*/<<TEN_BITS_SHIFT);
	Local_U32ErrorState |= (ADC_enuCallBack( (volatile void (*) (void) ) TempSensor_RiseFlag)<<TWELVE_BITS_SHIFT);
	Local_U32ErrorState |= (ADC_enuInit()<<FOURTEEN_BITS_SHIFT);
	GIE_enu_Enable();
	//*((volatile U8*)(0x34))= Local_U32ErrorState>>8;
	//*((volatile U8*)(0x34))= Local_U32ErrorState;

	//0b00000001;

//	*((volatile U8*)(0x31)) = 0b011000000;
	//*((volatile U8*)(0x34))=0b11;

	if(Local_U32ErrorState == TEMPSENSOR_CEACKVALUE_SIXTEEN || Local_U32ErrorState == TEMPSENSOR_CEACKVALUE_FOURTEEN || Local_U32ErrorState == TEMPSENSOR_CEACKVALUE_TWENTY)
	{
		Local_enuErrorState = ES_OK;
//		*((volatile U8*)(0x34))=0b01;
	}

	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * Get tempreature reading Fuction:
 * --------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------- HERE I WANT THE SYSTEM TO SUM TEN TERMPERATURE READING THEN GET THE AVRADGE TO DISPLAY ----------*/

ES_t TempSensor_enuGetTempReading(U16 *Copy_pU16TempReading)
{
	ES_t Local_enuErrorState = ES_NOK;
	U8 Local_U8ErrorState=TEMPSENSOR_INITIALVALUE ;
	U16 Local_U16ADC_Reading, Local_U16OneTempReading;
	U32 Local_U32ADC_Voltage;

#if  ADC_AUTO_TRIGGERING_SOURCE	== ADC_U8SingleConversion
	Local_U8ErrorState = ADC_enuStartConversion();

#endif

	if (TempSensor_U8Flag == TEMP_SENSOR_FLAG_RISED )
	{
		Local_U8ErrorState = ADC_enuReadDataRegister(&Local_U16ADC_Reading);
		/*----------------------------------- ADC READING CALCULATION -------------------------------*/
		Local_U32ADC_Voltage = Local_U16ADC_Reading * ADC_VOLTAGE_EQUATION_STEP;
//		*Copy_pU16TempReading = Local_U32ADC_Voltage/ ADC_READING_DIVISION_FACTOR;
		Local_U16OneTempReading = Local_U32ADC_Voltage/ ADC_READING_DIVISION_FACTOR;
		* Copy_pU16TempReading= Local_U16OneTempReading;
		TempSensor_U8Flag =TEMP_SENSOR_FLAG_NOT_RISED;
//		*((volatile U8*)(0x34))=*Copy_pU16TempReading;
	}
	if (Local_U8ErrorState ==TEMPSENSOR_CEACKVALUE_ONE )
	{
		Local_enuErrorState = ES_OK;
		//*((volatile U8*)(0x34))=Local_U8ErrorState;
	}
	return Local_enuErrorState;
}
