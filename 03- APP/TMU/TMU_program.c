#include "TYPES.h"
#include "ERROR_STATE.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "GIE_interface.h"
#include "interrupt.h"
#include "DIO_register.h"

//#include "TIMER_interface.h"

#include "TMU_config.h"
#include "TMU_private.h"
#include "TMU_interface.h"


static U16 Global_U16CounterENTERCTCISR=0;
static U16 Global_U16CounterCTC =0;
TCB_t TASKS[MAX_TASKS_NUMBER];
ES_t TMU_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

/*------------------------- TIMER0 SETTING ---------------------------*/

	TCCR0|=(TIMER_MASK_BIT<<TCCR0_CS02);
	TCCR0&=~(TIMER_MASK_BIT<<TCCR0_CS01);
	TCCR0|=(TIMER_MASK_BIT<<TCCR0_CS00);
	TCCR0|=(TIMER_MASK_BIT<<TCCR0_WGM01);

#if TICK_TIME <= MAX_TICK_TIME && TICK_TIME >=MIN_TICK_TIME

	OCR0 = (TICK_TIME * OCRN_COUNTS);
	Global_U16CounterENTERCTCISR =1;
	Global_U16CounterCTC =1;
#elif TICK_TIME > MAX_TICK_TIME
	U8 Local_U8MaxNumber, Local_U8Counter;
	for(Local_U8Counter=1; Local_U8Counter<= MAX_TICK_TIME; Local_U8Counter++)
	{
		if(TICK_TIME % Local_U8Counter == TMU_ZERO_NUMBER)
			Local_U8MaxNumber =Local_U8Counter;
	}
	OCR0 = (Local_U8MaxNumber * OCRN_COUNTS);
	DDRB=OCR0;
	Global_U16CounterENTERCTCISR =(TICK_TIME / Local_U8MaxNumber);
	Global_U16CounterCTC = Global_U16CounterENTERCTCISR;
#else
#error	"TICK_TIME SELECTION IS NOT CORRECT"
#endif

	return Local_enuErrorState;

}

ES_t TMU_enuCreateTask(void(*Copy_pfunTask)(void),U8 Copy_U8Priority, U8 Copy_U8Periodicity)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pfunTask !=NULL)
	{
		TASKS[Copy_U8Priority].Pfun=Copy_pfunTask;
		TASKS[Copy_U8Priority].priodicity=Copy_U8Periodicity;
		TASKS[Copy_U8Priority].counter=Copy_U8Periodicity-1;
		TASKS[Copy_U8Priority].State= READY;

	}
	else
		Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}


ES_t TMU_enuSuspendTask(U8 Copy_U8Priority)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_U8Priority	< MAX_TASKS_NUMBER)
	{
		TASKS[Copy_U8Priority].State= SUSPEND;
	}

	return Local_enuErrorState;
}
ES_t TMU_enuResumeTask (U8 Copy_U8Priority)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_U8Priority< MAX_TASKS_NUMBER)
		{
			TASKS[Copy_U8Priority].State= READY;
			TASKS[Copy_U8Priority].counter= TASKS[Copy_U8Priority].priodicity; //=0;

		}
	return Local_enuErrorState;
}




ES_t TMU_enuDeleteTask (U8 Copy_U8Priority)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_U8Priority< MAX_TASKS_NUMBER)
		{
			TASKS[Copy_U8Priority].State= SUSPEND;
			TASKS[Copy_U8Priority].Pfun= NULL;

		}
	return Local_enuErrorState;
}



ES_t TMU_enuStartScheduler(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	 //Enable the CTC Interrupt
	 TIMSK |= (TIMER_MASK_BIT<<TIMSK_OCIE0);
	 GIE_enu_Enable();
	 while(1);


	return Local_enuErrorState;
}

/*

ISR (VECT_TIMER0_CTC)
{
		Global_U16CounterCTC --;

	if (Global_U16CounterCTC ==0)
	{
		// scheduler
		for(U8 Local_U8Counter=0; Local_U8Counter< MAX_TASKS_NUMBER ; Local_U8Counter++)
		{
			if(TASKS[Local_U8Counter].Pfun !=NULL && TASKS[Local_U8Counter].counter ==0 &&TASKS[Local_U8Counter].State ==READY)
			{
				TASKS[Local_U8Counter].Pfun();
				TASKS[Local_U8Counter].counter= TASKS[Local_U8Counter].priodicity-1;

			}
			else
			{
				TASKS[Local_U8Counter].counter--;

			}
		}
		Global_U16CounterCTC = Global_U16CounterENTERCTCISR;
	}

}
*/
