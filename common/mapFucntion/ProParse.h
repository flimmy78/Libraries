/*
*声明报文解析及填充的函数接口
*/
#ifndef PROPARSE_H
#define PROPARSE_H

#include <map>
#include "log.h"

//定义上位机下行报文帧命令类型
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
	//根据报文的类型进行相应的处理
	PARSE_RESULT HandleFrameByCmd(CmdType cmd, FrameStruct* tmpFrame, BYTE* sndBuff, int& wLen);

	typedef PARSE_RESULT (CProParse::*Framefunc)(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//处理读数据报文
	PARSE_RESULT ParseRead(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//处理写数据报文
	PARSE_RESULT ParseWrite(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//处理控制电池掉电命令
	PARSE_RESULT ParseBatteryCtrl(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//处理点亮LED命令
	PARSE_RESULT ParseLEDCtrl(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//解析以太网升级
	PARSE_RESULT ParseTftpUpdate(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//解析切换到红外
	PARSE_RESULT ParseSwitchToInfrared(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);
	//解析切换到232
	PARSE_RESULT ParseSwitchTo232(FrameStruct* tmpFrame, BYTE* SndBuff, int& SndLen);

private:
	map<CmdType, Framefunc>     m_MapFunc;
};

#endif
