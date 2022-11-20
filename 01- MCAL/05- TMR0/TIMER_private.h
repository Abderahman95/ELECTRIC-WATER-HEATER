#ifndef _MCAL_TIMER_PRIVATE_H_
#define _MCAL_TIMER_PRIVATE_H_


/*----------------------------------------------------------------------------*/
/*------------------------ TCCR0 [BITS ORDER] --------------------------------*/
/*----------------------------------------------------------------------------*/

#define TCCR0_FOC0				      7
#define TCCR0_WGM00				      6
#define TCCR0_COM01				      5
#define TCCR0_COM00				      4
#define TCCR0_WGM01				      3
#define TCCR0_CS02				      2
#define TCCR0_CS01				      1
#define TCCR0_CS00				      0


/*----------------------------------------------------------------------------*/
/*------------------------ TTCR1A [BITS ORDER] -------------------------------*/
/*----------------------------------------------------------------------------*/

#define TCCR1A_COM1A1										7
#define TCCR1A_COM1A0                                       6
#define TCCR1A_COM1B1                                       5
#define TCCR1A_COM1B0                                       4
#define TCCR1A_FOC1A                                        3
#define TCCR1A_FOC1B                                        2
#define TCCR1A_WGM11                                        1
#define TCCR1A_WGM10                                        0

/*----------------------------------------------------------------------------*/
/*------------------------ TTCR1B [BITS ORDER] -------------------------------*/
/*----------------------------------------------------------------------------*/

#define TCCR1B_ICNC1                                        7
#define TCCR1B_ICES1                                        6
#define TCCR1B_WGM13                                        4
#define TCCR1B_WGM12                                        3
#define TCCR1B_CS12                                         2
#define TCCR1B_CS11                                         1
#define TCCR1B_CS10                                         0
/*----------------------------------------------------------------------------*/
/*------------------------ TCCR2 [BITS ORDER] --------------------------------*/
/*----------------------------------------------------------------------------*/

#define TCCR2_FOC2				      7
#define TCCR2_WGM20				      6
#define TCCR2_COM21				      5
#define TCCR2_COM20				      4
#define TCCR2_WGM21				      3
#define TCCR2_CS22				      2
#define TCCR2_CS21				      1
#define TCCR2_CS20				      0
#define ASSR_AS2					  3

/*----------------------------------------------------------------------------*/
/*------------------------- TIMSK [BITS ORDER] -------------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMSK_OCIE2				      7
#define TIMSK_TOIE2				      6
#define TIMSK_TICIE1			      5
#define TIMSK_OCIE1A			      4
#define TIMSK_OCIE1B			      3
#define TIMSK_TOIE1				      2
#define TIMSK_OCIE0				      1
#define TIMSK_TOIE0				      0
/*----------------------------------------------------------------------------*/
/*----------------------------- TIFR [BITS ORDER] ----------------------------*/
/*----------------------------------------------------------------------------*/
#define TIFR_OCF2      			      7
#define TIFR_TOV2      			      6
#define TIFR_ICF1      			      5
#define TIFR_OCF1A     			      4
#define TIFR_OCF1B      			  3
#define TIFR_TOV1      			      2
#define TIFR_OCF0      			      1
#define TIFR_TOV0      			      0
/*----------------------------------------------------------------------------*/

#define AASR_AS2			   		  3

/*----------------------------- TIME [PRESCALER CONFIGURATION] ---------------*/
/*----------------------------------------------------------------------------*/

#define 	TIMER_CLOCK_NO_CLOCK					0
#define		TIMER_CLOCK_NO_PRESCHALER				1
#define		TIMER_CLOCK_8_PRESCHALER				8
#define		TIMER_CLOCK_64_PRESCHALER				64
#define		TIMER_CLOCK_256_PRESCHALER				256
#define		TIMER_CLOCK_1024_PRESCHALER			    1024
#define		TIMER_CLOCK_EXTERNAL_FALLING_EDGE		6
#define		TIMER_CLOCK_EXTERNAL_RISING_EDGE		7
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER0 [MODES] -------------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMER0_NORMAL_MODE                          0
#define TIMER0_PHASE_CORRECT_PWM                    1
#define TIMER0_CTC_MODE                             2
#define TIMER0_FAST_PWM                             3

/*----------------------------- TIMER0 [OCX Pin Mode] -------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMER_OC0_DISCONNECTED                      0
#define TIMER_OC0_TOGGELE                           1
#define TIMER_OC0_RESERVED                          1
#define TIMER_OC0_CLEAR                             2
#define TIMER_OC0_SET	                            3
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER1 [MODES] ----------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMER1_NORMAL_MODE                          0
#define TIMER1_PHASE_CORRECT_PWM                    1
#define TIMER1_CTC_MODE_OCR1A                       2
#define TIMER1_CTC_MODE_ICR1                        3
#define TIMER1_FAST_PWM                             4
/*----------------------------------------------------------------------------*/
/*----------------------------- TIMER1 [CHANNELS] ----------------------------*/
#define CHANNEL_A									1
#define CHANNEL_B									2
#define CHANNEL_A_B									3

/*----------------------------------------------------------------------------*/
/*----------------------------- TIMER1 [OCX Pin Mode] ----------------------------*/
/*----------------------------------------------------------------------------*/


#define TIMER_OC1_DISCONNECTED                      0
#define TIMER_OC1_TOGGELE                           1
#define TIMER_OC1_RESERVED                          1
#define TIMER_OC1_CLEAR                             2
#define TIMER_OC1_SET	                            3
/*----------------------------------------------------------------------------*/
/*----------------------------- TIMER2 [MODES] ----------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMER2_NORMAL_MODE                          0
#define TIMER2_PHASE_CORRECT_PWM                    1
#define TIMER2_CTC_MODE                             2
#define TIMER2_FAST_PWM                             3
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER0 [OCX Pin Mode] ----------------------------*/
/*----------------------------------------------------------------------------*/


#define TIMER_OC2_DISCONNECTED                      0
#define TIMER_OC2_TOGGELE                           1
#define TIMER_OC2_RESERVED                          1
#define TIMER_OC2_CLEAR                             2
#define TIMER_OC2_SET	                            3
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER0 [OVERFLOW INTERRUPT] ----------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMER0_OVF_INTERRUPT_DISABLE  				0
#define TIMER0_OVF_INTERRUPT_ENABLE   				1
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER0 [CLEAR TIMER COMPARE MATCH INTERRUPT] --------------*/
/*----------------------------------------------------------------------------*/

#define TIMER0_CTC_INTERRUPT_DISABLE  				2
#define TIMER0_CTC_INTERRUPT_ENABLE   				3
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER0 [CALLBACK] ----------------------------*/
/*----------------------------------------------------------------------------*/

//#define TIMER0_DELAY_CALLBACK						0
#define TIMER0_OVF_CALLBACK_INT_INDEX				0
#define TIMER0_CTC_CALLBACK_INT_INDEX				1
#define TIMER0_CALL_BACK							2
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER1 [CALLBACK] ----------------------------*/
/*----------------------------------------------------------------------------*/

//#define TIMER1_DELAY_CALLBACK						0
#define TIMER1_OVF_CALLBACK_INT_INDEX				0
#define TIMER1_CTCA_CALLBACK_INT_INDEX				1
#define TIMER1_CTCB_CALLBACK_INT_INDEX				2
#define TIMER1_CALL_BACK							3
/*----------------------------------------------------------------------------*/

/*----------------------------- TIMER2 [CALLBACK] ----------------------------*/
/*----------------------------------------------------------------------------*/

//#define TIMER2_DELAY_CALLBACK						0
#define TIMER2_OVF_CALLBACK_INT_INDEX				0
#define TIMER2_CTC_CALLBACK_INT_INDEX				1
#define TIMER2_CALL_BACK							2
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/*----------------------------------- [MASKING] -------------------------------*/
/*----------------------------------------------------------------------------*/

#define TIMER_MASK_BIT								1
#define TIMER_MASK_EIGHT_BIT						8
/*----------------------------------------------------------------------------*/

#endif /* _MCAL_TIMER_PRIVATE_H_ */
