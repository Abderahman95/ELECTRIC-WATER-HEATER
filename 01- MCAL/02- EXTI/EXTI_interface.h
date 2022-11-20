#ifndef _MCAL_EXTI_INTERFACE_H_
#define _MCAL_EXTI_INTERFACE_H_


ES_t EXTI_enuInit (EXTI_t *Copy_pAstrEXTIConfig);

ES_t EXTI_enuSetSenseLevel(U8 Copy_U8IntNum, U8 Copy_U8SenceLevel);

ES_t EXTI_enuEnableInterrupt(U8 Copy_U8IntNum);

ES_t EXTI_enuDisableInterrupt(U8 Copy_U8IntNum);

ES_t EXTI_enuCallBack (volatile void (*Copy_pfunAppFun)(void), U8 Copy_U8IntNum);

#endif /* _MCAL_EXTI_INTERFACE_H_ */
