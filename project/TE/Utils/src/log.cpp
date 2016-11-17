#include "log.h"

CLog* CLog::m_pInstance = NULL;

CLog::CLog()
{
//    	m_logfile = NULL;
//    	m_Resfile = NULL;
	m_LogLevel = LEVEL_DEBUG;
//    	memset(m_LOGFILE, 0, sizeof(m_LOGFILE));

/*    	time_t timep;
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
*/
}

CLog::~CLog()
{
/*    if (m_logfile)
    {
        fclose(m_logfile);
        m_logfile = NULL;
    }
*/
}

CLog* CLog::GetInstance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new CLog();
    }
    
    return m_pInstance;

}

bool CLog::ReleaseInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }

    return true;
}

void CLog::SetLogLevel(LOG_LEVEL minLevel)
{
    m_LogLevel = minLevel;
}

void CLog::Log(LOG_LEVEL level, const char * strFileName, int nLine, const char * strFormat, ...)
{
	if (level < m_LogLevel)
	{
		return;
	}

	if(NULL == strFormat)
	{
		return;
	}

	char strInfo[512] = {0};
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vsprintf(strInfo, strFormat, arg_ptr);
	va_end(arg_ptr);
	//fputs(strInfo, stdout);
	char strOutPut[512] = {0};

	sprintf(strOutPut, "[%s::%d] %s", strFileName, nLine, strInfo);
	printf("%s\n", strOutPut);

/*	if (NULL == m_logfile)
	{        
		m_logfile = fopen(m_LOGFILE, "a+");
	}

	fprintf(m_logfile,"%s\n", strInfo);
	fclose(m_logfile);
	m_logfile = NULL;
*/
}
