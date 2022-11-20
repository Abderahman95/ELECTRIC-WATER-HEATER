#ifndef _MCAL_TIMER_INTERFACE_H_
#define _MCAL_TIMER_INTERFACE_H_



ES_t TIMER0_enuInit(void);
ES_t TIMER0_enuStartTimer(void);
ES_t TIMER0_enuInterruptEnable(void);
ES_t TIMER0_enuInterruptDisable(void);
ES_t TIMER0_enuSetCallBackDelay( void( *Copy_pfunISRFun) (void),U8 Copy_U8Timer0IntIndex, U16 Copy_U16Timer0Delay);
ES_t TIMER0_enuStopTimer(void);

/*-------------------------------------- TIMER ONE FUNCTIONS --------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

ES_t TIMER1_enuInit(void);
ES_t TIMER1_enuStartTimer(void);
ES_t TIMER1_enuInterruptEnable(void);
ES_t TIMER1_enuInterruptDisable(void);
ES_t TIMER1_enuSetCallBackDelay( void( *Copy_pfunISRFun) (void),U8 Copy_U8Timer0IntIndex, U16 Copy_U16Timer0Delay);
ES_t TIMER1_enuStopTimer(void);

/*-------------------------------------- TIMER TWO FUNCTIONS --------------------------------*/
/*-----------------------------------------------------------------------------------------------*/


ES_t TIMER2_enuInit(void);
ES_t TIMER2_enuStartTimer(void);
ES_t TIMER2_enuInterruptEnable(void);
ES_t TIMER2_enuInterruptDisable(void);
ES_t TIMER2_enuSetCallBackDelay( void( *Copy_pfunISRFun) (void),U8 Copy_U8Timer2IntIndex, U16 Copy_U16Timer2Delay);
ES_t TIMER2_enuStopTimer(void);


//ES_t Timer0_enuSetCallBack( void(*Copy_pfunISRFun)(void),U8 Copy_U8TimerIntIndex)

//ES_t Timer0_enuSetCallBack( void(*Copy_pfunISRFun)(void),U8 Copy_U8TimerIntIndex, U8 Copy_U8TimerDelay)
//ES_t TIMER0_enuCallBackCTC(volatile void( *Copy_pfunAppFun) (void));


#define TIMER_OVF0_INTERRUPT_INDEX		0
#define TIMER_CTC0_INTERRUPT_INDEX		1
#define TIMER_OVF1_INTERRUPT_INDEX		0
#define TIMER_CTC1A_INTERRUPT_INDEX		1
#define TIMER_CTC1B_INTERRUPT_INDEX		2

#define TIMER_OVF2_INTERRUPT_INDEX		0
#define TIMER_CTC2_INTERRUPT_INDEX		1
#define TIMER1_100_MILE_SECOND			1

#endif /* _MCAL_TIMER_INTERFACE_H_ */
