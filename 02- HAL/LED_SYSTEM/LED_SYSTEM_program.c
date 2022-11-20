#include "TYPES.h"
#include "ERROR_STATE.h"
#include "DIO_interface.h"

#include "LED_SYSTEM_interface.h"
#include "LED_SYSTEM_config.h"
#include "LED_SYSTEM_private.h"


ES_t LED_SYSTEM_enuIniti(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;

		/* LED SYSTEM */
		/* Direction */
	DIO_enuSetPinDirection(LED_SYSTEM_PORT,LED_SYSTEM_PIN, DIO_U8OUTPUT);
		/* SETPIN */
	DIO_enuSetPinValue(LED_SYSTEM_PORT,LED_SYSTEM_PIN,DIO_U8LOW);


	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
ES_t LED_SYSTEM_enuLedStart(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuSetPinValue(LED_SYSTEM_PORT,LED_SYSTEM_PIN,DIO_U8HIGH);
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
ES_t LED_SYSTEM_enuLedToggle(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuTogPinValue(LED_SYSTEM_PORT,LED_SYSTEM_PIN);
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;

}
ES_t LED_SYSTEM_enuLedStop(void)

{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuSetPinValue(LED_SYSTEM_PORT,LED_SYSTEM_PIN,DIO_U8LOW);
	Local_enu_ErrorState = ES_OK;
return Local_enu_ErrorState;
}
