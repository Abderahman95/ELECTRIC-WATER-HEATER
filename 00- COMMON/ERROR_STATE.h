#ifndef _COMMON_ERROR_STATE_H_
#define _COMMON_ERROR_STATE_H_

typedef enum
{
	
	ES_NOK,
	ES_OK,
	ES_OUT_OF_RANG,
	ES_NULL_POINTER,
	ES_I2C_Ok,
	ES_I2C_SC_Error,
	ES_I2C_RSC_Error,
	ES_I2C_SLA_W_Error,
	ES_I2C_SLA_R_Error,
	ES_I2C_DATA_Error,
	ES_I2C_MR_DATA_Error

}ES_t;

#endif /* _COMMON_ERROR_STATE_H_ */
