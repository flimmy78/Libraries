#include "log.h"
#include "datetime.h"

CFileLog* CFileLog::m_pInstance = NULL;

CFileLog::CFileLog()
{
    m_logfile = NULL;
    m_Resfile = NULL;
    m_LogLevel = LEVEL_ERR;
    memset(m_LOGFILE, 0, sizeof(m_LOGFILE));
    memset(m_RESFILE, 0, sizeof(m_RESFILE));
    system("rm -rf *.log");
    system("rm -rf *.res");
    system("sync");

    time_t timep;
    struct tm *tmp;
    time(&timep);
    tmp = localtime(&timep);
    sprintf(m_LOGFILE, "%s-%04d%02d%02d%02d%02d%02d%s", 
                      "/home/et1000/HW_test",
                      tmp->tm_year+1900, 
                      tmp->tm_mon+1, 
                      tmp->tm_mday, 
                      tmp->tm_hour, 
                      tmp->tm_min, 
                      tmp->tm_sec,
                      ".log");
    sprintf(m_RESFILE, "%s-%04d%02d%02d%02d%02d%02d%s",
                     "/home/et1000/HW_test",
                     tmp->tm_year+1900,
                     tmp->tm_mon+1,
                     tmp->tm_mday,
                     tmp->tm_hour,
                     tmp->tm_min,
                     tmp->tm_sec,
                     ".res");    
}

CFileLog::~CFileLog()
{
    if (m_logfile)
    {
        fclose(m_logfile);
        m_logfile = NULL;
    }
}

CFileLog* CFileLog::GetInstance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new CFileLog();
    }
    
    return m_pInstance;

}

bool CFileLog::ReleaseInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }

    return true;
}

void CFileLog::SetLogLevel(LOG_LEVEL minLevel)
{
    m_LogLevel = minLevel;
}

void CFileLog::Log(LOG_LEVEL level, const char * strFileName, int nLine, const char * strFormat, ...)
{
    if (level < m_LogLevel)
    {
        return;
    }

	if(NULL == strFormat)
	{
		return;
	}

	char strInfo[1000] = {0};
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vsprintf(strInfo, strFormat, arg_ptr);
	va_end(arg_ptr);
	fputs(strInfo, stdout);

    if (NULL == m_logfile)
    {        
        m_logfile = fopen(m_LOGFILE, "a+");
    }

    fputs("\n", m_logfile);
    fprintf(m_logfile,"[ %s::%d ] ", strFileName, nLine);
    fprintf(m_logfile,"%s\n", strInfo);
    fputs("\n", m_logfile);
    fclose(m_logfile);
    m_logfile=NULL;
}

void CFileLog::LogRes(LOG_LEVEL level, const char * strFormat, ...)
{
    if (level < m_LogLevel)
    {
        return;
    }

    if(NULL == strFormat)
	{
		return;
	}

    if (NULL == m_Resfile)
    {
        m_Resfile = fopen(m_RESFILE, "a+");
    }

    char strInfo[1000] = {0};
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vsprintf(strInfo, strFormat, arg_ptr);
	va_end(arg_ptr);
	fputs(strInfo, stdout);

    fprintf(m_Resfile, "%s\n", strInfo);
    fputs("\n", m_Resfile);
    fclose(m_Resfile);
    m_Resfile = NULL;
}

