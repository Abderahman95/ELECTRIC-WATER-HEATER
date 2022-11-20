#ifndef _MCAL_EEPROM_INT_H_
#define _MCAL_EEPROM_INT_H_


ES_t EEPROM_enuReadByteFromAddress( const U16 Copy_U16Address ,  U8 *Copy_U18data);
ES_t EEPROM_enuReadBlockFromAddress(const U16 Copy_U16Address, U8 *Copy_U8Distnation,const U16 Copy_U16Size);
ES_t EEPROM_enuWriteByteToAddress(const U16 Copy_U16Address, const U8 Copy_U8Data);
ES_t EEPROM_enuWriteBlockToAddress(const U16 Copy_U16Address, const U8 *Copy_U8Data,const U16 Copy_U16Size);

#endif /* _MCAL_EEPROM_INT_H_ */
