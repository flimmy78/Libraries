#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

// ��־����
enum LOG_LEVEL
{ 
    LEVEL_ERR       = 0,    //Ĭ�ϼ���
    LEVEL_NOTICE    = 1,    //��ʾ����
    LEVEL_DEBUG     = 2,    //���Լ���
    LEVEL_REAL_TIME = 99    //��߼��𣬵��յ�reboot����󣬽�������־ʵʱͬ�����ļ�
};

#define LOGFileD(strFormat, ...) \
    CFileLog::GetInstance()->Log(LEVEL_DEBUG, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LOGFileE(strFormat, ...) \
    CFileLog::GetInstance()->Log(LEVEL_ERR, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LOGFileN(strFormat, ...) \
    CFileLog::GetInstance()->Log(LEVEL_NOTICE, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LOGFileR(strFormat, ...) \
    CFileLog::GetInstance()->Log(LEVEL_REAL_TIME, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)


#define LOGResD(strFormat, ...) \
    CFileLog::GetInstance()->LogRes(LEVEL_DEBUG, strFormat, ## __VA_ARGS__)

#define LOGResE(strFormat, ...) \
    CFileLog::GetInstance()->LogRes(LEVEL_ERR, strFormat, ## __VA_ARGS__)

#define LOGResN(strFormat, ...) \
    CFileLog::GetInstance()->LogRes(LEVEL_NOTICE, strFormat, ## __VA_ARGS__)

#define LOGResR(strFormat, ...) \
    CFileLog::GetInstance()->LogRes(LEVEL_REAL_TIME, strFormat, ## __VA_ARGS__)

class CFileLog
{
public:
    ~CFileLog();
    static CFileLog* GetInstance();
    static bool ReleaseInstance();
    void SetLogLevel(LOG_LEVEL minLevel);
    void SetLogResFiles(const char* LogFile, const char* ResFile);
    void Log(LOG_LEVEL level, const char * strFileName, int nLine, const char * strFormat, ...);
    void LogRes(LOG_LEVEL level, const char * strFormat, ...);
    
private:
    CFileLog();

private:
    LOG_LEVEL           m_LogLevel;
    static CFileLog*    m_pInstance;
    char                m_LOGFILE[60];
    char                m_RESFILE[60];
    FILE*               m_logfile;
    FILE*               m_Resfile;
};

#endif //_LOG_H_
