#include "TYPES.h"
#include "ERROR_STATE.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "DIO_register.h"


#include "interrupt.h"

static void (* TIMER0_pfunISRFun[TIMER0_CALL_BACK] ) (void) ={NULL,NULL};
static void (* TIMER1_pfunISRFun[TIMER1_CALL_BACK] ) (void) ={NULL,NULL,NULL};
static void (* TIMER2_pfunISRFun[TIMER2_CALL_BACK] ) (void) ={NULL,NULL};

//static void (* TIMER0_pfunISRFun) (void) =NULL;
extern U16 Global_U16Timer0CTC_OneSecondCounter=0;
extern U32 Global_32TIMER1_CTCA_SecondsCounter=0;
static U32 Global_U32CounterOVF =0;
static U32 Global_U32CounterCTC =0;
static U16 Global_U32CounterCTC1A=0;
static U16 Global_U32CounterCTC1B=0;

static U32 Global_U32CounterOVF1 =0;

static U32 Global_U32CounterOVF2 =0;
static U16 Global_U32CounterCTC2=0;

static  U16 TIMER0_U16DELAY_MILEOSECOND;
static  U16 TIMER1_U16DELAY_MILEOSECOND;
static  U16 TIMER2_U16DELAY_MILEOSECOND;

static 	U16 Global_U16IMER1_PreloadValue = TIMER1_U16PRELOAD_VALUE;



/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER0_enuInit.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler,
**					  Waveform Generation Mode,
**					  Compare Match Output  Mode.
**---------------------------------------------------------------------------------------*/

ES_t TIMER0_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;


/**------------------------- Selection Mode and state of OC0_PIN --------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER0_NORMAL_MODE --------------------------*/
#if TIMER0_MODE == TIMER0_NORMAL_MODE

/*----------------------------- Waveform Generation Mode --------------------------*/

	  				 TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_WGM00);
	  		 	 	 TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_WGM01);


/*-----------------------------  Compare Match Output Mode --------------------------*/
	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	  		 	 	 TCNT0 = TIMER0_U8PRELOAD_VALUE;
/*-----------------------------  Overflow Interrupt Enable --------------------------*/
	  		 	 	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_TOIE0);


	 	 	  		 	Local_enuErrorState = ES_OK;

/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER0_PHASE_CORRECT_PWM --------------------------*/

#elif TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM
	  				 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_WGM00);
	  		 	 	 TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_WGM01);

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if	 	 	TIMER0_COMP_MODE == TIMER_OC0_DISCONNECTED
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif		TIMER0_COMP_MODE == TIMER_OC0_RESERVED
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif		TIMER0_COMP_MODE == TIMER_OC0_CLEAR
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		TIMER0_COMP_MODE == TIMER_OC0_SET
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;


#else
#error  "The TIMER0_COMP_MODE selection is not correct"
#endif
/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER0_CTC_MODE --------------------------*/

#elif TIMER0_MODE == TIMER0_CTC_MODE
	  		 	 	  			 TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_WGM00);
	  		 	 	  	 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_WGM01);

	  		 	 	  	 	 	 //OCR0 =TIMER_OCR0_COUNTS_NUMBER;
	  		 	 	  	 	 	 OCR0= 250;


/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER0_COMP_MODE == TIMER_OC0_DISCONNECTED
	  		 	 	  	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER0_COMP_MODE == TIMER_OC0_TOGGELE
	  		 	 	  	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER0_COMP_MODE == TIMER_OC0_CLEAR
	  		 	 	  	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM01);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER0_COMP_MODE == TIMER_OC0_SET
	  		 	 	  	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM01);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER0_COMP_MODE selection is not correct"
#endif
/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER0_FAST_PWM --------------------------*/

#elif TIMER0_MODE == TIMER0_FAST_PWM
	  		 	   		 	 		 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_WGM00);
	  		 	   		 	 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_WGM01);
/*-----------------------------  Compare Match Output Mode --------------------------*/

#if 	 	 	 			TIMER0_COMP_MODE == TIMER_OC0_DISCONNECTED
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  		TIMER0_COMP_MODE == TIMER_OC0_RESERVED
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  		TIMER0_COMP_MODE == TIMER_OC0_CLEAR
	  		 	 	  		 	 	 TCCR0 &=~ (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM01);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  		TIMER0_COMP_MODE == TIMER_OC0_SET
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM00);
	  		 	 	  		 	 	 TCCR0 |= (TIMER_MASK_BIT<<TCCR0_COM01);
	  		 	 	  		 	Local_enuErrorState = ES_OK;
 #else
#error  "The TIMER0_COMP_MODE selection is not correct"
#endif
/*----------------------------------------------------------------------------------------*/

/*----------------------------- MODE SELLECTION IS NOT CORRECT --------------------------*/

#else
#error "The TIMER0_MODE selection is not correct"
#endif

/*----------------------------------------------------------------------------------------*/




	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER0_enuInterruptEnable.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : Enable the OVERFLOW and CLEAR COMPARE MATCH INTERRUPTS.
**---------------------------------------------------------------------------------------*/

ES_t TIMER0_enuInterruptEnable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if TIMER0_MODE == TIMER0_NORMAL_MODE
 	 //Enable the OVF Interrupt
 	 GIE_enu_Enable();
	 Local_enuErrorState = ES_OK;

 	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_TOIE0);
#elif TIMER0_MODE == TIMER0_CTC_MODE
	 //Enable the CTC Interrupt
	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE0);
	 GIE_enu_Enable();
	 Local_enuErrorState = ES_OK;
#endif
	 return Local_enuErrorState ;
}
/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER0_enuInterruptDisable.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : Disable the OVERFLOW and CLEAR COMPARE MATCH INTERRUPTS.
**---------------------------------------------------------------------------------------*/

ES_t TIMER0_enuInterruptDisable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if TIMER0_MODE == TIMER0_NORMAL_MODE
 	 //Enable the OVF Interrupt
	 Local_enuErrorState = ES_OK;

 	 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_TOIE0);
#elif TIMER0_MODE == TIMER0_CTC_MODE
	 //Enable the CTC Interrupt
	 TIMSK &= ~ (TIMER_MASK_BIT<<TIMSK_OCIE0);
	 Local_enuErrorState = ES_OK;
#endif
	 return Local_enuErrorState ;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER0_enuStartTimer.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler to start the timer.
**					IF TIMER0 on CTC mode, Set OC0 pin as output, Set the OCR0 Value, Enable CTC Interrupt.
**---------------------------------------------------------------------------------------*/

ES_t TIMER0_enuStartTimer(void)
{
	ES_t Local_enuErrorState=ES_NOK;
	/*----------------------------------------------------------------------------------------*/
	/**----------------------- Set the OCO Pin as outputS -----------------------------------**/

//	DIO_enuSetPinDirection(DIO_U8PORT_B,DIO_U8PIN3,DIO_U8OUTPUT);

	/**----------------------- Selection TIMER0_PRESCALER -----------------------------------**/


	#if 	TIMER0_PRESCALER == TIMER_CLOCK_NO_PRESCHALER
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS00);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS01);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS02);
		  		 	Local_enuErrorState = ES_OK;

	#elif	TIMER0_PRESCALER == TIMER_CLOCK_8_PRESCHALER
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS00);
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS01);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS02);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER0_PRESCALER == TIMER_CLOCK_64_PRESCHALER
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS00);
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS01);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS02);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER0_PRESCALER == TIMER_CLOCK_256_PRESCHALER
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS00);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS01);
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS02);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER0_PRESCALER == TIMER_CLOCK_1024_PRESCHALER
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS00);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS01);
				TCCR0 |= (TIMER_MASK_BIT<<TCCR0_CS02);
		  		 	Local_enuErrorState = ES_OK;

	#else
	#error "The TIMER0_PRESCALER selection is not correct"
	#endif
	/*----------------------------------------------------------------------------------------*/


	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER0_enuStopTimer.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler to TIMER_CLOCK_NO_CLOCK to stop the timer.
**---------------------------------------------------------------------------------------*/

ES_t TIMER0_enuStopTimer(void)
{
	ES_t Local_enuErrorState=ES_NOK;

/**----------------------- Selection TIMER0_PRESCALER -----------------------------------**/
/*----------------------------TIMER_CLOCK_NO_CLOCK-------------------------------------------*/
			    TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS00);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS01);
				TCCR0 &= ~(TIMER_MASK_BIT<<TCCR0_CS02);
				Local_enuErrorState=ES_OK;
	return Local_enuErrorState;
}


/*--------------------------------------------------------------------------------------**
**	Function Name   : Timer0_enuSetCallBack.
**	Return Type     : ES_t ENUM.
**	Arguments       : The callback function, Index of the callback array, delay value in mile seconds .
**	Functionality   : .
**---------------------------------------------------------------------------------------*/


//ES_t Timer0_enuSetCallBack( void(*Copy_pfunISRFun)(void),U8 Copy_U8TimerIntIndex, U8 Copy_U8TimerDelay)
//ES_t Timer0_enuSetCallBack(volatile void( *Copy_pfunISRFun) (void))
ES_t TIMER0_enuSetCallBackDelay( void( *Copy_pfunISRFun) (void),U8 Copy_U8Timer0IntIndex, U16 Copy_U16Timer0Delay)

{
	ES_t Local_enuErrorState=ES_NOK;
	TIMER0_pfunISRFun[Copy_U8Timer0IntIndex]= Copy_pfunISRFun;
	//TIMER0_pfunISRFun= Copy_pfunISRFun;

	TIMER0_U16DELAY_MILEOSECOND = Copy_U16Timer0Delay;
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
*--------------------------------------Timer 0 ISR-----------------------------------------------*
**---------------------------------------------------------------------------------------*/


ISR (VECT_TIMER0_OVF)
{
	if (TIMER0_pfunISRFun[TIMER0_OVF_CALLBACK_INT_INDEX] != NULL)
	{
		Global_U32CounterOVF ++;

		if (Global_U32CounterOVF == TIMER0_U32NUMBER_OF_OVERFLOW)
		{
			TCCR0 = TIMER0_U8PRELOAD_VALUE;
			TIMER0_pfunISRFun[TIMER0_OVF_CALLBACK_INT_INDEX]();
			Global_U32CounterOVF =0;
		}
	}
}

ISR (VECT_TIMER0_CTC)
{

	if (TIMER0_pfunISRFun[TIMER_CTC0_INTERRUPT_INDEX] != NULL)
	{
	Global_U32CounterCTC ++;

		if (Global_U32CounterCTC == TIMER0_U16DELAY_MILEOSECOND)

		{
			TIMER0_pfunISRFun[TIMER_CTC0_INTERRUPT_INDEX]();
			//TIMER0_pfunISRFun();
			Global_U16Timer0CTC_OneSecondCounter++;
			Global_U32CounterCTC =0;
		}
	}

}


/*---------------------------------------- THE END OF TIMER 0 ------------------------------------------------------------------------*/



/*---------------------------------------- TIMER2 ------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER2_enuInit.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler,
**					  Waveform Generation Mode,
**					  Compare Match Output  Mode.
**---------------------------------------------------------------------------------------*/

ES_t TIMER2_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;


/**------------------------- Selection Mode and state of OC0_PIN --------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER2_NORMAL_MODE --------------------------*/
//ASSR &=~ (TIMER_MASK_BIT<<AASR_AS2);

#if TIMER2_MODE == TIMER2_NORMAL_MODE

/*----------------------------- Waveform Generation Mode --------------------------*/

	  				 TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_WGM20);
	  		 	 	 TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_WGM21);


/*-----------------------------  Compare Match Output Mode --------------------------*/
	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	  		 	 	 TCNT2 = TIMER2_U8PRELOAD_VALUE;
/*-----------------------------  Overflow Interrupt Enable --------------------------*/
	  		 	 	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_TOIE2);


	 	 	  		 	Local_enuErrorState = ES_OK;

/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER2_PHASE_CORRECT_PWM --------------------------*/

#elif TIMER2_MODE == TIMER2_PHASE_CORRECT_PWM
	  				 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_WGM20);
	  		 	 	 TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_WGM21);

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if	 	 	TIMER2_COMP_MODE == TIMER_OCX_DISCONNECTED
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif		TIMER2_COMP_MODE == TIMER_OCX_RESERVED
	  		 	 	  		 	 	 TCCR2 |=  (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif		TIMER2_COMP_MODE == TIMER_OCX_CLEAR
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 |=  (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		TIMER2_COMP_MODE == TIMER_OCX_SET
	  		 	 	  		 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;


#else
#error  "The TIMER2_COMP_MODE selection is not correct"
#endif
/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER2_CTC_MODE --------------------------*/

#elif TIMER2_MODE == TIMER2_CTC_MODE
	  		 	 	  			 TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_WGM20);
	  		 	 	  	 	 	 TCCR2 |=  (TIMER_MASK_BIT<<TCCR2_WGM21);
	  		 	 	  	 	ASSR &=~ (TIMER_MASK_BIT <<ASSR_AS2);
	  		 	 	  	 	 	 //OCR0 =TIMER_OCR0_COUNTS_NUMBER;
	  		 	 	  	 	 	 OCR2= 250;
	  		 	 	  	 	 	 //OCR2 =TIMER2_U32NUMBER_OF_TICKS_FRECTION;

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER2_COMP_MODE == TIMER_OC2_DISCONNECTED
	  		 	 	  	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER2_COMP_MODE == TIMER_OC2_TOGGELE
	  		 	 	  	  		 	 	 TCCR2 |=  (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER2_COMP_MODE == TIMER_OC2_CLEAR
	  		 	 	  	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  	  		 	 	 TCCR2 |=  (TIMER_MASK_BIT<<TCCR2_COM21);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER2_COMP_MODE == TIMER_OC2_SET
	  		 	 	  	  		 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  	  		 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_COM21);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER2_COMP_MODE selection is not correct"
#endif
/*----------------------------------------------------------------------------------------*/
/*----------------------------- TIMER2_FAST_PWM --------------------------*/

#elif TIMER2_MODE == TIMER2_FAST_PWM
	  		 	   		 	 		 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_WGM20);
	  		 	   		 	 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_WGM21);
/*-----------------------------  Compare Match Output Mode --------------------------*/

#if 	 	 	 			TIMER2_COMP_MODE == TIMER_OC2_DISCONNECTED
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  		TIMER2_COMP_MODE == TIMER_OC2_RESERVED
	  		 	 	  		 	 	 TCCR2  |= (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  		TIMER2_COMP_MODE == TIMER_OC2_CLEAR
	  		 	 	  		 	 	 TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2  |= (TIMER_MASK_BIT<<TCCR2_COM21);
	 	  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  		TIMER2_COMP_MODE == TIMER_OC2_SET
	  		 	 	  		 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_COM20);
	  		 	 	  		 	 	 TCCR2 |= (TIMER_MASK_BIT<<TCCR2_COM21);
	  		 	 	  		 	Local_enuErrorState = ES_OK;
 #else
#error  "The TIMER2_COMP_MODE selection is not correct"
#endif
/*----------------------------------------------------------------------------------------*/

/*----------------------------- MODE SELLECTION IS NOT CORRECT --------------------------*/

#else
#error "The TIMER2_MODE selection is not correct"
#endif

/*----------------------------------------------------------------------------------------*/




	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER2_enuInterruptEnable.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : Enable the OVERFLOW and CLEAR COMPARE MATCH INTERRUPTS.
**---------------------------------------------------------------------------------------*/

ES_t TIMER2_enuInterruptEnable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if TIMER2_MODE == TIMER2_NORMAL_MODE
 	 //Enable the OVF Interrupt
 	 GIE_enu_Enable();
	 Local_enuErrorState = ES_OK;

 	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_TOIE2);
#elif TIMER2_MODE == TIMER2_CTC_MODE
	 //Enable the CTC Interrupt
	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE2);
	 GIE_enu_Enable();
	 Local_enuErrorState = ES_OK;
#endif
	 return Local_enuErrorState ;
}
/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER2_enuInterruptDisable.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : Disable the OVERFLOW and CLEAR COMPARE MATCH INTERRUPTS.
**---------------------------------------------------------------------------------------*/

ES_t TIMER2_enuInterruptDisable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if TIMER2_MODE == TIMER2_NORMAL_MODE
 	 //Enable the OVF Interrupt
	 Local_enuErrorState = ES_OK;

 	 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_TOIE2);
#elif TIMER2_MODE == TIMER2_CTC_MODE
	 //Enable the CTC Interrupt
	 TIMSK &= ~ (TIMER_MASK_BIT<<TIMSK_OCIE2);
	 Local_enuErrorState = ES_OK;
#endif
	 return Local_enuErrorState ;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER2_enuStartTimer.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler to start the timer.
**					IF TIMER2 on CTC mode, Set OC0 pin as output, Set the OCR0 Value, Enable CTC Interrupt.
**---------------------------------------------------------------------------------------*/

ES_t TIMER2_enuStartTimer(void)
{
	ES_t Local_enuErrorState=ES_NOK;
	/*----------------------------------------------------------------------------------------*/
	/**----------------------- Set the OC2 Pin as outputS -----------------------------------**/

	//DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN7,DIO_U8OUTPUT);

	/**----------------------- Selection TIMER2_PRESCALER -----------------------------------**/


	#if 	TIMER2_PRESCALER == TIMER_CLOCK_NO_PRESCHALER
				TCCR2  |= (TIMER_MASK_BIT<<TCCR2_CS20);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS21);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS22);
		  		 	Local_enuErrorState = ES_OK;

	#elif	TIMER2_PRESCALER == TIMER_CLOCK_8_PRESCHALER
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS20);
				TCCR2  |= (TIMER_MASK_BIT<<TCCR2_CS21);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS22);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER2_PRESCALER == TIMER_CLOCK_64_PRESCHALER
				TCCR2 |= (TIMER_MASK_BIT<<TCCR2_CS20);
				TCCR2 |= (TIMER_MASK_BIT<<TCCR2_CS21);
				TCCR2 &=~ (TIMER_MASK_BIT<<TCCR2_CS22);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER2_PRESCALER == TIMER_CLOCK_256_PRESCHALER
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS20);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS21);
				TCCR2  |= (TIMER_MASK_BIT<<TCCR2_CS22);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER2_PRESCALER == TIMER_CLOCK_1024_PRESCHALER
				TCCR2 |= (TIMER_MASK_BIT<<TCCR2_CS20);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS21);
				TCCR2 |= (TIMER_MASK_BIT<<TCCR2_CS22);
		  		 	Local_enuErrorState = ES_OK;

	#else
	#error "The TIMER2_PRESCALER selection is not correct"
	#endif
	/*----------------------------------------------------------------------------------------*/


	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER2_enuStopTimer.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler to TIMER_CLOCK_NO_CLOCK to stop the timer.
**---------------------------------------------------------------------------------------*/

ES_t TIMER2_enuStopTimer(void)
{
	ES_t Local_enuErrorState=ES_NOK;

/**----------------------- Selection TIMER2_PRESCALER -----------------------------------**/
/*----------------------------TIMER_CLOCK_NO_CLOCK-------------------------------------------*/
			    TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS20);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS21);
				TCCR2 &= ~(TIMER_MASK_BIT<<TCCR2_CS22);
				Local_enuErrorState=ES_OK;
	return Local_enuErrorState;
}


/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER2_enuSetCallBack.
**	Return Type     : ES_t ENUM.
**	Arguments       : The callback function, Index of the callback array, delay value in mile seconds .
**	Functionality   : .
**---------------------------------------------------------------------------------------*/


//ES_t TIMER2_enuSetCallBack( void(*Copy_pfunISRFun)(void),U8 Copy_U8TimerIntIndex, U8 Copy_U8TimerDelay)
//ES_t TIMER2_enuSetCallBack(volatile void( *Copy_pfunISRFun) (void))
ES_t TIMER2_enuSetCallBackDelay( void( *Copy_pfunISRFun) (void),U8 Copy_U8Timer2IntIndex, U16 Copy_U16Timer2Delay)

{
	ES_t Local_enuErrorState=ES_NOK;
	TIMER2_pfunISRFun[Copy_U8Timer2IntIndex]= Copy_pfunISRFun;
	//TIMER2_pfunISRFun= Copy_pfunISRFun;

	TIMER2_U16DELAY_MILEOSECOND = Copy_U16Timer2Delay;
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
*--------------------------------------TIMER 2 ISR-----------------------------------------------*
**---------------------------------------------------------------------------------------*/


ISR (VECT_TIMER2_OVF)
{
	if (TIMER2_pfunISRFun[TIMER2_OVF_CALLBACK_INT_INDEX] != NULL)
	{
		Global_U32CounterOVF2 ++;

		if (Global_U32CounterOVF2 == TIMER2_U32NUMBER_OF_OVERFLOW)
		{
			TCCR2 = TIMER2_U8PRELOAD_VALUE;
			TIMER2_pfunISRFun[TIMER2_OVF_CALLBACK_INT_INDEX]();
			Global_U32CounterOVF2 =0;
		}
	}
}
/*
ISR (VECT_TIMER2_CTC)
{

	if (TIMER2_pfunISRFun[TIMER_CTC2_INTERRUPT_INDEX] != NULL)
	{
	Global_U32CounterCTC2 ++;

		if (Global_U32CounterCTC2 == TIMER2_U16DELAY_MILEOSECOND)

		{
			TIMER2_pfunISRFun[TIMER_CTC2_INTERRUPT_INDEX]();

			Global_U32CounterCTC2 =0;
		}
	}

}
*/
/*------------------------------------ THE END OF TIMER2 ------------------------------------------------------------------*/

/*---------------------------------------- TIMER 1 ------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER1_enuInit.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Waveform Generation Mode,
**					  Compare Match Output  Mode.
**---------------------------------------------------------------------------------------*/



ES_t TIMER1_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	U16 Local_u16OutCompareValue_A,Local_u16OutCompareValue_B;
/**------------------------- Selection Mode and state of OC1_PIN --------------------------*/
/*--------------------------------------------TIMER1OCR1A_COUNTS_NUMBER--------------------------------------------*/
/*----------------------------- TIMER1_NORMAL_MODE --------------------------*/
#if TIMER1_MODE == TIMER1_NORMAL_MODE

/*----------------------------- Waveform Generation Mode --------------------------*/

	  				 TCCR1A &= ~(TIMER_MASK_BIT<<TCCR1A_WGM10);
	  		 	 	 TCCR1A &= ~(TIMER_MASK_BIT<<TCCR1A_WGM11);
	  				 TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_WGM12);
	  		 	 	 TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_WGM13);



/*-----------------------------  Compare Match Output Mode --------------------------*/
	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		 	 	 TCNT1H = (Global_U16IMER1_PreloadValue>>TIMER_MASK_EIGHT_BIT);
	  		 	 	TCNT1L = Global_U16IMER1_PreloadValue;
/*-----------------------------  Overflow Interrupt Enable --------------------------*/
	  		 	 	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_TOIE1);


	 	 	  		 	Local_enuErrorState = ES_OK;

/*----------------------------------------------------------------------------------------*/

/*----------------------------- TIMER1_CTC_MODE --------------------------*/

#elif TIMER1_MODE == TIMER1_CTC_MODE_OCR1A


	  		 	 	  			 TCCR1A &= ~(TIMER_MASK_BIT<<TCCR1A_WGM10);
	  		 	 	  	 	 	 TCCR1A  &= ~ (TIMER_MASK_BIT<<TCCR1A_WGM11);
	  		 	 	  	 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_WGM12);
	  		 	 	  	 	 	 TCCR1B  &= ~(TIMER_MASK_BIT<<TCCR1B_WGM13);

#if TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
	  		 	 	  	 	 //OCR1A =TIMER1OCR1A_COUNTS_NUMBER;
	  		 	 	  	 	//Local_u16OutCompareValue_A = TIMER1OCR1A_COUNTS_NUMBER;
	  		 	 	  	Local_u16OutCompareValue_A = TIMER1_CTCMODE_COUNTS_NUMBER;

	  		 	 	  	OCR1AH = (Local_u16OutCompareValue_A >> TIMER_MASK_EIGHT_BIT);
	  		 	 	  	OCR1AL =  Local_u16OutCompareValue_A;
	  		 	 	  /*	 OCR1AH = 0b11000011;
	  		 	 	  	 OCR1AL = 0b00010011;
	  		 	 	 */

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER1_COMP_MODE == TIMER_OC1_DISCONNECTED
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_TOGGELE
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_CLEAR
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_SET
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER1_COMP_MODE selection is not correct"
#endif

#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B

	  		  		 	 	  	Local_u16OutCompareValue_B = TIMER1_CTCMODE_COUNTS_NUMBER;
	  		  		 	 	  		OCR1BH = (Local_u16OutCompareValue_B >> TIMER_MASK_EIGHT_BIT);
	  		  		 	 	  		OCR1BL =  Local_u16OutCompareValue_B;

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER1_COMP_MODE == TIMER_OC1_DISCONNECTED
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_TOGGELE
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_CLEAR
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_SET
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B0);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER1_COMP_MODE selection is not correct"
#endif

#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B

	  		  	  		 	 	  Local_u16OutCompareValue_A = TIMER1_CTCMODE_COUNTS_NUMBER;

	  		  	  		 	 	  	OCR1AH = (Local_u16OutCompareValue_A >> TIMER_MASK_EIGHT_BIT);
	  		  	  		 	 	  	OCR1AL =  Local_u16OutCompareValue_A;
	  		  		 	 	  	Local_u16OutCompareValue_B = TIMER1_CTCMODE_COUNTS_NUMBER;
	  		  		 	 	  		OCR1BH = (Local_u16OutCompareValue_B >> TIMER_MASK_EIGHT_BIT);
	  		  		 	 	  		OCR1BL =  Local_u16OutCompareValue_B;

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER1_COMP_MODE == TIMER_OC1_DISCONNECTED
 		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
 		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
 		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_TOGGELE
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_CLEAR

	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_SET
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1A0);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1A1);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B0);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER1_COMP_MODE selection is not correct"
#endif
#else
#error	"CHANNEL SELLECTION IS NOT CORRECT"
#endif

/*----------------------------------------------------------------------------------------*/

#elif TIMER1_MODE == TIMER1_CTC_MODE_ICR1


	  		 	 	  			 TCCR1A  &=~(TIMER_MASK_BIT<<TCCR1A_WGM10);
	  		 	 	  	 	 	 TCCR1A  &=~(TIMER_MASK_BIT<<TCCR1A_WGM11);
	  		 	 	  	 	 	 TCCR1B   |=(TIMER_MASK_BIT<<TCCR1B_WGM12);
	  		 	 	  	 	 	 TCCR1B   |=(TIMER_MASK_BIT<<TCCR1B_WGM13);



#if TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
	  		 	 	  	 	 //OCR1A =TIMER1OCR1A_COUNTS_NUMBER;
	  		 	 	  	 	//Local_u16OutCompareValue_A = TIMER1OCR1A_COUNTS_NUMBER;
	  		 	 	  	Local_u16OutCompareValue_A = TIMER1_CTCMODE_COUNTS_NUMBER;

	  		 	 	  	OCR1AH = (Local_u16OutCompareValue_A >> TIMER_MASK_EIGHT_BIT);
	  		 	 	  	OCR1AL =  Local_u16OutCompareValue_A;

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER1_COMP_MODE == TIMER_OC1_DISCONNECTED
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_TOGGELE
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_CLEAR
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_SET
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER1_COMP_MODE selection is not correct"
#endif

#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B

	  		  		 	 	  	Local_u16OutCompareValue_B = TIMER1_CTCMODE_COUNTS_NUMBER;
	  		  		 	 	  		OCR1BH = (Local_u16OutCompareValue_B >> TIMER_MASK_EIGHT_BIT);
	  		  		 	 	  		OCR1BL =  Local_u16OutCompareValue_B;

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER1_COMP_MODE == TIMER_OC1_DISCONNECTED
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_TOGGELE
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_CLEAR
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_SET
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B0);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER1_COMP_MODE selection is not correct"
#endif

#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B

	  		  	  		 	 	  Local_u16OutCompareValue_A = TIMER1_CTCMODE_COUNTS_NUMBER;

	  		  	  		 	 	  	OCR1AH = (Local_u16OutCompareValue_A >> TIMER_MASK_EIGHT_BIT);
	  		  	  		 	 	  	OCR1AL =  Local_u16OutCompareValue_A;
	  		  		 	 	  	Local_u16OutCompareValue_B = TIMER1_CTCMODE_COUNTS_NUMBER;
	  		  		 	 	  		OCR1BH = (Local_u16OutCompareValue_B >> TIMER_MASK_EIGHT_BIT);
	  		  		 	 	  		OCR1BL =  Local_u16OutCompareValue_B;

/*-----------------------------  Compare Match Output Mode --------------------------*/

#if								TIMER1_COMP_MODE == TIMER_OC1_DISCONNECTED
 		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
 		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
 		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif  		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_TOGGELE
	  		 	 	  	  		 	 	 TCCR1A |= (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_CLEAR

	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1A0);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1A1);
	  		 	 	  	  		 	 	 TCCR1A &=~ (TIMER_MASK_BIT<<TCCR1A_COM1B0);
	  		 	 	  	  		 	 	 TCCR1A  |= (TIMER_MASK_BIT<<TCCR1A_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#elif 		 	 	  	  		TIMER1_COMP_MODE == TIMER_OC1_SET
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1A0);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1A1);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B0);
	  		 	 	  	  		 	 	 TCCR1B |= (TIMER_MASK_BIT<<TCCR1B_COM1B1);
	  		  		 	 	  		 	Local_enuErrorState = ES_OK;

#else
#error  "The TIMER1_COMP_MODE selection is not correct"
#endif
#else
#error	"CHANNEL SELLECTION IS NOT CORRECT"
#endif

/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/

/*----------------------------- MODE SELLECTION IS NOT CORRECT --------------------------*/

#else
#error "The TIMER1_MODE selection is not correct"
#endif

/*----------------------------------------------------------------------------------------*/




	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER1_enuInterruptEnable.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : Enable the OVERFLOW and CLEAR COMPARE MATCH INTERRUPTS.
**---------------------------------------------------------------------------------------*/


ES_t TIMER1_enuInterruptEnable(void)
{
	ES_t Local_enuErrorState = ES_NOK;
/*NORMAL MODE*/
#if TIMER1_MODE == TIMER1_NORMAL_MODE
 	 //Enable the OVF Interrupt
 	 GIE_enu_Enable();
	 Local_enuErrorState = ES_OK;

 	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_TOIE1);
/*CTC_OCR1A MODE*/
#elif TIMER1_MODE == TIMER1_CTC_MODE_OCR1A
#if	TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
 	//Enable the CTC_A Interrupt
 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1A);
 		 GIE_enu_Enable();
 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B
 	 	//Enable the CTC_B Interrupt
 	 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 GIE_enu_Enable();
 	 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B
 	 	//Enable the CTC_A & CTC_B Interrupt
 	 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1A);
 	 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 GIE_enu_Enable();
 	 		 Local_enuErrorState = ES_OK;
#else
#error "TIMER1_CTC_MODE_CHANNEL SELECTION IS NOT CORRECT"
#endif
/*CTC_ICR1 MODE*/
#elif TIMER1_MODE == TIMER1_CTC_MODE_ICR1
#if	TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
 	//Enable the CTC_A Interrupt
 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1A);
 		 GIE_enu_Enable();
 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B
 	 	//Enable the CTC_B Interrupt
 	 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 GIE_enu_Enable();
 	 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B
 	 	//Enable the CTC_A & CTC_B Interrupt
 	 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1A);
 	 		 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 GIE_enu_Enable();
 	 		 Local_enuErrorState = ES_OK;
#else
#error "TIMER1_CTC_MODE_CHANNEL SELECTION IS NOT CORRECT"
#endif
#else
#error "TIMER1_MODE SELECTION IS NOT CORRECT"
#endif
	 return Local_enuErrorState ;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER1_enuInterruptDisable.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : Disable the OVERFLOW and CLEAR COMPARE MATCH INTERRUPTS.
**---------------------------------------------------------------------------------------*/

ES_t TIMER1_enuInterruptDisable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if TIMER1_MODE == TIMER1_NORMAL_MODE
 	 //Enable the OVF Interrupt
	 Local_enuErrorState = ES_OK;

 	 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_TOIE1);
#elif TIMER1_MODE == TIMER1_CTC_MODE_OCR1A
#if	TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
 	 	 //Disable the CTC Interrupt
 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1A);
 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B
 	 	 //Disable the CTC Interrupt
 	 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B
 	 	 //Disable the CTC Interrupt
 	 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1A);
 	 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 Local_enuErrorState = ES_OK;
#else
#error "TIMER1_CTC_MODE_CHANNEL SELECTION IS NOT CORRECT"
#endif
#elif TIMER1_MODE == TIMER1_CTC_MODE_ICR1
#if	TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
 	 	 //Disable the CTC Interrupt
 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1A);
 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B
 	 	 //Disable the CTC Interrupt
 	 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B
 	 	 //Disable the CTC Interrupt
 	 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1A);
 	 		 TIMSK &= ~(TIMER_MASK_BIT<<TIMSK_OCIE1B);
 	 		 Local_enuErrorState = ES_OK;
#else
#error "TIMER1_CTC_MODE_CHANNEL SELECTION IS NOT CORRECT"
#endif
#else
#error "TIMER1_MODE SELECTION IS NOT CORRECT"
      	 	 Local_enuErrorState = ES_NOK;

#endif
	 return Local_enuErrorState ;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER1_enuStartTimer.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler to start the timer.
**					IF TIMER0 on CTC mode, Set OC1 pin as output, Set the OCR0 Value, Enable CTC Interrupt.
**---------------------------------------------------------------------------------------*/


ES_t TIMER1_enuStartTimer(void)
{
	ES_t Local_enuErrorState=ES_NOK;
	/*----------------------------------------------------------------------------------------*/
	/**----------------------- Set the OC1 Pin as outputs (OC1B) PD4 || (OC1A) PD5  -----------------------------------**/

     #if	TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A
		//DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN5,DIO_U8OUTPUT);
	  		 Local_enuErrorState = ES_OK;
	 #elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_B
	 // 	DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN4,DIO_U8OUTPUT);
      	 		 Local_enuErrorState = ES_OK;
#elif TIMER1_CTC_MODE_CHANNEL	== CHANNEL_A_B
	//	DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN5,DIO_U8OUTPUT);
	//	DIO_enuSetPinDirection(DIO_U8PORT_D,DIO_U8PIN4,DIO_U8OUTPUT);
 	 		 Local_enuErrorState = ES_OK;
	 #else
	 #error "TIMER1_CTC_MODE_CHANNEL SELECTION IS NOT CORRECT"
      	 	 Local_enuErrorState = ES_NOK;
	 #endif



	/**----------------------- Selection TIMER1_PRESCALER -----------------------------------**/


	#if 	TIMER1_PRESCALER == TIMER_CLOCK_NO_PRESCHALER
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS10);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS11);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS12);
		  		 	Local_enuErrorState = ES_OK;

	#elif	TIMER1_PRESCALER == TIMER_CLOCK_8_PRESCHALER
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS10);
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS11);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS12);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER1_PRESCALER == TIMER_CLOCK_64_PRESCHALER
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS10);
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS11);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS12);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER1_PRESCALER == TIMER_CLOCK_256_PRESCHALER
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS10);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS11);
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS12);
		  		 	Local_enuErrorState = ES_OK;

	#elif TIMER1_PRESCALER == TIMER_CLOCK_1024_PRESCHALER
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS10);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS11);
				TCCR1B  |= (TIMER_MASK_BIT<<TCCR1B_CS12);
		  		 	Local_enuErrorState = ES_OK;

	#else
	#error "The TIMER0_PRESCALER selection is not correct"
		      	 	 Local_enuErrorState = ES_NOK;

	#endif

	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
**	Function Name   : TIMER1_enuStopTimer.
**	Return Type     : ES_t ENUM.
**	Arguments       : void.
**	Functionality   : SETTING THE TIMER Prescaler to TIMER_CLOCK_NO_CLOCK to stop the timer.
**---------------------------------------------------------------------------------------*/

ES_t TIMER1_enuStopTimer(void)
{
	ES_t Local_enuErrorState=ES_NOK;

/**----------------------- Selection TIMER1_PRESCALER -----------------------------------**/
/*----------------------------TIMER_CLOCK_NO_CLOCK-------------------------------------------*/
			    TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS10);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS11);
				TCCR1B &= ~(TIMER_MASK_BIT<<TCCR1B_CS12);
				Local_enuErrorState=ES_OK;
	return Local_enuErrorState;
}


/*--------------------------------------------------------------------------------------**
**	Function Name   : Timer1_enuSetCallBack.
**	Return Type     : ES_t ENUM.
**	Arguments       : The callback function, Index of the callback array, delay value in mile seconds .
**	Functionality   : .
**---------------------------------------------------------------------------------------*/

ES_t TIMER1_enuSetCallBackDelay( void( *Copy_pfunISRFun) (void),U8 Copy_U8Timer1IntIndex, U16 Copy_U16Timer1Delay)

{
	ES_t Local_enuErrorState=ES_NOK;
	TIMER1_pfunISRFun[Copy_U8Timer1IntIndex]= Copy_pfunISRFun;
	//DDRD= 1;
	TIMER1_U16DELAY_MILEOSECOND = Copy_U16Timer1Delay;
	Local_enuErrorState =ES_OK;
	return Local_enuErrorState;
}

/*--------------------------------------------------------------------------------------**
*--------------------------------------Timer 0 ISR-----------------------------------------------*
**---------------------------------------------------------------------------------------*/


ISR (VECT_TIMER1_OVF)
{
	if (TIMER1_pfunISRFun[TIMER1_OVF_CALLBACK_INT_INDEX] != NULL)
	{
		Global_U32CounterOVF1 ++;

		if (Global_U32CounterOVF1 == TIMER1_U32NUMBER_OF_OVERFLOW)
		{
			TCNT1H = (Global_U16IMER1_PreloadValue>>TIMER_MASK_EIGHT_BIT);
			TCNT1L = Global_U16IMER1_PreloadValue;

			TIMER1_pfunISRFun[TIMER1_OVF_CALLBACK_INT_INDEX]();
			Global_U32CounterOVF1 =0;
		}
	}
}

ISR (VECT_TIMER1_CTCA)
{

	if (TIMER1_pfunISRFun[TIMER1_CTCA_CALLBACK_INT_INDEX] != NULL)
	{
		Global_U32CounterCTC1A ++;
		Global_32TIMER1_CTCA_SecondsCounter=0;
		if (Global_U32CounterCTC1A == TIMER1_U16DELAY_MILEOSECOND)

		{
			TIMER1_pfunISRFun[TIMER1_CTCA_CALLBACK_INT_INDEX]();
			Global_32TIMER1_CTCA_SecondsCounter = 1;
			Global_U32CounterCTC1A =0;
		}
	}

}
/*USING CTC_B TO TRIGGER THE ADC, EVERY 100m second READ THE VALUE OF THE TEMP SENSOR AND
 *  GET THE READING OF THE ADC */
/*HERE THE INTERRUPT OF THE CTC_B OCCUR EACH 100m second*/
ISR (VECT_TIMER1_CTCB)
{
////////////////////////////////////////////////////////////////////////
	if (TIMER1_pfunISRFun[TIMER1_CTCB_CALLBACK_INT_INDEX] != NULL)
	{
	Global_U32CounterCTC1B ++;

		if (Global_U32CounterCTC1B == TIMER1_U16DELAY_MILEOSECOND)

		{
			TIMER1_pfunISRFun[TIMER1_CTCB_CALLBACK_INT_INDEX]();

			Global_U32CounterCTC1B =0;
		}
	}

}

/*---------------------------------------- THE END OF TIMER 1 ------------------------------------------------------------------------*/

