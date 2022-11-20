#ifndef _MCAL_ADC_REGISTER_H_
#define _MCAL_ADC_REGISTER_H_
#include "ADC_private.h"


/***************THE ADC Multiplexer Selection  REGISTER: ADMUX [ADDRESS & BITS ORDER]***************/
#define		ADMUX	         		*((volatile U8*)(0x27))

#define ADMUX_REFS1				      7
#define ADMUX_REFS0				      6
#define ADMUX_ADLAR				      5
#define ADMUX_MUX4				      4
#define ADMUX_MUX3				      3
#define ADMUX_MUX2				      2
#define ADMUX_MUX1				      1
#define ADMUX_MUX0				      0

/***************THE ADC Control and Status REGISTER: ADCSRA [ADDRESS & BITS ORDER]***************/
#define		ADCSRA		        	*((volatile U8*)(0x26))

#define ADCSRA_ADEN			          7
#define ADCSRA_ADSC			          6
#define ADCSRA_ADATE		          5
#define ADCSRA_ADIF			          4
#define ADCSRA_ADIE			          3
#define ADCSRA_ADPS2		          2
#define ADCSRA_ADPS1		          1
#define ADCSRA_ADPS0		          0

/***************THE ADC Special Function IO REGISTER: SFIOR [ADDRESS & BITS ORDER]***************/
#define		SFIOR				    *((volatile U8*)(0x50))

#define SFIOR_ADTS2			          7
#define SFIOR_ADTS1			          6
#define SFIOR_ADTS0		           	  5
#define SFIOR_RESERVED		 	      4
#define SFIOR_ACME			          3
#define SFIOR_POD		              2
#define SFIOR_PSR2		              1
#define SFIOR_PSR10		              0

/***************THE ADC Data Low REGISTER: ADCL [ADDRESS & BITS ORDER]***************/
#define		ADCL			    	*((volatile U8*)(0x24))
#define ADCL_LEFT					 6
/***************THE ADC Data High REGISTER: ADCH [ADDRESS & BITS ORDER]***************/
#define		ADCH				    *((volatile U8*)(0x25))
#define ADCH_RIGHT					 8
#define ADCH_LEFT 					 2


#endif /* _MCAL_ADC_REGISTER_H_ */
