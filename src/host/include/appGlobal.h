#ifndef APPGLOBAL_H_
#define APPGLOBAL_H_


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/eventfd.h>


#define MAX_SUPPORT_TRANS_NUM           12  // �ܹ�֧�ֵ����ת��·��
#define MAX_SUPPORT_TRANS_SD_NUM        12  // �ܹ�֧�ֵ�������·�� - ������ʹ��
#define MAX_SUPPORT_TRANS_HD_NUM        4   // �ܹ�֧�ֵ�������·��
#define MAX_SUPPORT_AUDIO_NUM_PROGRAM   4   // ÿ����Ŀ��֧�ֵ������Ƶ����

#define OS_MAX_LINE_LEN              1024    // ϵͳ֧�ֵ����һ���ַ�������
#define OS_MAX_FILE_NAME_LEN         1024    // ϵͳ֧�ֵ�����ļ�������
#define OS_INVALID_FD                  (-1)  // ��Ч���ļ�������

typedef unsigned char           U8;
typedef unsigned short          U16;
typedef unsigned int            U32;
typedef unsigned long long      U64;
typedef signed char             S8;
typedef signed short            S16;
typedef signed int              S32;
typedef long long               S64;


#endif



