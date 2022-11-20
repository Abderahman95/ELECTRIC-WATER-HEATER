#ifndef __HAL_HEAT_COOL_ELEMENTS_CONFIG_H_
#define __HAL_HEAT_COOL_ELEMENTS_CONFIG_H_


#define HE_PORT 		DIO_U8PORT_B
#define HE_PIN			DIO_U8PIN4

#define CE_PORT			DIO_U8PORT_B
#define CE_PIN			DIO_U8PIN5


#define HEAT_PORT_DIR 					DDRB
#define HEAT_PORT 						PORTB
#define HEAT_PIN 						4

#define COOL_PORT_DIR 					DDRB
#define COOL_PORT						PORTB
#define COOL_PIN 						5


#endif /* __HAL_COOL_ELEMENTS_CONFIG_H_ */
