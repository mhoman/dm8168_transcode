#ifndef WV_TSINPUT_H_
#define WV_TSINPUT_H_

#include "appGlobal.h"
#include "linux/types.h" 


#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libavutil/time.h"
#include "libavutil/mathematics.h"
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/audio_fifo.h"
#include "libavfilter/avfiltergraph.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"

#define INPUT_TS_MAX_PROGRAM_NUM        2
#define INPUT_TS_MAX_FRAME_BUFFER_NUM   60
#define MAX_STREAM_NUM                  30      
#define MAX_PROGTRAM_NAME_LEN           50      


/* �����һ֡����Ƶ���� */
typedef struct {
    /* һ֡���� */
    AVPacket *  pktData;
} INPUT_TS_FRAME_S;

/* һ������������ */
typedef struct {   
    u_int32_t                   u32StreamId;    // PID
    u_int32_t                   u32StreamIndex; // Stream index
    enum AVMediaType            eStreamType;    // Stream 


    /* �����֡�� */
    u_int32_t           numFrames;
   
    /* ������� */
    INPUT_TS_FRAME_S    frameBuf[INPUT_TS_MAX_FRAME_BUFFER_NUM];
    
    /* ��������֪ͨ�¼� */
    int32_t             inputEventFd; 
} INPUT_STREAM_FRAME_LIST_S;


/* һ�������Ŀ���� */
typedef struct {
    u_int32_t                         u32ProgramId;
    u_int8_t                          u8ServiceName[MAX_PROGTRAM_NAME_LEN];         // Program name
    u_int8_t                          u8ServiceProder[MAX_PROGTRAM_NAME_LEN];       // Provider name 
    u_int32_t                         u32StreamNum;                                 // Stream count
    INPUT_STREAM_FRAME_LIST_S         stStreams[MAX_SUPPORT_STREAM_NUM_PROGRAM];       
} INPUT_TS_PROGRAM_LIST_S;


/* һ������ͨ��  */
typedef struct
{
    /* ����ͨ��ID */
    u_int32_t           channelId;   
    
    /* ����ͨ����URL��ַ */
    int8_t              inputURL[OS_MAX_LINE_LEN]; 

    /* �������Ƶ������ */
    AVFormatContext *   ifmt_ctx;

    /* �Ƿ��ȡ���� */
    int8_t              inputReadFlag; 

    /* ��Ŀ���� */
    u_int32_t           programNum;
    
    /* ��Ŀbuffer */
   	INPUT_TS_PROGRAM_LIST_S programInfo[INPUT_TS_MAX_PROGRAM_NUM];
}TSIP_INPUT_CHANNEL_S;

/* TS������ */
typedef struct
{
    TSIP_INPUT_CHANNEL_S  inputChannel[MAX_SUPPORT_TRANS_NUM];
}TSIP_INPUT_S;


TSIP_INPUT_S *  tsInput_GetHandler(void);
int32_t         tsInput_Init(void);
int32_t         tsInput_StartChannel(const int32_t inpuChannelNum, const int8_t * url);
int32_t         tsInput_StopChannel(const int32_t inpuChannelNum);
int32_t         tsInput_WriteChannelVideoPkt(const int32_t inpuChannelNum, AVPacket *  pstPkt);
int32_t         tsInput_ReadChannelVideoPkt(const int32_t inpuChannelNum, AVPacket *  pstPkt);
int32_t         tsInput_WriteChannelAudioPkt(const int32_t inpuChannelNum, const int32_t audioChannelNum, AVPacket *  pstPkt);
int32_t         tsInput_ReadChannelAudioPkt(const int32_t inpuChannelNum, const int32_t audioChannelNum, AVPacket *  pstPkt);
int32_t         tsInput_GetChannelVideoPktNum(const int32_t inpuChannelNum);
int32_t         tsInput_GetChannelAudioPktNum(const int32_t inpuChannelNum, const int32_t audioChannelNum);

#endif


