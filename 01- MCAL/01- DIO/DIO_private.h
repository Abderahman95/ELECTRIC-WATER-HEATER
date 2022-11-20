#ifndef _MCAL_DIO_PRIVATE_H_
#define _MCAL_DIO_PRIVATE_H_



#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)		0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)

#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0) 		0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC_D(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_V(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)

#define INIT_DDR_DIRECTION			 	        CONC_D(DIO_U8PinA7_Direction,DIO_U8PinA6_Direction,DIO_U8PinA5_Direction,DIO_U8PinA4_Direction,DIO_U8PinA3_Direction,DIO_U8PinA2_Direction,DIO_U8PinA1_Direction,DIO_U8PinA0_Direction)
#define INIT_PORT_VALUE		 			        CONC_V(DIO_U8PinA7_Value,DIO_U8PinA6_Value,DIO_U8PinA5_Value,DIO_U8PinA4_Value,DIO_U8PinA3_Value,DIO_U8PinA2_Value,DIO_U8PinA1_Value,DIO_U8PinA0_Value)

#define DIO_U8PORT_A			0
#define DIO_U8PORT_B			1
#define DIO_U8PORT_C			2
#define DIO_U8PORT_D			3

#define DIO_U8PIN0  			0
#define DIO_U8PIN1		    	1
#define DIO_U8PIN2		    	2
#define DIO_U8PIN3		    	3
#define DIO_U8PIN4		    	4
#define DIO_U8PIN5		    	5
#define DIO_U8PIN6		    	6
#define DIO_U8PIN7		    	7

#define DIO_U8INPUT 			0
#define DIO_U8OUTPUT			1

#define DIO_U8LOW 		    	0
#define DIO_U8HIGH		    	1

#define DIO_U8FLOAT 			0
#define DIO_U8PULL_UP			1

#define DIO_MASK_BIT 			1



#endif /* _MCAL_DIO_PRIVATE_H_ */
