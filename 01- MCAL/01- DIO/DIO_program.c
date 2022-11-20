#include "TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "DIO_interface.h"
#include "DIO_register.h"
#include "DIO_private.h"
#include "DIO_config.h"


//1-Initialization

ES_t DIO_enuInit(void)
{
ES_t Local_enuErrorState = ES_NOK;

DDRA = INIT_DDR_DIRECTION;
PORTA=  INIT_PORT_VALUE;

return Local_enuErrorState;
}
//2-SetPinDirection[input/output]
ES_t DIO_enuSetPinDirection(U8 Copy_U8PortID, U8 Copy_U8PinID, U8 Copy_U8Direction)
{
	ES_t Local_enuErrorState = ES_NOK;
if(Copy_U8PortID<=DIO_U8PORT_D&&Copy_U8PinID<=DIO_U8PIN7&&Copy_U8Direction<=DIO_U8OUTPUT)
	{
		switch(Copy_U8PortID)
		{
		case DIO_U8PORT_A:
			DDRA &=~(DIO_MASK_BIT<<Copy_U8PinID);
			DDRA |= (Copy_U8Direction<<Copy_U8PinID);
			break;
		case DIO_U8PORT_B:
					DDRB &=~(DIO_MASK_BIT<<Copy_U8PinID);
					DDRB |= (Copy_U8Direction<<Copy_U8PinID);
					break;
		case DIO_U8PORT_C:
					DDRC &=~(DIO_MASK_BIT<<Copy_U8PinID);
					DDRC |= (Copy_U8Direction<<Copy_U8PinID);
					break;
		case DIO_U8PORT_D:
					DDRD &=~(DIO_MASK_BIT<<Copy_U8PinID);
					DDRD |= (Copy_U8Direction<<Copy_U8PinID);
					break;
		}
		 Local_enuErrorState = ES_OK;
	}

		else
		{
		Local_enuErrorState = ES_OUT_OF_RANG;
		}
	return  Local_enuErrorState;
}
//3-SetPinValue
ES_t DIO_enuSetPinValue(U8 Copy_U8PortID, U8 Copy_U8PinID, U8 Copy_U8Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_U8PortID<=DIO_U8PORT_D	&&Copy_U8PinID<=DIO_U8PIN7&&(Copy_U8Value<=DIO_U8HIGH ||Copy_U8Value<=DIO_U8PULL_UP))
		{
			switch(Copy_U8PortID)
			{
			case DIO_U8PORT_A:
						PORTA &=~(DIO_MASK_BIT<<Copy_U8PinID);
						PORTA |= (Copy_U8Value<<Copy_U8PinID);
						break;
			case DIO_U8PORT_B:
						PORTB &=~(DIO_MASK_BIT<<Copy_U8PinID);
						PORTB |= (Copy_U8Value<<Copy_U8PinID);
						break;
			case DIO_U8PORT_C:
						PORTC &=~(DIO_MASK_BIT<<Copy_U8PinID);
						PORTC |= (Copy_U8Value<<Copy_U8PinID);
						break;
			case DIO_U8PORT_D:
						PORTD &=~(DIO_MASK_BIT<<Copy_U8PinID);
						PORTD |= (Copy_U8Value<<Copy_U8PinID);
						break;
			}
			 Local_enuErrorState = ES_OK;
		}

			else
			{
				 Local_enuErrorState = ES_OUT_OF_RANG;
			}
		return  Local_enuErrorState;
}

//4-GetPin
ES_t DIO_enuGetPinValue(U8 Copy_U8PortID, U8 Copy_U8PinID, U8 *Copy_U8Value)
{

	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_U8Value!= NULL)
	{
		if(Copy_U8PortID<=DIO_U8PORT_D	&&Copy_U8PinID<=DIO_U8PIN7)
		{
			switch(Copy_U8PortID)
					{
					case DIO_U8PORT_A:
								*Copy_U8Value=((PINA>>Copy_U8PinID) &DIO_MASK_BIT);

								break;
					case DIO_U8PORT_B:
						*Copy_U8Value=(PINB>>Copy_U8PinID) &DIO_MASK_BIT;

								break;
					case DIO_U8PORT_C:
						*Copy_U8Value=(PINC>>Copy_U8PinID) &DIO_MASK_BIT;

								break;
					case DIO_U8PORT_D:
						*Copy_U8Value=(PIND>>Copy_U8PinID) &DIO_MASK_BIT;

								break;
					}
					 Local_enuErrorState = ES_OK;
				}

			else
			{
				Local_enuErrorState = ES_OUT_OF_RANG;
			}
		}
	else
		{
		Local_enuErrorState = ES_NULL_POINTER;
		}

	return Local_enuErrorState;
}


//5-TogglePin
ES_t DIO_enuTogPinValue(U8 Copy_U8PortID, U8 Copy_U8PinID)
{

	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_U8PortID<=DIO_U8PORT_D	&&Copy_U8PinID<=DIO_U8PIN7)
		{
			switch(Copy_U8PortID)
			{
			case DIO_U8PORT_A:
						PORTA ^=(DIO_MASK_BIT<<Copy_U8PinID);
						break;
			case DIO_U8PORT_B:
						PORTB ^=(DIO_MASK_BIT<<Copy_U8PinID);
						break;
			case DIO_U8PORT_C:
						PORTC ^=(DIO_MASK_BIT<<Copy_U8PinID);
						break;
			case DIO_U8PORT_D:
						PORTD ^=(DIO_MASK_BIT<<Copy_U8PinID);
						break;
			}
			 Local_enuErrorState = ES_OK;
		}

			else
			{
				 Local_enuErrorState = ES_OUT_OF_RANG;
			}

	return Local_enuErrorState;

}

