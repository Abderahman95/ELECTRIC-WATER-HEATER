#include "ERROR_STATE.h"
#include "TYPES.h"
#include "interrupt.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

static volatile void (* EXTI_pfunISRFun[3]) (void) = {NULL,NULL,NULL};



ES_t EXTI_enuInit(EXTI_t * Copy_pAstrEXTIConfig)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pAstrEXTIConfig[INT0].Int_State == ENABLED)
	{
		GICR |= (1<<6);
		switch(Copy_pAstrEXTIConfig[INT0].Sence_level)
		{
		case LOW_LEVEL:
			MCUCR &= ~(3<<0);
			break;
		case ANY_LOGICAL:
			MCUCR |=  (1<<0);
			MCUCR &= ~(1<<1);
			break;
		case FALLING:
			MCUCR &= ~(1<<0);
			MCUCR |=  (1<<1);
			break;
		case RISING:
			MCUCR |=  (3<<0);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}
	else if (Copy_pAstrEXTIConfig[INT0].Int_State == DISABLED)
	{
		GICR &=~(1<<6);
	}

	if (Copy_pAstrEXTIConfig[INT1].Int_State == ENABLED)
	{
		GICR |= (1<<7);
		switch(Copy_pAstrEXTIConfig[INT1].Sence_level)
		{
		case LOW_LEVEL:
			MCUCR &= ~(3<<2);
			break;
		case ANY_LOGICAL:
			MCUCR |=  (1<<2);
			MCUCR &= ~(1<<3);
			break;
		case FALLING:
			MCUCR &= ~(1<<2);
			MCUCR |=  (1<<3);
			break;
		case RISING:
			MCUCR |=  (3<<2);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}
	else if (Copy_pAstrEXTIConfig[INT1].Int_State == DISABLED)
	{
		GICR &=~(1<<7);
	}

	if (Copy_pAstrEXTIConfig[INT2].Int_State == ENABLED)
	{
		GICR |= (1<<5);
		switch(Copy_pAstrEXTIConfig[INT2].Sence_level)
		{
		case FALLING:
			MCUCSR &= ~(1<<6);
			break;
		case RISING:
			MCUCSR |=  (1<<6);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}
	else if (Copy_pAstrEXTIConfig[INT2].Int_State == DISABLED)
	{
		GICR &=~(1<<5);
	}
	return Local_enuErrorState;
}

ES_t EXTI_enuSetSenseLevel(U8 Copy_U8IntNum, U8 Copy_U8SenceLevel)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_U8IntNum == INT0)
	{
		switch(Copy_U8SenceLevel)
		{
		case LOW_LEVEL:
			MCUCR &= ~(3<<0);
			break;
		case ANY_LOGICAL:
			MCUCR |=  (1<<0);
			MCUCR &= ~(1<<1);
			break;
		case FALLING:
			MCUCR &= ~(1<<0);
			MCUCR |=  (1<<1);
			break;
		case RISING:
			MCUCR |=  (3<<0);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}
	else if (Copy_U8IntNum == INT1)
	{
		switch(Copy_U8SenceLevel)
		{
		case LOW_LEVEL:
			MCUCR &= ~(3<<2);
			break;
		case ANY_LOGICAL:
			MCUCR |=  (1<<2);
			MCUCR &= ~(1<<3);
			break;
		case FALLING:
			MCUCR &= ~(1<<2);
			MCUCR |=  (1<<3);
			break;
		case RISING:
			MCUCR |=  (3<<2);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}
	else if (Copy_U8IntNum == INT2)
	{
		switch(Copy_U8SenceLevel)
		{
		case FALLING:
			MCUCSR &= ~(1<<6);
			break;
		case RISING:
			MCUCSR |=  (1<<6);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}


	return Local_enuErrorState;
}

ES_t EXTI_enuEnableInterrupt(U8 Copy_U8IntNum)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_U8IntNum == INT0)
	{
		GICR |= (1<<6);
	}
	else if (Copy_U8IntNum == INT1)
	{
		GICR |= (1<<7);
	}
	else if (Copy_U8IntNum == INT2)
	{
		GICR |= (1<<5);
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANG;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuDisableInterrupt(U8 Copy_U8IntNum)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_U8IntNum == INT0)
	{
		GICR &=~(1<<6);
	}
	else if (Copy_U8IntNum == INT1)
	{
		GICR &=~(1<<7);
	}
	else if (Copy_U8IntNum == INT2)
	{
		GICR &=~(1<<5);
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANG;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuCallBack(volatile void (* Copy_pfunAppFun)(void), U8 Copy_U8IntNum)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pfunAppFun != NULL)
	{
		if (Copy_U8IntNum <=2 )
		{
				EXTI_pfunISRFun[Copy_U8IntNum] = Copy_pfunAppFun;
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANG;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}