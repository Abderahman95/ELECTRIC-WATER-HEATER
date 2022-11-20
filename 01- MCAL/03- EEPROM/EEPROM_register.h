#ifndef _MCAL_EEPROM_REGISTER_H_
#define _MCAL_EEPROM_REGISTER_H_

#define		EEDR					*((volatile U8*)(0x3D))

#define		EECR					*((volatile U8*)(0x3C))

#define		EEARH					*((volatile U8*)(0x3F))

#define		EEARL					*((volatile U8*)(0x3E))
#define		EEAR					*((volatile U8*)(0x3E))


#define EECR_EERIE						3
#define EECR_EEMWE						2
#define EECR_EEWE						1
#define EECR_EERE						0



#endif /* _MCAL_EEPROM_REGISTER_H_ */
