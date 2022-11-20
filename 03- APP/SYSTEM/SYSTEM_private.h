#ifndef _APP_SYSTEM_PRIVATE_H_
#define _APP_SYSTEM_PRIVATE_H_



#define		MCUCR					*((volatile U8*)(0x35))

#define MCUCR_SE								7
#define MCUCR_SM2								6
#define MCUCR_SM1								5
#define MCUCR_SM0								4


#define NUM_OF_TEMP_MEASURES 					10
#define FIVE_TEMP_DEGREE						5
#define INITIAL_DESIRED_TEMP 					60
#define MAXIMUM_TEMP							75
#define MINIMUM_TEMP							35
#define TIMER0_CTC_INDEX						1
#define TIMER0_DELAY_ONE_SECOND					1000
#define TIMER1_DELAY_FIVE_SECONDS				50
#define FIVE_SECONDS							5000
#define ZERO_VALUE								0
#define TEMP_UP_SWITCH							0
#define TEMP_DOWN_SWITCH						1
#define ON_OFF_SWITCH							2
#define OFF_STATE								0
#define ON_STATE								1
#define SETTINT_STATE							2
#define NOT_RISED								0
#define RISED									1


#endif /* _APP_SYSTEM_PRIVATE_H_ */
