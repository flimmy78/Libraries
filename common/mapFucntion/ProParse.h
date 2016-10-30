/*
*�������Ľ��������ĺ����ӿ�
*/
#ifndef PROPARSE_H
#define PROPARSE_H

#include <map>
#include "log.h"

//������λ�����б���֡��������
typedef enum CmdType 
{
	Err              = 0,
	ReadParam        = 1,
	WriteParam       = 2,
	CtrlBattery      = 3,
	CtrlLED          = 4,
	Test485          = 5,
	SwitchTo232      = 6,
	SwitchToInfrared = 7,
	TftpUpdate       = 8,
} CT;

typedef enum ParseResult 
{
	PT_NORMAL         = 0,
	PT_SUCCESS        = 1,
	PT_FAILED         = 2,
} PARSE_RESULT;

class CProParse
{
public:
	CProParse();
	~CProParse();

public:
	//���ݱ��ĵ����ͽ�����Ӧ�Ĵ���
	PARSE_RESULT HandleFrameByCmd(CmdType cmd, FrameStruct* tmpFrame, BYTE* sndBuff, int& wLen);

	typedef PARSE_RESULT (CProParse::*Framefunc)(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//��������ݱ���
	PARSE_RESULT ParseRead(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//����д���ݱ���
	PARSE_RESULT ParseWrite(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//������Ƶ�ص�������
	PARSE_RESULT ParseBatteryCtrl(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//�������LED����
	PARSE_RESULT ParseLEDCtrl(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//������̫������
	PARSE_RESULT ParseTftpUpdate(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//�����л�������
	PARSE_RESULT ParseSwitchToInfrared(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//�����л���232
	PARSE_RESULT ParseSwitchTo232(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);

private:
	map<CmdType, Framefunc>     m_MapFunc;
};

#endif
