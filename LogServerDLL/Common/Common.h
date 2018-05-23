#ifndef __LFZL_LOGSERVERDLL_COMMON_COMMON_H__
#define __LFZL_LOGSERVERDLL_COMMON_COMMON_H__

enum em_Sock_Msg
{
	em_Sock_Msg_Error			= 0xF,
	em_Sock_Msg_Initialize,
	em_Sock_Msg_KeepLive,		
	em_Sock_Msg_IsExistCmd,
	em_Sock_Msg_Log,
	em_Sock_Msg_DownLoad_File,

};

#define LFZL_LOG_SOCKET_PORT 12367

#endif // !__LFZL_LOGSERVERDLL_COMMON_COMMON_H__
