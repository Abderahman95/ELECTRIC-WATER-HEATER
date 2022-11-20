#include "ERROR_STATE.h"
#include "TYPES.h"
#include "DIO_interface.h"
#include "SEVENSEGMENT_config.h"
#include "SEVENSEGMENT_private.h"
#include "util/delay.h"
#include "SEVENSEGMENT_interface.h"

extern SSG_t SEVENSEGMENT_AstrSevenSegmentConfig [SSG_NUMBER];


ES_t SevenSegment_enuInit(SSG_t *Copy_pAstrSevenSegmentConf)
{
ES_t Local_enuErrorState	=ES_NOK;

U8 Local_U8Iterator;
U32 Local_U32ErrorState;
for(Local_U8Iterator=0;Local_U8Iterator<SSG_NUMBER;Local_U8Iterator++)
{
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinA_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinA_Pin,DIO_U8OUTPUT);
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinB_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinB_Pin,DIO_U8OUTPUT)<< TWO_BITS_SHIFT;
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinC_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinC_Pin,DIO_U8OUTPUT)<< FOUR_BITS_SHIFT;
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinD_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinD_Pin,DIO_U8OUTPUT)<< SIX_BITS_SHIFT;
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinE_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinE_Pin,DIO_U8OUTPUT)<< EIGHT_BITS_SHIFT;
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinF_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinF_Pin,DIO_U8OUTPUT)<< TEN_BITS_SHIFT;
	Local_U32ErrorState=	DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinG_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_PinG_Pin,DIO_U8OUTPUT)<< TWELVE_BITS_SHIFT;

	//COMMENT AND DOT PIN IF CONNECTED set direction output

	if(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Common_Port != NOT_CONNECTED &&Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Common_Pin != NOT_CONNECTED )
	{
		DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Common_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Common_Pin,DIO_U8OUTPUT);

	}

	if(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Dot_Port != NOT_CONNECTED &&Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Dot_Pin != NOT_CONNECTED )
		{
			DIO_enuSetPinDirection(Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Dot_Port,Copy_pAstrSevenSegmentConf[Local_U8Iterator].SSG_Dot_Pin,DIO_U8OUTPUT);

		}
}
if(Local_U32ErrorState== SSG_CHECKVALUE)
{
Local_enuErrorState=ES_OK;
}
return Local_enuErrorState;

}//end of initialization

ES_t SevenSegment_enuDisplayNumber(SSG_t *Copy_pstrSevenSegmentInfo ,U8 Copy_U8Number)
{
	ES_t Local_enuErrorState	=ES_NOK;
	U32 Local_U32ErrorState;

		/*Boundary check*/

	if(Copy_pstrSevenSegmentInfo->SSG_Type == COMMON_ANODE)
	{
		/*Representation of the sent number*/
		Copy_U8Number= ~ SEVENSEGMENT_AU8COMMON_CATHODE_VALUES[Copy_U8Number];
	}
	else if (Copy_pstrSevenSegmentInfo->SSG_Type == COMMON_CATHOND)
	{
		/*Representation of the sent number*/
			Copy_U8Number=  SEVENSEGMENT_AU8COMMON_CATHODE_VALUES[Copy_U8Number];
	}

	Local_U32ErrorState = DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinA_Port, Copy_pstrSevenSegmentInfo->SSG_PinA_Pin, (( Copy_U8Number>>0)&1) );
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinB_Port, Copy_pstrSevenSegmentInfo->SSG_PinB_Pin,((Copy_U8Number>>1)&1))<< TWO_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinC_Port, Copy_pstrSevenSegmentInfo->SSG_PinC_Pin,((Copy_U8Number>>2)&1))<< FOUR_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinD_Port, Copy_pstrSevenSegmentInfo->SSG_PinD_Pin,((Copy_U8Number>>3)&1))<< SIX_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinE_Port, Copy_pstrSevenSegmentInfo->SSG_PinE_Pin,((Copy_U8Number>>4)&1))<< EIGHT_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinF_Port, Copy_pstrSevenSegmentInfo->SSG_PinF_Pin,((Copy_U8Number>>5)&1))<< TEN_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinG_Port, Copy_pstrSevenSegmentInfo->SSG_PinG_Pin,((Copy_U8Number>>6)&1))<< TWELVE_BITS_SHIFT;
	if(Local_U32ErrorState== SSG_CHECKVALUE)
	{
	Local_enuErrorState=ES_OK;
	}

	return Local_enuErrorState;
}
ES_t SevenSegment_enuToggleDisplay(SSG_t *Copy_pstrSevenSegmentInfo)
{
	ES_t Local_enuErrorState	=ES_NOK;
if(Copy_pstrSevenSegmentInfo->SSG_Common_Port != NOT_CONNECTED
		&& Copy_pstrSevenSegmentInfo->SSG_Common_Pin !=NOT_CONNECTED)
{
	if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_ANODE)
	{

		DIO_enuTogPinValue(Copy_pstrSevenSegmentInfo->SSG_Common_Port, Copy_pstrSevenSegmentInfo->SSG_Common_Pin);
	}
	else if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_CATHOND)
	{
		DIO_enuTogPinValue(Copy_pstrSevenSegmentInfo->SSG_Common_Port, Copy_pstrSevenSegmentInfo->SSG_Common_Pin);
	}
	Local_enuErrorState=ES_OK;
}




	return Local_enuErrorState;
}

ES_t SevenSegment_enuEnableCommon(SSG_t *Copy_pstrSevenSegmentInfo)
{
	ES_t Local_enuErrorState	=ES_NOK;
if(Copy_pstrSevenSegmentInfo->SSG_Common_Port != NOT_CONNECTED
		&& Copy_pstrSevenSegmentInfo->SSG_Common_Pin !=NOT_CONNECTED)
{
	if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_ANODE)
	{
		DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Common_Port, Copy_pstrSevenSegmentInfo->SSG_Common_Pin,DIO_U8HIGH);
	}
	else if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_CATHOND)
	{
		DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Common_Port, Copy_pstrSevenSegmentInfo->SSG_Common_Pin,DIO_U8LOW);
	}
	Local_enuErrorState=ES_OK;
}




	return Local_enuErrorState;
}

ES_t SevenSegment_enuDisableCommon(SSG_t *Copy_pstrSevenSegmentInfo)
{
	ES_t Local_enuErrorState	=ES_NOK;

	if(Copy_pstrSevenSegmentInfo->SSG_Common_Port != NOT_CONNECTED
			&& Copy_pstrSevenSegmentInfo->SSG_Common_Pin !=NOT_CONNECTED)
	{
		if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_ANODE)
		{
			DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Common_Port, Copy_pstrSevenSegmentInfo->SSG_Common_Pin,DIO_U8LOW);
		}
		else if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_CATHOND)
		{
			DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Common_Port, Copy_pstrSevenSegmentInfo->SSG_Common_Pin,DIO_U8HIGH);
		}
		Local_enuErrorState=ES_OK;
	}


	return Local_enuErrorState;
}

ES_t SevenSegment_enuEnableDot(SSG_t *Copy_pstrSevenSegmentInfo)
{
	ES_t Local_enuErrorState	=ES_NOK;

	if(Copy_pstrSevenSegmentInfo->SSG_Dot_Port != NOT_CONNECTED
			&& Copy_pstrSevenSegmentInfo->SSG_Dot_Pin !=NOT_CONNECTED)
	{
		if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_ANODE)
		{
			DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Dot_Port, Copy_pstrSevenSegmentInfo->SSG_Dot_Pin,DIO_U8LOW);
		}
		else if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_CATHOND)
		{
			DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Dot_Port, Copy_pstrSevenSegmentInfo->SSG_Dot_Pin,DIO_U8HIGH);
		}
		Local_enuErrorState=ES_OK;
	}


	return Local_enuErrorState;
}
ES_t SevenSegment_enuDisableDot(SSG_t *Copy_pstrSevenSegmentInfo)
{
	ES_t Local_enuErrorState	=ES_NOK;

	if(Copy_pstrSevenSegmentInfo->SSG_Dot_Port != NOT_CONNECTED
			&& Copy_pstrSevenSegmentInfo->SSG_Dot_Pin !=NOT_CONNECTED)
	{
		if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_ANODE)
		{
			DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Dot_Port, Copy_pstrSevenSegmentInfo->SSG_Dot_Pin,DIO_U8HIGH);
		}
		else if(Copy_pstrSevenSegmentInfo->SSG_Type ==COMMON_CATHOND)
		{
			DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_Dot_Port, Copy_pstrSevenSegmentInfo->SSG_Dot_Pin,DIO_U8LOW);
		}
		Local_enuErrorState=ES_OK;
	}



	return Local_enuErrorState;
}

/*Will disable it pin by pin*/
ES_t SevenSegment_enuStopDisplay(SSG_t *Copy_pstrSevenSegmentInfo) /*stop display the common on GIO*/
{
	ES_t Local_enuErrorState	=ES_NOK;
	U8 Local_U8StopValue=ZeroValue;
	U32 Local_U32ErrorState;
	if(Copy_pstrSevenSegmentInfo->SSG_Type == COMMON_CATHOND)
	{
		Local_U8StopValue= ~Local_U8StopValue; //255
	}

	Local_U32ErrorState = DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinA_Port, Copy_pstrSevenSegmentInfo->SSG_PinA_Pin,((Local_U8StopValue>>0)&1));
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinB_Port, Copy_pstrSevenSegmentInfo->SSG_PinB_Pin,((Local_U8StopValue>>1)&1))<< TWO_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinC_Port, Copy_pstrSevenSegmentInfo->SSG_PinC_Pin,((Local_U8StopValue>>2)&1))<< FOUR_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinD_Port, Copy_pstrSevenSegmentInfo->SSG_PinD_Pin,((Local_U8StopValue>>3)&1))<< SIX_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinE_Port, Copy_pstrSevenSegmentInfo->SSG_PinE_Pin,((Local_U8StopValue>>4)&1))<< EIGHT_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinF_Port, Copy_pstrSevenSegmentInfo->SSG_PinF_Pin,((Local_U8StopValue>>5)&1))<< TEN_BITS_SHIFT;
	Local_U32ErrorState|= DIO_enuSetPinValue(Copy_pstrSevenSegmentInfo->SSG_PinG_Port, Copy_pstrSevenSegmentInfo->SSG_PinG_Pin,((Local_U8StopValue>>6)&1))<< TWELVE_BITS_SHIFT;
	if(Local_U32ErrorState== SSG_CHECKVALUE)
	{
	Local_enuErrorState=ES_OK;
	}

	return Local_enuErrorState;
}






void SevenSegment_Write(U8 Copy_U8Number)
{
	U8 units,tens;
					units = Copy_U8Number % 10;
					tens = (int) Copy_U8Number / 10;

					SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[0]);
					SevenSegment_enuDisplayNumber(&SEVENSEGMENT_AstrSevenSegmentConfig[1],units);
					SevenSegment_enuEnableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[1]);


					_delay_ms(3.1);

					SevenSegment_enuDisableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[1]);
					SevenSegment_enuDisplayNumber(&SEVENSEGMENT_AstrSevenSegmentConfig[0],tens);
					SevenSegment_enuEnableCommon(&SEVENSEGMENT_AstrSevenSegmentConfig[0]);
					_delay_ms(1.1);
}
