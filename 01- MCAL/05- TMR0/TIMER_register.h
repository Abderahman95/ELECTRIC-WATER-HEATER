#ifndef _MCAL_TIMER_REGISTER_H_
#define _MCAL_TIMER_REGISTER_H_


/*----------------------------------- TIMER ZERO Registers --------------------------------------*/

/***************THE Timer0 Control Register � TCCR0 [ADDRESS]***************/
#define		TCCR0					*((volatile U8*)(0x53))
/***************THE Timer0 Register � TCNT0 [ADDRESS]***************/
#define		TCNT0					*((volatile U8*)(0x52))
/***************THE TIMER0 Output Compare Register � OCR0 [ADDRESS]***************/
#define		OCR0					*((volatile U8*)(0x5c))
/***************THE Timer0 Interrupt Mask Register � TIMSK [ADDRESS]***************/
#define		TIMSK					*((volatile U8*)(0x59))
/***************THE Timer0 Interrupt Flag Register � TIFR [ADDRESS]***************/
#define		TIFR					*((volatile U8*)(0x58))

/*----------------------------------- TIMER ONE Registers --------------------------------------*/

/***************THE TIMER1 Output Compare Register � TCCR1A [ADDRESS]***************/
#define		TCCR1A					*((volatile U8*)(0x4F))
/***************THE TIMER1 Output Compare Register � TCCR1B [ADDRESS]***************/
#define		TCCR1B					*((volatile U8*)(0x4E))
/***************THE TIMER1 Output Compare Register � TCNT1H [ADDRESS]***************/
#define		TCNT1H					*((volatile U8*)(0x4D))
/***************THE TIMER1 Output Compare Register � TCNT1L [ADDRESS]***************/
#define		TCNT1L					*((volatile U8*)(0x4C))
/***************THE TIMER1 Output Compare Register � OCR1AH [ADDRESS]***************/
#define		OCR1AH					*((volatile U8*)(0x4B))
/***************THE TIMER1 Output Compare Register � OCR1AL [ADDRESS]***************/
#define		OCR1AL					*((volatile U8*)(0x4A))
/***************THE TIMER1 Output Compare Register � OCR1BH [ADDRESS]***************/
#define		OCR1BH					*((volatile U8*)(0x49))
/***************THE TIMER1 Output Compare Register � OCR1BL [ADDRESS]***************/
#define		OCR1BL					*((volatile U8*)(0x48))
/***************THE TIMER1 Output Compare Register � ICR1H [ADDRESS]***************/
#define		ICR1H					*((volatile U8*)(0x47))
/***************THE TIMER1 Output Compare Register � ICR1L [ADDRESS]***************/
#define		ICR1L					*((volatile U8*)(0x46))

/*----------------------------------- TIMER TWO Registers --------------------------------------*/

/***************THE TIMER0 Output Compare Register � ASSR [ADDRESS]***************/
#define		ASSR					*((volatile U8*)(0x42))
/***************THE TIMER0 Output Compare Register � OCR2 [ADDRESS]***************/
#define		OCR2					*((volatile U8*)(0x43))
/***************THE Timer0 Register � TCNT2 [ADDRESS]***************/
#define		TCNT2					*((volatile U8*)(0x44))
/***************THE Timer2 Control Register � TCCR0 [ADDRESS]***************/
#define		TCCR2					*((volatile U8*)(0x45))

/*------------------------------------------------------------------------------------------------*/



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



#endif /* _MCAL_TIMER_REGISTER_H_ */
