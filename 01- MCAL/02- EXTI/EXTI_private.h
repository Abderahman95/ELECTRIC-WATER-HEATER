#ifndef _MCAL_EXTI_PRIVATE_H_
#define _MCAL_EXTI_PRIVATE_H_


#define MCUCR     		 *((volatile U8*)0x55)
#define MCUCSR    		 *((volatile U8*)0x54)
#define GICR      		 *((volatile U8*)0x5B)
#define GIFR      		 *((volatile U8*)0x5A)



enum
{
	LOW_LEVEL,
	ANY_LOGICAL,
	FALLING,
	RISING,

	DISABLED = 0,
	ENABLED,

	INT0=0,
	INT1,
	INT2
};

#endif /* _MCAL_EXTI_PRIVATE_H_ */
