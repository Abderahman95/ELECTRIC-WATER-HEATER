#ifndef _MCAL_DIO_REGISTER_H_
#define _MCAL_DIO_REGISTER_H_



/*PORTA*/
#define		PORTA				*((volatile U8*)(0x3B))
#define		DDRA				*((volatile U8*)(0x3A))
#define		PINA				*((volatile U8*)(0x39))
/*PORTB*/
#define		PORTB				*((volatile U8*)(0x38))
#define		DDRB				*((volatile U8*)(0x37))
#define		PINB				*((volatile U8*)(0x36))
/*PORTC*/
#define		PORTC				*((volatile U8*)(0x35))
#define		DDRC				*((volatile U8*)(0x34))
#define		PINC				*((volatile U8*)(0x33))
/*PORTD*/
#define		PORTD				*((volatile U8*)(0x32))
#define		DDRD				*((volatile U8*)(0x31))
#define		PIND				*((volatile U8*)(0x30))



#endif /* _MCAL_DIO_REGISTER_H_ */
