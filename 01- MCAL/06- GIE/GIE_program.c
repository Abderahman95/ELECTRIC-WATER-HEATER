#include"ERROR_STATE.h"
#include"TYPES.h"
#include"GIE_private.h"
#include"GIE_interface.h"

ES_t GIE_enu_Init(void)
{
	ES_t Local_enuErrorState =ES_NOK;

/****************CLEAR THE BIT I GIE***************/
	if(SREG &=~(BIT_MASKING<<GIE_BIT_I))
		{
			Local_enuErrorState=ES_OK;
		}

	return Local_enuErrorState;
}
ES_t GIE_enu_Enable(void)
{
	ES_t Local_enuErrorState =ES_NOK;
	/****************SET THE BIT I GIE***************/

	if(SREG |=(BIT_MASKING<<GIE_BIT_I))
		{
			Local_enuErrorState=ES_OK;
		}
	return Local_enuErrorState;
}

ES_t GIE_enu_Disable(void)
{
	ES_t Local_enuErrorState =ES_NOK;
	/****************CLEAR THE BIT I GIE***************/

	if(SREG &=~(BIT_MASKING<<GIE_BIT_I))
		{
			Local_enuErrorState=ES_OK;
		}

	return Local_enuErrorState;
}
