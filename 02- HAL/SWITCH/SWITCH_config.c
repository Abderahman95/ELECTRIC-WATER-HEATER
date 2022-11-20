#include "TYPES.h"
#include "ERROR_STATE.h"
#include "DIO_interface.h"
#include "SWITCH_config.h"
#include "SWITCH_private.h"

//U8 SWITCH_U8SwitchNumbers=SW_NUM;

SW_t SWITCH_AstrSwitchConfig [SW_NUM]=
{
		/* UP_SWITCH on Port B Pin0*/{DIO_U8PORT_D,DIO_U8PIN2,DIO_U8FLOAT},
		/* DOWN_SWITCH on Port B Pin1*/{DIO_U8PORT_D,DIO_U8PIN3,DIO_U8FLOAT},
		/* ON_OFF_SWITCH on Port B Pin2*/{DIO_U8PORT_B,DIO_U8PIN2,DIO_U8FLOAT}

};
