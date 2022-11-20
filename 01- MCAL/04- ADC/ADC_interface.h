#ifndef _MCAL_ADC_INTERFACE_H_
#define _MCAL_ADC_INTERFACE_H_


ES_t ADC_enuInit(void);
ES_t ADC_enuEnableADC(void);
ES_t ADC_enuDisableADC(void);
ES_t ADC_enuEnableADC_Intrrupt(void);
ES_t ADC_enuDisableADC_Intrrupt(void);
ES_t ADC_enuStartConversion(void);
ES_t ADC_enuChannelSelect(U8 Ccopy_U8ChannelID);
ES_t ADC_enuAutoTriggerSource(U8 Copy_U8InterruptSource);
ES_t ADC_enuAutoTriggerDisable(void);
ES_t ADC_enuReadDataRegister(U16 *Copy_pU16ConversionResult);

ES_t ADC_enuCallBack(volatile void( *Copy_pfunAppFun) (void));

ES_t ADC_enuPolling(void);


#endif /* _MCAL_ADC_INTERFACE_H_ */
