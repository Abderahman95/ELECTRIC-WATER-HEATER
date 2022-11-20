#ifndef _MCAL_INTERRUPT_H_
#define _MCAL_INTERRUPT_H_


#define ISR(vect_num) 		void vect_num (void)__attribute__((signal));\
												void vect_num (void)


#define VECT_INT0																					__vector_1
#define VECT_INT1																					__vector_2
#define VECT_INT2																					__vector_3

#define VECT_TIMER2_CTC																				__vector_4
#define VECT_TIMER2_OVF																				__vector_5

#define VECT_TIMER1_CTCA																			__vector_7
#define VECT_TIMER1_CTCB																			__vector_8
#define VECT_TIMER1_OVF																				__vector_9

#define VECT_TIMER0_CTC																				__vector_10
#define VECT_TIMER0_OVF																				__vector_11


#define VECT_RXC   	           																		__vector_13
#define VECT_UDRE              																		__vector_14
#define VECT_TXC	             																	__vector_15

#define VECT_ADC																					__vector_16

#endif /* _MCAL_INTERRUPT_H_ */
