#ifndef _APP_TMU_PRIVATE_H_
#define _APP_TMU_PRIVATE_H_

typedef	struct
		{
			void (*Pfun) (void);
			U16 priodicity;
			U16 counter;
			U8 State;
		}TCB_t; //NEW DATA TYPE


#define READY										11
#define SUSPEND										12
#define KILLED										13

#define 	MIN_TICK_TIME 							0
#define 	TIMER_MASK_BIT							1
#define 	TMU_ZERO_NUMBER							0
#define 	TIMER_CLOCK_NO_CLOCK					0
#define		TIMER_CLOCK_NO_PRESCHALER				1
#define		TIMER_CLOCK_8_PRESCHALER				8
#define		TIMER_CLOCK_64_PRESCHALER				64
#define		TIMER_CLOCK_256_PRESCHALER				256
#define		TIMER_CLOCK_1024_PRESCHALER			    1024
#define		ONE_KILO								1000
#define		 CPU_FREQ								16000000
#define 	TIME_NUMERATOR 							USED_TIMER##_RESOLUTION_COUNTS * USED_TIMER##_PRESCALER
#define 	TIME_DENOMINATOR						F_CPU
#define 	MAX_TICK_TIME							16


#define OCRN_COUNTS						(U16)(( CPU_FREQ) / (1024ul *1000ul ) +1)


#endif /* _APP_TMU_PRIVATE_H_ */
