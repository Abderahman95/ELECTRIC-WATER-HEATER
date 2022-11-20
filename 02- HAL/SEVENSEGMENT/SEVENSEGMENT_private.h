#ifndef _HAL_SEVENSEGMENT_PRIVATE_H_
#define _HAL_SEVENSEGMENT_PRIVATE_H_

#define COMMON_CATHOND			10
#define COMMON_ANODE			20
#define NOT_CONNECTED			30

#define ZeroValue				0

#define TWO_BITS_SHIFT			2
#define FOUR_BITS_SHIFT    		4
#define SIX_BITS_SHIFT      	6
#define EIGHT_BITS_SHIFT      	8
#define TEN_BITS_SHIFT          10
#define TWELVE_BITS_SHIFT       12
#define SSG_CHECKVALUE			0X1555
/*0001 0101 0101 0101*/

 static  U8 SEVENSEGMENT_AU8COMMON_CATHODE_VALUES  [ ]= {
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 0x3F,0x06,0x5B,0x4F,0x66,
																		 0x6D,0x7D,0x07,0x7F,0x6F,
																		 0x77,0x7C,0x39,0x5E,0x79,0x71
 };

#endif /* _HAL_SEVENSEGMENT_PRIVATE_H_ */
