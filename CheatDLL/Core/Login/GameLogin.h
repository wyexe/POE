#ifndef __LFZL_CHEATDLL_CORE_LOGIN_GAMELOGIN_H__
#define __LFZL_CHEATDLL_CORE_LOGIN_GAMELOGIN_H__

#include <GameStruct.h>
#include <functional>

class CGameLogin
{
public:
	enum class em_Login_RetCode
	{
		Succ,
		Band,
		Faild
	};
public:
	CGameLogin() = default;
	~CGameLogin() = default;

	em_Login_RetCode Begin();
private:
	BOOL IsExistGameProc() CONST;

	BOOL IsTimeOut(_In_ DWORD dwTimeout, _In_ std::function<BOOL(VOID)> Ptr) CONST;

	BOOL IsExistGameWindows() CONST;

	BOOL IsAlreadyInChoicPlayer() CONST;

	BOOL IsAlreadyInGameState() CONST;

	BOOL IsAreaLoadingState() CONST;

	em_Login_RetCode ChoicPlyaerToGame() CONST;
};



#endif // !__LFZL_CHEATDLL_CORE_LOGIN_GAMELOGIN_H__
