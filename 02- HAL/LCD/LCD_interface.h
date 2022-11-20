#ifndef _HAL_LCD_INTERFACE_H_
#define _HAL_LCD_INTERFACE_H_


ES_t LCD_enuInit(void);
ES_t LCD_enuSendData(U8 Copy_U8Data);
ES_t LCD_enuSendCommand(U8 Copy_U8Command);
ES_t LCD_enuSendpcString(const char *Copy_pcString);
ES_t LCD_enuSendPosition(U8 Copy_U8Line, U8 Copy_U8Position);
ES_t LCD_enuSendCustomCharacter(U8 * Copy_U8PArrCustomCharacter, U8 Copy_U8PatternsNumber,U8 Copy_U8XPosition, U8 Copy_U8YPosition, U8 Copy_U8Direction);
ES_t LCD_enuDisplayIntegerNum(S32 Copy_S32Num);
ES_t LCD_enuClearDisplay( void );

#define FIRST_LINE											 0x80
#define SECOND_LINE									 		 0xc0

#endif /* _HAL_LCD_INTERFACE_H_ */
