#include "ProParse.h"
#include "HWCommon.h"

FrameStruct* FrameList = NULL; 
CSemaphore Sem(0x88);
//CProParse* CProParse::m_pInstance = NULL;

CProParse::CProParse()
{
	m_bIs232 = true;
	m_MapFunc.insert(make_pair(ReadParam, &CProParse::ParseRead));
	m_MapFunc.insert(make_pair(WriteParam, &CProParse::ParseWrite));
	m_MapFunc.insert(make_pair(CtrlBattery, &CProParse::ParseBatteryCtrl));
	m_MapFunc.insert(make_pair(CtrlLED, &CProParse::ParseLEDCtrl));
	m_MapFunc.insert(make_pair(SwitchTo232, &CProParse::ParseSwitchTo232));
	m_MapFunc.insert(make_pair(SwitchToInfrared, &CProParse::ParseSwitchToInfrared));
	m_MapFunc.insert(make_pair(TftpUpdate, &CProParse::ParseTftpUpdate)); 
}

CProParse::~CProParse()
{
}

//��������ݱ���
PARSE_RESULT CProParse::ParseRead(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	LogToFile(LOGFILE, "CProParse::ParseRead");
	return PT_NORMAL;
}

//����д���ݱ���
PARSE_RESULT CProParse::ParseWrite(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	LogToFile(LOGFILE, "CProParse::ParseWrite");
	return PT_NORMAL;
}

//������Ƶ�ص�������
PARSE_RESULT CProParse::ParseBatteryCtrl(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	return PT_NORMAL;
}

//�������LED����
PARSE_RESULT CProParse::ParseLEDCtrl(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	return PT_NORMAL;
}

//������̫������
PARSE_RESULT CProParse::ParseTftpUpdate(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	return PT_NORMAL;
}

//�����л�������
PARSE_RESULT CProParse::ParseSwitchToInfrared(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	return PT_NORMAL;
}

//�����л���232
PARSE_RESULT CProParse::ParseSwitchTo232(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen)
{
	return PT_NORMAL;
}

//���ݱ��ĵ����ͽ�����Ӧ�Ĵ���
PARSE_RESULT CProParse::HandleFrameByCmd(CmdType cmd, FrameStruct* tmpFrame, BYTE* SndBuff, int& wLen)
{
	if (!tmpFrame)
	{
		return PT_NORMAL;
	}

	LogToFile(LOGFILE, "CProParse::HandleFrameByCmd");
	Framefunc function = m_MapFunc[cmd];
	PARSE_RESULT result = (this->*(function))(tmpFrame, SndBuff, wLen);
	m_SerialCom.SerialRW(SndBuff, wLen, NULL);
	return result;
}
