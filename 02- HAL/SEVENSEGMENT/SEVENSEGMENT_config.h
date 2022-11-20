#ifndef _HAL_SEVENSEGMENT_CONFIG_H_
#define _HAL_SEVENSEGMENT_CONFIG_H_

#define SSG_NUMBER 					2

typedef  struct
{
	//SSG_Seven Pins
	U8 SSG_PinA_Port;				U8 SSG_PinA_Pin;
	U8 SSG_PinB_Port;				U8 SSG_PinB_Pin;
	U8 SSG_PinC_Port;				U8 SSG_PinC_Pin;
	U8 SSG_PinD_Port;				U8 SSG_PinD_Pin;
	U8 SSG_PinE_Port;				U8 SSG_PinE_Pin;
	U8 SSG_PinF_Port;				U8 SSG_PinF_Pin;
	U8 SSG_PinG_Port;				U8 SSG_PinG_Pin;


	U8 SSG_Common_Port;				U8 SSG_Common_Pin;
	U8 SSG_Dot_Port;				U8 SSG_Dot_Pin;

	U8 SSG_Type;



}SSG_t;




#endif /* _HAL_SEVENSEGMENT_CONFIG_H_ */
