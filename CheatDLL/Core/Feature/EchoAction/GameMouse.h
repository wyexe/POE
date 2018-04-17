#ifndef __LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_GAMEMOUSE_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_GAMEMOUSE_H__

#include <GameStruct.h>

class CGameMouse
{
private:
	struct tagMovePoint
	{
		int X = 0, Y = 0;

		tagMovePoint(int tmpX, int tmpY) : X(tmpX), Y(tmpY) {}
	};
public:
	CGameMouse() = default;
	~CGameMouse() = default;

	static CGameMouse& GetInstance();
public:
	// In Client 
	VOID MoveTo(_In_ CONST Point& Pos);

	// in Screen
	VOID MoveToClient(_In_ CONST Point& Pos);
private:
	Point AddGameClientPos(_In_ CONST Point& Pos) CONST;

	VOID MoveToPoint(_In_ CONST Point& Pos) CONST;

	// 
	VOID CircelMove(_In_ CONST tagMovePoint& A, _In_ CONST tagMovePoint& B) CONST;

	// 
	VOID LineMove(_In_ CONST tagMovePoint& A, _In_ CONST tagMovePoint& B) CONST;

	// 
	VOID RectangleMove(_In_ CONST tagMovePoint& A, _In_ CONST tagMovePoint& B) CONST;

	//
	VOID RandSleep() CONST;
};


#endif // !__LFZL_CHEATDLL_CORE_FEATURE_ECHOACTION_GAMEMOUSE_H__
