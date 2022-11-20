#include "TYPES.h"
#include "ERROR_STATE.h"
#include "EEPROM_private.h"
#include "EEPROM_register.h"
#include "EEPROM_interface.h"


ES_t EEPROM_enuReadByteFromAddress( const U16 Copy_U16Address ,  U8 *Copy_U18Data)
{
	ES_t Local_enuErrorState = ES_NOK;
	/* Wait for completion of previous write */
	while (((EECR & (1 << EECR_EEWE))>>EECR_EEWE)==1);
	/* Set up address register */
	EEAR = Copy_U16Address;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EECR_EERE);
	/* Return data from data register */
	(*Copy_U18Data) = EEDR;

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES_t EEPROM_enuReadBlockFromAddress(const U16 Copy_U16Address, U8 *Copy_U8Distnation,const U16 Copy_U16Size)
{
	ES_t Local_enuErrorState = ES_NOK;
	/* Wait for completion of previous write */
	while (((EECR & (1 << EECR_EEWE))>>EECR_EEWE)==1)
	;

	U16 Local_U16Counter = 0;//the Local_U16Counter of bytes that are read

	while (Local_U16Counter < Copy_U16Size) //loop until move all bytes to the given array
	{
		/* Set up address register */
		EEAR = Copy_U16Address + Local_U16Counter;
		/* Start EEPROM read by writing EECR_EERE */
		EECR |= (1 << EECR_EERE);
		/* move data from data register to the array */
		*(Copy_U8Distnation + Local_U16Counter) = EEDR;

		Local_U16Counter++;//increase the bytes Local_U16Counter

	}
	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}


ES_t EEPROM_enuWriteByteToAddress(const U16 Copy_U16Address, const U8 Copy_U8Data)
{
	ES_t Local_enuErrorState = ES_NOK;
	/* Wait for completion of previous write process*/
	while ( ( (EECR & (1 << EECR_EEWE) ) >>EECR_EEWE ) == 1)
	;
	/* Set up address register */
	EEAR = Copy_U16Address;

	/* Read the byte in the address of EEAR */
	EECR |= (1 << EECR_EERE);
	if (EEDR != Copy_U8Data)//compare the value read to the value to be written
	{//if they are not equal then write the data 
		EEDR = Copy_U8Data;//move the data to EEDR

		/* Write logical one to EEMWE */
		EECR |= (1 << EECR_EEMWE);
		/* Start EEPROM write by setting EECR_EEWE */
		EECR |= (1 << EECR_EEWE);
	}
	else
	{

	}
	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;

}

ES_t EEPROM_enuWriteBlockToAddress(const U16 Copy_U16Address, const U8 *Copy_U8Data,const U16 Copy_U16Size)
{
	ES_t Local_enuErrorState = ES_NOK;
	U16 Local_U16Counter = 0;//Bytes write Local_U16Counter
	while (Local_U16Counter < Copy_U16Size)
	{
		/* Wait for completion of previous write process*/
		while (( (EECR & (1 << EECR_EEWE) ) >>EECR_EEWE ) == 1)
		;
		/* Set up address register */
		EEAR = Copy_U16Address + Local_U16Counter;

		/* Read the byte in the address of EEAR */
		EECR |= (1 << EECR_EERE);
		if (EEDR != (*(Copy_U8Data + Local_U16Counter)))//compare the value read to the value to be written
		{//if they are not equal then write the data 
			EEDR = *(Copy_U8Data + Local_U16Counter);//move the data to EEDR

			/* Write logical one to EECR_EEMWE */
			EECR |= (1 << EECR_EEMWE);
			/* Start EEPROM write by setting EECR_EEWE */
			EECR |= (1 << EECR_EEWE);
		}
		else
		{

		}
		Local_U16Counter++;
	}
	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}
