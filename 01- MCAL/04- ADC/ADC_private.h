#ifndef _MCAL_ADC_PRIVATE_H_
#define _MCAL_ADC_PRIVATE_H_


#define AREF_REFERENCE 			             						1
#define AVCC_REFERENCE			             						2
#define INTERNAL_REFERENCE 		             				        3

#define LEFT_ADJUSMENT 					       						4
#define RIGHT_ADJUSMENT 					  						5

#define PRESCALER_2													6
#define PRESCALER_4													7
#define PRESCALER_8													8
#define PRESCALER_16												16
#define PRESCALER_32												32
#define PRESCALER_64												64
#define PRESCALER_128												128

#define TRIGGER_SOURCE_MAXNUMBER 					                7
#define CHANNEL_MAXNUMBER									    	31
#define CHANNEL_MASKING_ZERO						     ~0x1F  //~0x1F //0xE0 //0b1110000
#define AUTO_TRIGGER_MASKING_ZERO	 					 0x1F  //0x1F  //0b00011111
 #define ADC_MASK_BIT 												1




 #endif /* _MCAL_ADC_PRIVATE_H_ */
