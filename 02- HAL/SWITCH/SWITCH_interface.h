#ifndef _HAL_SWITCH_INTERFACE_H_
#define _HAL_SWITCH_INTERFACE_H_



ES_t SWITCH_enuIniti(SW_t *Copy_pAstrSwitchConfig);

//ES_t SWITCH_enuIniti(SW_t * Copy_pAstrSwitchConfig);
/*switch is always input> so we need to know whether it is float or pull_up*/
 ES_t SWITCH_enuGetState(SW_t *Copy_pAstrSwitchInfo, U8 *Copy_pU8Value);


#endif /* _HAL_SWITCH_INTERFACE_H_ */
