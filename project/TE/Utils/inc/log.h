#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

enum LOG_LEVEL
{ 
    LEVEL_DEBUG      = 0,
    LEVEL_WARRNING  = 1,
    LEVEL_ERROR     = 2,
    LEVEL_FATAL     = 3,
};

#define LogD(strFormat, ...) \
    CLog::GetInstance()->Log(LEVEL_DEBUG, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LogW(strFormat, ...) \
    CLog::GetInstance()->Log(LEVEL_WARNING, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LogE(strFormat, ...) \
    CLog::GetInstance()->Log(LEVEL_ERROR, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LogF(strFormat, ...) \
    CLog::GetInstance()->Log(LEVEL_FATAL, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

class CLog
{
public:
    ~CLog();
    static CLog* GetInstance();
    static bool ReleaseInstance();
    void SetLogLevel(LOG_LEVEL minLevel);
    void Log(LOG_LEVEL level, const char * strFileName, int nLine, const char * strFormat, ...);
    
private:
    CLog();

private:
    LOG_LEVEL           m_LogLevel;
    static CLog*    	m_pInstance;
    char                m_LOGFILE[60];
    char                m_RESFILE[60];
    FILE*               m_logfile;
    FILE*               m_Resfile;
};

#endif //_LOG_H_
