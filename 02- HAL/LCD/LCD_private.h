#ifndef _HAL_LCD_PRIVATE_H_
#define _HAL_LCD_PRIVATE_H_

#define FOUR_BIT							4
#define EIGHT_BIT							8
#define FUNCTION_SET_EIGHT_BIT 			    0x38
#define FUNCTION_SET_FOUR_BIT 		    	0x28
#define DISPLAY_ON_OFF_BIT		 			0x0f
#define DISPLAY_CLEAR_BIT 					0x01
#define ENTERY_MODE_BIT		 				0x06


#define LATCH_DELAY							5
#define POWER_ON_DELAY    					30
#define FUNCTION_SET_DELAY    				39
#define DISPLAY_CLEAR_DELAY    				1.53
#define BIT_MASK_MOVE						1
#define BIT_NUMBER_0						0
#define BIT_NUMBER_1						1
#define BIT_NUMBER_2						2
#define BIT_NUMBER_3						3
#define BIT_NUMBER_4						4
#define BIT_NUMBER_5						5
#define BIT_NUMBER_6						6
#define BIT_NUMBER_7						7
#define ONE_STEP											1
static ES_t LCD_enuWriteNLatch(U8 Copy_U8Command);/*Static local function to make falling edge high then low*/

#endif /* _HAL_LCD_PRIVATE_H_ */
