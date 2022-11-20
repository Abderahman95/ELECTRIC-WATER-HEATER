#ifndef _HAL_TEMP_SENSOR_INTERFACE_H_
#define _HAL_TEMP_SENSOR_INTERFACE_H_
/*
	Function Name        : TempSensor_enuInit
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : Set the direction and value of the temperature sensor pin to the microcontroller as input float.
						   Select the ADC channel.
						   ADC auto triggering source, wether its external interrupt, timer one compare match on B channel, or single conversion system.
						   In our Electric water heating system:
						   The trigger source selection is Timer1 CTC-B channel. Though, timer1 is initiallized, and its interrupt is enabled,
						   and the timer1 CTC-B ISR is responsible of enabling the ADC every 100 m second, then the ADC ISR is responsible for calulation of the temperature reading every 100m second.
	 */
/*-----------------------------------------------------------------------------------------------*/

ES_t TempSensor_enuInit(void);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : TempSensor_enuGetTempReading
	Function Returns     : ENUM
	Function Arguments   : ADDRESS OF A VARIABLE TO HOLD THE READ TEMPERATURE READING {* Copy_pU16TempReading}
	Function Description : Function depends on the TempSensor_enuInit() Function:
  	  	  	  	  	  	   Which Contain :	Two CallBack Function for Timer1 Interrupt and ADC Interrupt: Both aim to
  	  	  	  	  	  	   read the Value of the ADC readying every 100m second.
  				 	 	 TIMER1_enuSetCallBackDelay((volatile void (*) (void) ) ADC_enuEnableADC,TIMER_CTC1B_INTERRUPT_INDEX,TIMER1_100_MILE_SECOND);
  					 	 ADC_enuCallBack( (volatile void (*) (void) ) TempSensor_RiseFlag);


 */
/*-----------------------------------------------------------------------------------------------*/


ES_t TempSensor_enuGetTempReading(U16 *Copy_pU16TempReading);

/*-----------------------------------------------------------------------------------------------*/




#endif /* _HAL_TEMP_SENSOR_INTERFACE_H_ */
