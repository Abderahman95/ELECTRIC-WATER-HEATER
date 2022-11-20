#ifndef _APP_TMU_INTERFACE_H_
#define _APP_TMU_INTERFACE_H_


ES_t TMU_enuInit(void);
ES_t TMU_enuCreateTask(void(*Copy_pfunTask)(void),U8 Copy_U8Priority, U8 Copy_U8Periodicity);
ES_t TMU_enuStartScheduler(void);

ES_t TMU_enuSuspendTask(U8 Copy_U8Priority);
ES_t TMU_enuResumeTask (U8 Copy_U8Priority);
ES_t TMU_enuDeleteTask (U8 Copy_U8Priority);

#define READY										11
#define SUSPEND										12
#define KILLED										13

#endif /* _APP_TMU_INTERFACE_H_ */
