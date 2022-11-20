#include "TYPES.h"
#include "ERROR_STATE.h"
#include "DIO_interface.h"
#include "HEAT_COOL_Elements_interface.h"
#include "HEAT_COOL_Elements_config.h"
#include "HEAT_COOL_Elements_private.h"

ES_t HEAT_COOL_ELEMENTS_enuIniti(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;

		/* HEATING ELEMENT*/
		/* Direction */
	DIO_enuSetPinDirection(HE_PORT,HE_PIN, DIO_U8OUTPUT);
		/* SETPIN */
	DIO_enuSetPinValue(HE_PORT,HE_PIN,DIO_U8LOW);

	/* COOLING ELEMENT*/
		/* Direction */
	DIO_enuSetPinDirection(CE_PORT,CE_PIN, DIO_U8OUTPUT);
		/* SETPIN */
	DIO_enuSetPinValue(CE_PORT,CE_PIN,DIO_U8LOW);

	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
ES_t HEAT_COOL_ELEMENTS_enuHeaterStart(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuSetPinValue(HE_PORT,HE_PIN,DIO_U8HIGH);
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
ES_t HEAT_COOL_ELEMENTS_enuHeaterToggle(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuTogPinValue(HE_PORT,HE_PIN);
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
ES_t HEAT_COOL_ELEMENTS_enuHeaterStop(void)

{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuSetPinValue(HE_PORT,HE_PIN,DIO_U8LOW);
	Local_enu_ErrorState = ES_OK;
return Local_enu_ErrorState;
}
ES_t HEAT_COOL_ELEMENTS_enuCoolerStart(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuSetPinValue(CE_PORT,CE_PIN,DIO_U8HIGH);
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
ES_t HEAT_COOL_ELEMENTS_enuCoolerStop(void)
{
	ES_t Local_enu_ErrorState = ES_NOK;
	/* SETPIN */
	DIO_enuSetPinValue(CE_PORT,CE_PIN,DIO_U8LOW);
	Local_enu_ErrorState = ES_OK;
	return Local_enu_ErrorState;
}
