#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

// 日志级别
enum LOG_LEVEL
{ 
    LEVEL_ERR       = 0,    //默认级别
    LEVEL_NOTICE    = 1,    //提示级别
    LEVEL_DEBUG     = 2,    //调试级别
    LEVEL_REAL_TIME = 99    //最高级别，当收到reboot命令后，将所有日志实时同步到文件
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
