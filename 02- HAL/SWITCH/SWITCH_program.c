#include "TYPES.h"
#include "ERROR_STATE.h"
#include "DIO_interface.h"

#include "SWITCH_config.h"
#include "SWITCH_private.h"
#include "SWITCH_interface.h"


extern ES_t SWITCH_enuIniti(SW_t *Copy_pAstrSwitchConfig)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	U8 Local_U8Iterator;
	for(Local_U8Iterator=0;Local_U8Iterator<SW_NUM;Local_U8Iterator++)
	{
		/*Direction*/ DIO_enuSetPinDirection(Copy_pAstrSwitchConfig[Local_U8Iterator].SW_Port,Copy_pAstrSwitchConfig[Local_U8Iterator].SW_Pin, DIO_U8INPUT);
		/*SETPIN*/ DIO_enuSetPinValue((Copy_pAstrSwitchConfig+Local_U8Iterator)->SW_Port,(Copy_pAstrSwitchConfig+Local_U8Iterator)->SW_Pin,(Copy_pAstrSwitchConfig+Local_U8Iterator)->SW_State);
	}
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}

extern ES_t SWITCH_enuGetState(SW_t *Copy_pAstrSwitchInfo,U8 *Copy_pU8Value)
{
	ES_t Local_enu_ErrorState = ES_NOK;

	Local_enu_ErrorState = DIO_enuGetPinValue(Copy_pAstrSwitchInfo->SW_Port,Copy_pAstrSwitchInfo->SW_Pin, Copy_pU8Value);

	return Local_enu_ErrorState;

}

