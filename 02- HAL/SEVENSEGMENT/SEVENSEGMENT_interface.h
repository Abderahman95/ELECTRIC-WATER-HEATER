#ifndef _HAL_SEVENSEGMENT_INTERFACE_H_
#define _HAL_SEVENSEGMENT_INTERFACE_H_



//INITIALIZATION,DISPLAY,ENABLE,DISABLE,STOPDISPLAY
ES_t SevenSegment_enuInit(SSG_t *Copy_pAstrSevenSegmentConf);
ES_t SevenSegment_enuEnableCommon(SSG_t *Copy_pstrSevenSegmentInfo);
ES_t SevenSegment_enuEnableDot(SSG_t *Copy_pstrSevenSegmentInfo);
ES_t SevenSegment_enuDisplayNumber(SSG_t *Copy_pstrSevenSegmentInfo ,U8 Copy_U8Number);
ES_t SevenSegment_enuwrite(U16 Copy_U16Number);
void SevenSegment_Write(U8 Copy_U8Number);
ES_t SevenSegment_enuDisableCommon(SSG_t *Copy_pstrSevenSegmentInfo);
ES_t SevenSegment_enuDisableDot(SSG_t *Copy_pstrSevenSegmentInfo);
ES_t SevenSegment_enuStopDisplay(SSG_t *Copy_pstrSevenSegmentInfo);
ES_t SevenSegment_enuToggleDisplay(SSG_t *Copy_pstrSevenSegmentInfo);


//stop display the common on GIO

#endif /* _HAL_SEVENSEGMENT_INTERFACE_H_ */
