#ifndef _MCAL_DIO_INTERFACE_H_
#define _MCAL_DIO_INTERFACE_H_



//1-Initialization
ES_t DIO_enuInit(void); 

//2-SetPinDirection[input/output]
ES_t DIO_enuSetPinDirection(U8 Copy_U8PortID, U8 Copy_U8PinID, U8 Copy_U8Direction);

//3-SetPinValue
ES_t DIO_enuSetPinValue(U8 Copy_U8PortID, U8 Copy_U8PinID, U8 Copy_U8Value);

//4-GetPin
ES_t DIO_enuGetPinValue(U8 Copy_U8PortID, U8 Copy_U8PinID, U8  * Copy_U8Value);

//5-TogglePin
ES_t DIO_enuTogPinValue(U8 Copy_U8PortID, U8 Copy_U8PinID);


typedef enum
{
	DIO_U8PORT_A,
	DIO_U8PORT_B,
	DIO_U8PORT_C,
	DIO_U8PORT_D,

	DIO_U8PIN0 = 0,
	DIO_U8PIN1,
	DIO_U8PIN2,
	DIO_U8PIN3,
	DIO_U8PIN4,
	DIO_U8PIN5,
	DIO_U8PIN6,
	DIO_U8PIN7,

	DIO_U8INPUT = 0,
	DIO_U8OUTPUT,

	DIO_U8LOW = 0,
	DIO_U8HIGH,

	DIO_U8FLOAT = 0,
	DIO_U8PULL_UP
	
}ES_interface;



#endif /* _MCAL_DIO_INTERFACE_H_ */
