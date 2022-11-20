#ifndef _MCAL_ADC_CONFIG_H_
#define _MCAL_ADC_CONFIG_H_

/*Please select the required prescaler from these choices: PRESCALER_2		PRESCALER_4		 PRESCALER_8		PRESCALER_16		PRESCALER_32		PRESCALER_64	PRESCALER_128*/
#define ADC_PRESCALER 								PRESCALER_64

/* AREF_REFERENCE 	AVCC_REFERENCE		INTERNAL_REFERENCE 	*/
#define ADC_VREFERNCE								AVCC_REFERENCE

/*LEFT_ADJUSMENT 			RIGHT_ADJUSMENT*/
#define ADC_ADJUSMENT	 							LEFT_ADJUSMENT

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* Select the ADC trigger source ------------------------->>			ADC_AUTO_TRIGGERING_SOURCE
* Free Running Mode	------------------------------------>>			ADC_U8FreeRunningMode
*External Interrupt request 0  ---------------------------->>   		ADC_U8ExternalInterruptRequest_0
*Timer Interrupt request 0 CompareMatch -------------->>   		ADC_U8TimerInterrupt0_CompareMatch
*Timer Interrupt request 0 Overflow -------------------->>   		ADC_U8TimerInterrupt0_Overflow
*Timer Interrupt request 1 CompareMatch B  ----------->>     	ADC_U8TimerInterrupt_CompareMatchB
*Timer Interrupt request 1 Overflow  -------------------->>  		ADC_U8TimerInterrupt1_Overflow
 *Timer Interrupt request 1 Capture Event --------------->>         ADC_U8TimerInterrupt1_ CaptureEvent


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	*/
#define 	ADC_AUTO_TRIGGERING_SOURCE						ADC_U8TimerInterrupt_CompareMatchB

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* Single Conversion	------------------------------------>>			ADC_U8SingleConversion
* Free Running Mode	------------------------------------>>			ADC_U8FreeRunningMode
*External Interrupt request 0  ---------------------------->>   		ADC_U8ExternalInterruptRequest_0
*Timer Interrupt request 0 CompareMatch -------------->>   		ADC_U8TimerInterrupt0_CompareMatch
*Timer Interrupt request 0 Overflow -------------------->>   		ADC_U8TimerInterrupt0_Overflow
*Timer Interrupt request 1 CompareMatch B  ----------->>     	ADC_U8TimerInterrupt_CompareMatchB
*Timer Interrupt request 1 Overflow  -------------------->>  		ADC_U8TimerInterrupt1_Overflow
 *Timer Interrupt request 1 Capture Event --------------->>         ADC_U8TimerInterrupt1_ CaptureEvent


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	*/
#define 	ADC_U8FreeRunningMode								0
#define 	ADC_U8ExternalInterruptRequest_0				  	2
#define 	ADC_U8TimerInterrupt0_CompareMatch			       	3
#define 	ADC_U8TimerInterrupt0_Overflow						4
#define 	ADC_U8TimerInterrupt_CompareMatchB			       	5
#define 	ADC_U8TimerInterrupt1_Overflow					  	6
#define 	ADC_U8TimerInterrupt1_CaptureEvent				    7


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* * Select the ADC Channel ------------------------->>			ADC_CHANNEL_SELECTION


*Single Ended Input ADC0 --------------------------->>          ADC_SINGLE_ENDED_ADC0
*Single Ended Input ADC1 --------------------------->>          ADC_SINGLE_ENDED_ADC1
*Single Ended Input ADC2 --------------------------->>          ADC_SINGLE_ENDED_ADC2
*Single Ended Input ADC3 --------------------------->>          ADC_SINGLE_ENDED_ADC3
*Single Ended Input ADC4 --------------------------->>          ADC_SINGLE_ENDED_ADC4
*Single Ended Input ADC5 --------------------------->>          ADC_SINGLE_ENDED_ADC5
*Single Ended Input ADC6 --------------------------->>          ADC_SINGLE_ENDED_ADC6
*Single Ended Input ADC7 --------------------------->>          ADC_SINGLE_ENDED_ADC7

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	*/

#define ADC_SINGLE_ENDED_ADC0                                   0
#define ADC_SINGLE_ENDED_ADC1                                   1
#define ADC_SINGLE_ENDED_ADC2                                   2
#define ADC_SINGLE_ENDED_ADC3                                   3
#define ADC_SINGLE_ENDED_ADC4                                   4
#define ADC_SINGLE_ENDED_ADC5                                   5
#define ADC_SINGLE_ENDED_ADC6                                   6
#define ADC_SINGLE_ENDED_ADC7                                   7

#define ADC_CHANNEL_SELECTION									ADC_SINGLE_ENDED_ADC0


#endif /* _MCAL_ADC_CONFIG_H_ */
