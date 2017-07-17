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

#define INPUT_TS_MAX_PROGRAM_NUM        2       // program number per ts
#define INPUT_TS_MAX_FRAME_BUFFER_NUM   60
#define MAX_STREAM_NUM                  30      // max stream number per ts
#define MAX_PROGTRAM_NAME_LEN           50      

#define MAX_AUDIO_NUM_PER_PROGRAM        4
#define MAX_SUPPORT_STREAM_PER_PROGRAM   (MAX_AUDIO_NUM_PER_PROGRAM + 1)   // ÿ����Ŀ��֧�ֵ�������

#define __aligned(x) __attribute__((aligned(x)))


/* �����һ֡����Ƶ���� */
#pragma pack (4)
typedef struct {
    /* һ֡���� */
    AVPacket *  pktData;
} __aligned(4) INPUT_TS_FRAME_S;

/* һ������������ */
#pragma pack (4)
typedef struct {   
    /* PID */
    U32                         u32StreamId; 

    /* program index */
    U32                         u32ProgramIndex;

    /* Stream index */
    U32                         u32StreamIndex;  

    /* stream type */
    enum AVMediaType            eStreamType; 

    /* buffer lock */
    pthread_mutex_t             bufferLock;


    /* �����֡�� */
    U32                         numFrames;
   
    /* ������� */
    INPUT_TS_FRAME_S            frameBuf[INPUT_TS_MAX_FRAME_BUFFER_NUM];
    
    /* ��������֪ͨ�¼� */
    S32                         inputEventFd; 
} __aligned(4) INPUT_STREAM_FRAME_LIST_S;


/* һ�������Ŀ���� */
#pragma pack (4)
typedef struct {
    U32                                 u32ProgramId;                                   
    U8                                  u8ServiceName[MAX_PROGTRAM_NAME_LEN];         // Program name
    U8                                  u8ServiceProder[MAX_PROGTRAM_NAME_LEN];       // Provider name 
    U32                                 u32StreamNum;                                 // Stream count
    U32                                 u32AudioStreamNum;  

    U32                                 u32VideoInputIndex;
    U32                                 u32VideoBufferIndex;
    U32                                 u32AudioInputIndex[MAX_AUDIO_NUM_PER_PROGRAM];  // stream index of ffmpeg ifctx
    U32                                 u32AudioBufferIndex[MAX_AUDIO_NUM_PER_PROGRAM]; // stream index of program
    
    INPUT_STREAM_FRAME_LIST_S           stStreams[MAX_SUPPORT_STREAM_PER_PROGRAM];       
} __aligned(4) INPUT_TS_PROGRAM_LIST_S;


/* һ������ͨ��  */
#pragma pack (4)
typedef struct
{
    /* ����ͨ��ID */
    U32                     channelId;   
    
    /* ����ͨ����URL��ַ */
    S8                      inputURL[OS_MAX_LINE_LEN]; 

    /* �������Ƶ������ */
    AVFormatContext *       ifmt_ctx;

    /* �Ƿ��ȡ���� */
    S8                      inputReadFlag; 

    /* �Ƿ��˳� */
    S8                      exitFlag;

    /* ��Ŀ���� */
    U32                     programNum;

    /* �Ƿ񱣴浽�ļ� */
    U32                     localSave;
    
    /* ��Ŀbuffer */
   	INPUT_TS_PROGRAM_LIST_S programInfo[INPUT_TS_MAX_PROGRAM_NUM];
}__aligned(4) TSIP_INPUT_CHANNEL_S;

/* TS������ */
#pragma pack (4)
typedef struct
{
    TSIP_INPUT_CHANNEL_S  inputChannel[MAX_SUPPORT_TRANS_NUM];
}__aligned(4) TSIP_INPUT_S;


TSIP_INPUT_S *  tsInput_GetHandler(void);
S32             tsInput_Init(void);
S32             tsInput_StartChannel(const S32 inpuChannelNum, const S8 * url);
S32             tsInput_StopChannel(const S32 inpuChannelNum);
S32             tsInput_WriteChannelVideoPkt(const S32 inpuChannelNum, AVPacket *  pstPkt);
S32             tsInput_ReadChannelVideoPkt(const S32 inpuChannelNum, const S32 programIndex, AVPacket ** pstPkt);
S32             tsInput_WriteChannelAudioPkt(const S32 inpuChannelNum, AVPacket *  pstPkt);
S32             tsInput_ReadChannelAudioPkt(const S32 inpuChannelNum, const S32 programIndex, const S32 audioIndex, AVPacket **  pstPkt);
S32             tsInput_GetChannelVideoPktNum(const S32 inpuChannelNum, const S32 programIndex );
S32             tsInput_GetChannelAudioPktNum(const S32 inpuChannelNum, const S32 programIndex, const S32 audioIndex);
bool            tsInput_VideoBufferIsFull(const S32 inpuChannelNum, const S32 programIndex);
bool            tsInput_AudioBufferIsFull(const S32 inpuChannelNum, const S32 programIndex, const S32 audioIndex);
S32             tsInput_WaitChannelStart(const S32 inpuChannelNum, const S32 timeOut);

S32             tsInput_Test(void);

#endif


