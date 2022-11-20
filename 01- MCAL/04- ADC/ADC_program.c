#include "ERROR_STATE.h"
#include "TYPES.h"

#include "interrupt.h"

#include "ADC_interface.h"
#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"

static volatile void (* ADC_pfunISRFun ) (void) =NULL;


ES_t ADC_enuInit(void)
{

	ES_t		Local_enuErrorState = ES_NOK;


	/* ADC clock Prescaler Selection is done by Bit 1:0- ADPS2:0 in ADCSRA Register*/
		/* ADC_PRESCALER : PRESCALER_2 ADCSRA: ADPS2 = 0, ADPS1 = 0, ADPS0 = 0*/
		/* ADC_PRESCALER : PRESCALER_2 ADCSRA: ADPS2 = 0, ADPS1 = 0, ADPS0 = 1*/
	#if 	  ADC_PRESCALER ==      PRESCALER_2

	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS0);

	/* ADC_PRESCALER : PRESCALER_4 ADCSRA: ADPS2 = 0, ADPS1 = 1, ADPS0 = 0*/
#elif   ADC_PRESCALER ==   PRESCALER_4

	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS0);


	/* ADC_PRESCALER : PRESCALER_8 ADCSRA: ADPS2 = 0, ADPS1 = 1, ADPS0 = 1*/
#elif   ADC_PRESCALER ==   PRESCALER_8

	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS0);



	/* ADC_PRESCALER : PRESCALER_16 ADCSRA: ADPS2 = 1, ADPS1 = 0, ADPS0 = 0*/
#elif   ADC_PRESCALER ==   PRESCALER_16

	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS0);


	/* ADC_PRESCALER : PRESCALER_32 ADCSRA: ADPS2 = 1, ADPS1 = 0, ADPS0 = 1*/
#elif   ADC_PRESCALER ==   PRESCALER_32

	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS0);


	/* ADC_PRESCALER : PRESCALER_64 ADCSRA: ADPS2 = 1, ADPS1 = 1, ADPS0 = 0 */
#elif   ADC_PRESCALER ==   PRESCALER_64

	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA &= ~(ADC_MASK_BIT<<ADCSRA_ADPS0);

	/* ADC_PRESCALER : PRESCALER_128 ADCSRA: ADPS2 = 1, ADPS1 = 1, ADPS0 =1 */
#elif   ADC_PRESCALER ==   PRESCALER_128
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS2);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS1);
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADPS0);

#else
#error"ADC PRESCALER  SELECTION IS NOT CORRECT"

#endif

/* Voltage Reference Selection is done by Bit 7:6- REFS1:0 in ADMUX Register*/
	/*AREF_REFERENCE ADMUX: REFS1 = 0, REFS0 =0*/
#if ADC_VREFERNCE		==        AREF_REFERENCE

	ADMUX &=~ (ADC_MASK_BIT<<ADMUX_REFS0);
	ADMUX &=~ (ADC_MASK_BIT<<ADMUX_REFS1);


	/*AVCC_REFERENCE ADMUX: REFS1 = 0, REFS0 =1*/
#elif ADC_VREFERNCE		== 	 	AVCC_REFERENCE

		ADMUX |= (ADC_MASK_BIT<<ADMUX_REFS0);
		ADMUX &=~ (ADC_MASK_BIT<<ADMUX_REFS1);

	/*INTERNAL_REFERENCE ADMUX: REFS1 = 1, REFS0 =1*/
#elif ADC_VREFERNCE		==        INTERNAL_REFERENCE

		ADMUX |= (ADC_MASK_BIT<<ADMUX_REFS0);
		ADMUX |= (ADC_MASK_BIT<<ADMUX_REFS1);

#else
#error"ADC REFERENCE VOLTAGE SELECTION IS NOT CORRECT"

#endif

/* ADC ADJUSMENT Selection is done by Bit 5- ADLAR in ADMUX Register*/
		/*LEFT_ADJUSMENT ADMUX: ADLAR = 1*/
#if ADC_ADJUSMENT	 	==	LEFT_ADJUSMENT
		ADMUX |= (ADC_MASK_BIT<<ADMUX_ADLAR);

		/*LEFT_ADJUSMENT ADMUX: ADLAR = 0*/
#elif ADC_ADJUSMENT	 	==	RIGHT_ADJUSMENT
		ADMUX &= ~ (ADC_MASK_BIT<<ADMUX_ADLAR);

#else
#error"ADC ADJUSMENT SELECTION IS NOT CORRECT"

#endif
		Local_enuErrorState =ES_OK;
	return Local_enuErrorState;

}

/*----------------------------------------------------------------------------------------------------
 *ES_t ADC_enuEnableADC(void)
 * This Function is responsible for the selection of :
 * 1- Enabling the ADC Driver
 *----------------------------------------------------------------------------------------------------*/

ES_t ADC_enuEnableADC(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	ADCSRA|= (ADC_MASK_BIT<<ADCSRA_ADEN);
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;
}

ES_t ADC_enuDisableADC(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	ADCSRA&= ~(ADC_MASK_BIT<<ADCSRA_ADEN);
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;
}

ES_t ADC_enuEnableADC_Intrrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	ADCSRA|= (ADC_MASK_BIT<<ADCSRA_ADIE);
	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES_t ADC_enuDisableADC_Intrrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	ADCSRA&= ~(ADC_MASK_BIT<<ADCSRA_ADIE);
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;
}


/*----------------------------------------------------------------------------------------------------
 *ES_t ADC_enuStartConversion(void)
 * This Function is responsible for the selection of :
 * 1- Starting the first ADC conversion.
 * 			(A)- Write logic one to the bit 6 - ADSC of the ADCSRA to start the first conversion.
 *----------------------------------------------------------------------------------------------------*/
ES_t ADC_enuStartConversion(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADSC);
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;

}

ES_t ADC_enuChannelSelect(U8 Copy_U8ChannelID)
{

	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_U8ChannelID <=CHANNEL_MAXNUMBER)
	{
/*--------------------------------------------------------------------------------------------------------------------------------
 * Clearing the ADMUX - Bits 4:0: MUX4:0. Before assenting the new channel ID
 *-------------------------------------------------------------------------------------------------------------------------------- */
		ADMUX&= CHANNEL_MASKING_ZERO;
		ADMUX|=(Copy_U8ChannelID);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANG;
	}


	return Local_enuErrorState;

}

ES_t ADC_enuAutoTriggerSource(U8 Copy_U8InterruptSource)
{
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_U8InterruptSource <= TRIGGER_SOURCE_MAXNUMBER)
	{
/* -------------------------------------------------------------------------------------------------------------------------------
	*  Disable ADC Auto trigger source.
*  --------------------------------------------------------------------------------------------------------------------------------*/
		ADCSRA&= ~ (ADC_MASK_BIT<< ADCSRA_ADATE);

/* -------------------------------------------------------------------------------------------------------------------------------
	*  Mask ADC Auto trigger source  by zero, to ensure no incorrectness accrues.
*  --------------------------------------------------------------------------------------------------------------------------------*/
		SFIOR &= AUTO_TRIGGER_MASKING_ZERO;

/* -------------------------------------------------------------------------------------------------------------------------------
	*  ADC Auto trigger source selection
*  --------------------------------------------------------------------------------------------------------------------------------*/
		SFIOR|= Copy_U8InterruptSource << SFIOR_ADTS0;

/*----------------------------------------------------------------------------------------------------------------------------------
 	  * In Case of Free running Mode,
 *  ----------------------------------------------------------------------------------------------------------------------------------*/
		if (Copy_U8InterruptSource == 0)
		{
			ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADSC);
		}
/* -------------------------------------------------------------------------------------------------------------------------------
 	 *  ADC Auto triggering Enable
 *  -------------------------------------------------------------------------------------------------------------------------------*/
		ADCSRA|= (ADC_MASK_BIT<< ADCSRA_ADATE);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANG;
	}

	return Local_enuErrorState;

}

ES_t ADC_enuAutoTriggerDisable(void)
{
	ES_t Local_enuErrorState = ES_NOK;
/* -------------------------------------------------------------------------------------------------------------------------------
	*  Disable ADC Auto trigger source.
*  --------------------------------------------------------------------------------------------------------------------------------*/
		ADCSRA&= ~ (ADC_MASK_BIT<< ADCSRA_ADATE);
		Local_enuErrorState =ES_OK;
		return Local_enuErrorState;
	}

ES_t ADC_enuReadDataRegister(U16 * Copy_pU16ConversionResult)
{

	ES_t Local_enuErrorState = ES_NOK;

#if ADC_ADJUSMENT == LEFT_ADJUSMENT
	*Copy_pU16ConversionResult= (ADCL>>ADCL_LEFT);
	*Copy_pU16ConversionResult |= ((U16)ADCH<<ADCH_LEFT);
	Local_enuErrorState =ES_OK;
#elif ADC_ADJUSMENT == RIGHT_ADJUSMENT
	*Copy_pU16ConversionResult= ADCL;
	*Copy_pU16ConversionResult |= ((U16)ADCH<<ADCH_RIGHT);
	Local_enuErrorState =ES_OK;
#else
#error "ADC ADJUSTMENT SELECTION IS NO CORRECT"
#endif
	return Local_enuErrorState;

}

ES_t ADC_enuCallBack(volatile void( *Copy_pfunAppFun) (void))
{

	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pfunAppFun != NULL)
	{
		ADC_pfunISRFun = Copy_pfunAppFun;
		Local_enuErrorState =ES_OK;
	}
	return Local_enuErrorState;

}

ES_t ADC_enuPolling(void)
{

	ES_t Local_enuErrorState = ES_NOK;
	while (!((ADCSRA>>ADCSRA_ADIF)&ADC_MASK_BIT));
	{
	ADCSRA |= (ADC_MASK_BIT<<ADCSRA_ADIF); 
	Local_enuErrorState =ES_OK;
	}
	return Local_enuErrorState;

}

ISR(VECT_ADC)
{
	if (ADC_pfunISRFun != NULL)
	{
		ADC_pfunISRFun();
	}
}
