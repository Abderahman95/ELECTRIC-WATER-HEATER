#ifndef _APP_SYSTEM_INTERFACE_H_
#define _APP_SYSTEM_INTERFACE_H_

/*-------------------------------------- SYSTEM MODULE FUNCTIONS --------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuInit
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description :-To initialize the system Modules:
                                                            -Digital Input Output Module.
                                                            -Push button switches. 		                    [INPUT]
                                                            -Temperature Sensor. 		                    [INPUT]
                                                            -Analog to Digital Converter. 			        [INTERRUPT]
                                                            -External Interrupt.                            [INTERRUPT]
                                                            -Timer/Counter 0 8-bit. 	                    [INTERRUPT]
                                                            -Timer/Counter 1 16-bit. 	                    [INTERRUPT]
                                                            -Timer/Counter 2 8-bit. 	                    [INTERRUPT]
                                                            -Global Interrupt Enable. 						[INTERRUPT]
                                                            -LED system.				                    [OUTPUT]
                                                            -Seven Segment Display.		                    [OUTPUT]
                                                            -Liquid Crystal Display.	                    [OUTPUT]
                                                            -Heating and Cooling Elements.                  [OUTPUT]
						   - Setting the initial temperature degree to the internal EEPORM.

*/
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuInit(void);

/*-----------------------------------------------------------------------------------------------*/


/*
	Function Name        : SYSTEM_enuOnState
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : Receiving the calculated read temperature degree from the Temperature Sensor [LM35],
						   After received and processed by the ADC every 100m seconds, where Timer/Counter 1 compare match on channel B is responsible for.
						   Building an array to save these reading then calculate there average of the last ten readings every 1 second.
						   Then Display this averaged ten temperature readings on the Seven Segments and the LCD.
						   Then monitor any change in the read temperature and compare it with the desired/saved temperature in the EEPROM.
						   And take an action if the current averaged temperature is less or greater than the set desired/saved temperature.
						   Controlling the HEATING and COOLING elements, LED system, Seven Segments, and LCD display.
*/
/*-----------------------------------------------------------------------------------------------*/


ES_t SYSTEM_enuOnState(void);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuOffState
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : This function is triggered by the External Interrupt when the ON/OFF push botton switch is pressed while,
						   the system either in the ON_STATED or SETTING_STATE Modes.
						   It Disables to system modules.
 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuOffState(void);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuSettingState
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : This function is triggered by the External Interrupt when either the UP_SWITCH or DOWN_SWITCH is pressed while,
	 	 	 	 	 	   the system in the ON_STATE mode.
	 	 	 	 	 	   This function allows the user to modify the desired/saved temperature and save the new set in the EEPROM.
	 	 	 	 	 	   Then this new set temperature value is displayed on the LCD and the seven segments, however.
	 	 	 	 	 	   The seven segments are blinking every one second in this mode [TIMER0 CTC is responsible for this blinking].
	 	 	 	 	 	   After five seconds of UP_SWITCH or DOWN_SWITCH being not pressed, the system exits the SETTING_STATE mode to the ON_STATE mode [TIMER1 CTC-A channel and TIMER2 CTC are responsible of this behavior].
 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuSettingState(void);

/*-----------------------------------------------------------------------------------------------*/


/*-------------------------------------- INNER FUNCTIONS --------------------------------*/
/*-----------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------*/


/*
	Function Name        : SYSTEM_enuGetTemp
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : Internal function of the [SYSTEM_enuOnState(),
	 	 	 	 	 	   which is responsible for getting the read temperature reading by the system [ADC] every 100m second [TIMER/Counter1 CTC-B channel],
	 	 	 	 	 	   which is responsible for  building a ten size array to hold ten read temperature readings in 1 second period.

 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuGetTemp(void);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuAddNewTemp
	Function Returns     : ENUM
	Function Arguments   : ARRAY ADDRESS {* Copy_pAstrTempReadings}, A NEW READ TEMPERATURE {Copy_U16TempNewValue}
	Function Description : Internal function of the [SYSTEM_enuOnState(),
	 	 	 	 	 	   which is responsible for  entering a temperature reading in a ten size array.
 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuAddNewTemp(U16 *Copy_pAstrTempReadings , U16 Copy_U16TempNewValue);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuCalculateAverateTemp
	Function Returns     : ENUM
	Function Arguments   : ARRAY ADDRESS {* Copy_pAstrTempReadings}, A VARIABLE ADDRESS TO HOLD THE COLCULATED TEMPERATURE READINGS AVERAGE {* Copy_U16ReturnTempValue}
	Function Description : Internal function of the [SYSTEM_enuOnState(),
	 	 	 	 	 	   which is responsible for  calculating the average of the last ten read temperature reading in the last one second.
 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuCalculateAverateTemp(U16 *Copy_pAstrTempReadings, U16 *Copy_U16ReturnTempValue);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuChangeTemp
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : Internal function of the [SYSTEM_enuOnState(),
	 	 	 	 	 	   which is responsible for behavior of the  Heating and cooling systems as well as the LED system.
	 	 	 	 	 	   If the current water temperature readings average is less than the set saved temperature by five degrees:
	 	 	 	 	 	   the heating element is turned on, then LED system 'Heating Element LED' is blinking every one second [TIMER0 CTC is responsible for this blinking],and the cooling element is turned off.
	 	 	 	 	 	   If the current water temperature readings average is greater than the set saved temperature by five degrees:
	 	 	 	 	 	   the heating element is turned off, and the cooling element is turned on, then LED system 'Heating Element LED' is turned on.
	 	 	 	 	 	   If the current water temperature readings average is equal the set saved temperature by five degrees :
	 	 	 	 	 	   the heating element is turned OFF, the cooling element is turned off and the LED system 'Heating Element LED' is turned off.
 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuChangeTemp(void);

/*-----------------------------------------------------------------------------------------------*/

/*
	Function Name        : SYSTEM_enuSleepMode
	Function Returns     : ENUM
	Function Arguments   : void
	Function Description : Power management and sleep mode, this function select the IDLE sleeping mode by clearing the MCU control register sleep mode select bits.
 */
/*-----------------------------------------------------------------------------------------------*/

ES_t SYSTEM_enuSleepMode(void);

/*-----------------------------------------------------------------------------------------------*/

//ES_t SYSTEM_enuDisplayTemp(void);

/*-----------------------------------------------------------------------------------------------*/

#define NUM_OF_TEMP_MEASURES 					10
#define ZERO_VALUE								0
#define TEMP_UP_SWITCH							0
#define TEMP_DOWN_SWITCH						1
#define ON_OFF_SWITCH							2
#
#define OFF_STATE								0
#define ON_STATE								1
#define SETTINT_STATE							2

#endif /* _APP_SYSTEM_INTERFACE_H_ */
