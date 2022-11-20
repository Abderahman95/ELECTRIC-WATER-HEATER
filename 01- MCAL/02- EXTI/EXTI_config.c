#include "ERROR_STATE.h"
#include "TYPES.h"
#include "EXTI_config.h"
#include "EXTI_private.h"


EXTI_t EXTI_AstrEXTIConfig [INT_NUM]=
	{
			{ENABLED, RISING},	  //int 0
			{ENABLED, RISING}, 	  //int 1
			{ENABLED, RISING}	  //int 2 WILL BE CONNECTED TO ON_OFF_SWITCH
	};
