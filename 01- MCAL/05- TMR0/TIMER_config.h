#ifndef _MCAL_TIMER_CONFIG_H_
#define _MCAL_TIMER_CONFIG_H_


/*Please select the TIMER 0 Prescaler from these choices:
 *
														 * TIMER_CLOCK_NO_CLOCK
														 * TIMER_CLOCK_NO_PRESCHALER
														 * TIMER_CLOCK_8_PRESCHALER
														 * TIMER_CLOCK_64_PRESCHALER
														 * TIMER_CLOCK_256_PRESCHALER
														 * TIMER_CLOCK_1024_PRESCHALER
														 * TIMER_CLOCK_EXTERNAL_FALLING_EDGE
														 * TIMER_CLOCK_EXTERNAL_RISING_EDGE 							*/

#define TIMER0_PRESCALER 									TIMER_CLOCK_64_PRESCHALER


/*Please select the TIMER 0 Mode from these choices:
 *
														 * TIMER0_NORMAL_MODE
														 * TIMER0_PHASE_CORRECT_PWM
														 * TIMER0_CTC_MODE
														 * TIMER0_FAST_PWM         											*/

#define TIMER0_MODE 										TIMER0_CTC_MODE

/*Please select the TIMER 0  Compare Output Mode from these choices:
 *
														 * TIMER_OC0_DISCONNECTED
														 * TIMER_OC0_TOGGELE //  TIMER_OCX_RESERVED
														 * TIMER_OC0_CLEAR
														 * TIMER_OC0_SET	       							*/
#define TIMER0_COMP_MODE 									TIMER_OC0_TOGGELE


/*--------------------------------------------------------------------------------------**
*----------------------------------- TIMER1 configuration--------------------------------*
**---------------------------------------------------------------------------------------*/


/*Please select the TIMER 0 Prescaler from these choices:
 *
														 * TIMER_CLOCK_NO_CLOCK
														 * TIMER_CLOCK_NO_PRESCHALER
														 * TIMER_CLOCK_8_PRESCHALER
														 * TIMER_CLOCK_64_PRESCHALER
														 * TIMER_CLOCK_256_PRESCHALER
														 * TIMER_CLOCK_1024_PRESCHALER
														 * TIMER_CLOCK_EXTERNAL_FALLING_EDGE
														 * TIMER_CLOCK_EXTERNAL_RISING_EDGE 							*/

#define TIMER1_PRESCALER 									TIMER_CLOCK_64_PRESCHALER


/*Please select the TIMER 1 Mode from these choices:
 *
														 * TIMER1_NORMAL_MODE
														 * TIMER1_PHASE_CORRECT_PWM
														 * TIMER1_CTC_MODE_OCR1A
														 * TIMER1_CTC_MODE_ICR1
														 * TIMER1_FAST_PWM         											*/

#define TIMER1_MODE 										TIMER1_CTC_MODE_OCR1A
/*select between channels :
 * 														*CHANNEL_A
 * 														*CHANNEL_B
 * 														*CHANNEL_A_B															*/

#define TIMER1_CTC_MODE_CHANNEL								CHANNEL_A_B

/*Please select the TIMER 1  Compare Output Mode from these choices:
 *
														 * TIMER_OC1_DISCONNECTED
														 * TIMER_OC1_TOGGELE //  TIMER_OCX_RESERVED
														 * TIMER_OC1_CLEAR
														 * TIMER_OC1_SET	       							*/
#define TIMER1_COMP_MODE 									TIMER_OC1_TOGGELE



/*--------------------------------------------------------------------------------------**
*----------------------------------- TIMER2 configuration--------------------------------*
**---------------------------------------------------------------------------------------*/

/*Please select the TIMER 2 Prescaler from these choices:
 *
														 * TIMER_CLOCK_NO_CLOCK
														 * TIMER_CLOCK_NO_PRESCHALER
														 * TIMER_CLOCK_8_PRESCHALER
														 * TIMER_CLOCK_64_PRESCHALER
														 * TIMER_CLOCK_256_PRESCHALER
														 * TIMER_CLOCK_1024_PRESCHALER
														 * TIMER_CLOCK_EXTERNAL_FALLING_EDGE
														 * TIMER_CLOCK_EXTERNAL_RISING_EDGE 							*/

#define TIMER2_PRESCALER 									TIMER_CLOCK_64_PRESCHALER


/*Please select the TIMER 2 Mode from these choices:
 *
														 * TIMER2_NORMAL_MODE
														 * TIMER2_PHASE_CORRECT_PWM
														 * TIMER2_CTC_MODE
														 * TIMER2_FAST_PWM         											*/

#define TIMER2_MODE 										TIMER2_CTC_MODE

/*Please select the TIMER 2  Compare Output Mode from these choices:
 *
														 * TIMER_OC2_DISCONNECTED
														 * TIMER_OC2_TOGGELE //  TIMER_OCX_RESERVED
														 * TIMER_OC2_CLEAR
														 * TIMER_OC2_SET	       							*/
#define TIMER2_COMP_MODE 									TIMER_OC2_TOGGELE

/**---------------------------------------------------------------------------------------------------*/
/*--------------------------------------------- TIMER0 configuration ----------------------------------------*/


#define TIMER0_DESIRED_TIME									1/1000
#define TIMER0_F_CPU										16000000
#define TIMER0_RESOLUTION_COUNTS 							256

#define TIMER0_CLOCK 									 TIMER0_F_CPU / TIMER0_PRESCALER
#define TIMER0_ONE_CLOCK											1 / TIMER0_CLOCK

#define TIMER0_OVERFLOW									TIMER0_ONE_CLOCK	* TIMER0_RESOLUTION_COUNTS

#define TIMER0_NUMBER_OVERFLOW 							(TIMER0_DESIRED_TIME / TIMER0_OVERFLOW)
#define TIMER_OCR0_COUNTS_NUMBER						(TIMER0_NUMBER_OVERFLOW * TIMER0_RESOLUTION_COUNTS)

#define TIMER0_U32NUMBER_OF_OVERFLOW					(U32)(TIMER0_DESIRED_TIME / TIMER0_OVERFLOW)
#define TIMER0_FRECTION									((U8) TIMER0_U32NUMBER_OF_OVERFLOW) - TIMER0_U32NUMBER_OF_OVERFLOW
#define TIMER0_U32NUMBER_OF_TICKS_FRECTION   			TIMER0_FRECTION * TIMER0_RESOLUTION_COUNTS
#define TIMER0_U8PRELOAD_VALUE							(U8)( TIMER0_RESOLUTION_COUNTS - TIMER0_U32NUMBER_OF_TICKS_FRECTION )


/**---------------------------------------------------------------------------------------------------*/
/**-------Timer One is needed to trigger the ADC to read the Temp every 100m second-------------------*
 * --------Then, NUMBER_COUNT= (DISRED_TIME * F_CPU)/PRESCALER ---------------------------------------*
 * ----------------- NUMBER_COUNT = (0.1* 16000000)/256 =6250 ----------------------------------------*/

#define TIMER1_DESIRED_TIME									(F32)	100/1000
#define TIMER1_F_CPU										16000000
#define TIMER1_RESOLUTION_COUNTS 							65536
/*fOC1A = fCLK /(2*prescaler* (1+OC1A)*/

#define TIMER1OCR1A_COUNTS_NUMBER 						((TIMER1_F_CPU * TIMER1_DESIRED_TIME) / (2 * TIMER1_PRESCALER )-1)
/**---------------------------------------- CALCULATION OF THE NUMBER OF COUNTS NEEDED IN CTC MODE --------------------------------------------**/
#define TIMER1_CTCMODE_COUNTS_NUMBER					((TIMER1_DESIRED_TIME * TIMER1_F_CPU) / (TIMER1_PRESCALER))
/**--------------------------- The Next Calculation is responsible for getting the Preload Value for OVERFLOW MODE-----------------------------**/

#define TIMER1_CLOCK 									 TIMER1_F_CPU / TIMER1_PRESCALER
#define TIMER1_ONE_CLOCK											1 / TIMER1_CLOCK

#define TIMER1_OVERFLOW									TIMER1_ONE_CLOCK	* TIMER1_RESOLUTION_COUNTS

#define TIMER1_NUMBER_OVERFLOW 							(TIMER1_DESIRED_TIME / TIMER1_OVERFLOW)
#define TIMER1OCR1_COUNTS_NUMBER						(TIMER1_NUMBER_OVERFLOW * TIMER1_RESOLUTION_COUNTS)

#define TIMER1_U32NUMBER_OF_OVERFLOW					(F32)(TIMER1_DESIRED_TIME / TIMER1_OVERFLOW)
#define TIMER1_FRECTION									((U8) TIMER1_U32NUMBER_OF_OVERFLOW) - TIMER1_U32NUMBER_OF_OVERFLOW
#define TIMER1_U32NUMBER_OF_TICKS_FRECTION   			(U16) (TIMER1_FRECTION * TIMER1_RESOLUTION_COUNTS)
#define TIMER1_U16PRELOAD_VALUE							(U16)( TIMER1_RESOLUTION_COUNTS - TIMER1_U32NUMBER_OF_TICKS_FRECTION )



/*--------------------------------------------- TIMER2 configuration ----------------------------------------*/


#define TIMER2_DESIRED_TIME									1/1000
#define TIMER2_F_CPU										16000000
#define TIMER2_RESOLUTION_COUNTS 							256

#define TIMER2_CLOCK 									 TIMER2_F_CPU / TIMER2_PRESCALER
#define TIMER2_ONE_CLOCK											1 / TIMER2_CLOCK

#define TIMER2_OVERFLOW									TIMER2_ONE_CLOCK	* TIMER2_RESOLUTION_COUNTS

#define TIMER2_NUMBER_OVERFLOW 							(TIMER2_DESIRED_TIME / TIMER2_OVERFLOW)
#define TIMER2OCR0_COUNTS_NUMBER						(TIMER2_NUMBER_OVERFLOW * TIMER2_RESOLUTION_COUNTS)

#define TIMER2_U32NUMBER_OF_OVERFLOW					(U32)(TIMER2_DESIRED_TIME / TIMER2_OVERFLOW)
#define TIMER2_FRECTION									((U8) TIMER2_U32NUMBER_OF_OVERFLOW) - TIMER2_U32NUMBER_OF_OVERFLOW
#define TIMER2_U32NUMBER_OF_TICKS_FRECTION   			TIMER2_FRECTION * TIMER2_RESOLUTION_COUNTS
#define TIMER2_U8PRELOAD_VALUE							(U8)( TIMER2_RESOLUTION_COUNTS - TIMER2_U32NUMBER_OF_TICKS_FRECTION )




#endif /* _MCAL_TIMER_CONFIG_H_ */
