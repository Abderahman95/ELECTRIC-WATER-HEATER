#ifndef _HAL_SWITCH_CONFIG_H_
#define _HAL_SWITCH_CONFIG_H_

#define SW_NUM			3

//# define SWITCH_U8SwitchNumbers = SW_NUM;

typedef struct
{
		U8 SW_Port;
		U8 SW_Pin;
		U8 SW_State;

}SW_t;


#endif /* _HAL_SWITCH_CONFIG_H_ */
