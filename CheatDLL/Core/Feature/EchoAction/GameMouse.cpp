#include "GameMouse.h"
#include <cmath>
#include <LogLib/Log.h>
#include <ProcessLib/KeyboardMsg/KeyboardMsg.h>
#include <TimeLib/TimeRand.h>

#pragma comment(lib,"TimeLib.lib")

#define _SELF L"GameMouse.cpp"
CGameMouse& CGameMouse::GetInstance()
{
	static CGameMouse Instance;
	return Instance;
}


VOID CGameMouse::MoveTo(_In_ CONST Point& Pos)
{
	MoveToPoint(Pos);
}

VOID CGameMouse::MoveToClient(_In_ CONST Point& Pos)
{
	MoveToPoint(Pos);
}

VOID CGameMouse::MoveToPoint(_In_ CONST Point& Pos) CONST
{
	POINT CursorPos;
	if (!::GetCursorPos(&CursorPos))
	{
		LOG_MSG_CF(L"GetCursorPos = FALSE!");
		return;
	}

	tagMovePoint A(CursorPos.x, CursorPos.y);
	tagMovePoint B(Pos.X, Pos.Y);

	LineMove(A, B);
	/*switch (libTools::CTimeRand::GetRand(1, 5)) // 随机移动路线
	{
	case 2:
		LineMove(A, B);
		break;
	case 4:
		RectangleMove(A, B);
		break;
	default:
		LineMove(A, B);
		break;
	}*/
}

VOID CGameMouse::CircelMove(_In_ CONST tagMovePoint& A, _In_ CONST tagMovePoint& B) CONST
{
	// 设当前鼠标的坐标=A， 终点坐标=B 
	// 圆的直径 ^ 2 = (A.X - B.X)^2 + (A.Y - B.Y) ^ 2
	float L = sqrt(pow(static_cast<float>(abs(A.X - B.X)), 2) + pow(static_cast<float>(abs(A.Y - B.Y)), 2));
	// 半径
	float r = L / 2;
	// 圆心(a,b) = [A.X + (B.X - A.X), (A.Y + (B.Y - A.Y))]
	
	tagMovePoint CircleCenter((A.X + B.X) / 2, (A.Y + B.Y) / 2);
	LOG_C_D(L"A(%d,%d) B(%d,%d) r(%d,%d) r[%d] L[%d]", A.X, A.Y, B.X, B.Y, CircleCenter.X, CircleCenter.Y, (int)r,(int)L);
#define PI 3.141592
	for (int Angle = 0; Angle <= 180; ++Angle)
	{
		// 在圆弧上的每一个点C(x,y)都有 (x - a)^2 + (y - b)^2 = r^2
		// 用三角函数 x = a + r * cos(Angle)
		// y = b + r * sin(Angle)
		int X = B.X > A.X ? static_cast<int>(CircleCenter.X + r * cos(PI / 180 * Angle)) : static_cast<int>(CircleCenter.X - r * cos(PI / 180 * Angle));
		int Y = B.Y > A.Y ? static_cast<int>(CircleCenter.Y + r * sin(PI / 180 * Angle)) : static_cast<int>(CircleCenter.Y - r * sin(PI / 180 * Angle));
		::SetCursorPos(X, Y);
		RandSleep();
	}

	::MessageBoxW(NULL, L"End!", L"", NULL);
	::SetCursorPos(B.X, B.Y);
}

VOID CGameMouse::LineMove(_In_ CONST tagMovePoint& A, _In_ CONST tagMovePoint& B) CONST
{
	// 求出2点间的距离
	float L = sqrt(pow(static_cast<float>(abs(A.X - B.X)), 2) + pow(static_cast<float>(abs(A.Y - B.Y)), 2));

	// 每次移动3 的距离
	CONST static float nDis = 3;

	// 相似三角形
	float fAngleX = (B.X - A.X) / L;
	float fAngleY = (B.Y - A.Y) / L;

	CONST static int dwArray[] = { -2 , -1, 0, 1, 2, 0 };
	
	for (float i = nDis; i < L; i += nDis)
	{
		int X = static_cast<int>(fAngleX * i);
		int Y = static_cast<int>(fAngleY * i);

		::SetCursorPos(A.X + X + dwArray[libTools::CTimeRand::GetRand(0, 5)] , A.Y + Y + dwArray[libTools::CTimeRand::GetRand(0, 5)]);
		RandSleep();
	}


	::SetCursorPos(B.X, B.Y);
}

VOID CGameMouse::RectangleMove(_In_ CONST tagMovePoint& A, _In_ CONST tagMovePoint& B) CONST
{
	// 每次移动5 的距离
	CONST static int nDis = 5;


	// 向往水平方向移动到B
	int nHorizontalDis = abs(B.X - A.X);
	bool IsMoveToRight = B.X > A.X ? true : false;
	for (int i = nDis; i < nHorizontalDis; i += nDis)
	{
		::SetCursorPos(IsMoveToRight ? A.X + i : A.X - i, A.Y);
		RandSleep();
	}
	::SetCursorPos(B.X, A.Y);


	// 垂直方向
	int nNverticalDis = abs(B.Y - A.Y);
	bool IsMoveToBottom = B.Y > A.Y ? true : false;
	for (int i = nDis; i < nNverticalDis; i += nDis)
	{
		::SetCursorPos(B.X, IsMoveToBottom ? A.Y + i : A.Y - i);
		RandSleep();
	}

	::SetCursorPos(B.X, B.Y);
}

VOID CGameMouse::RandSleep() CONST
{
	::Sleep(libTools::CTimeRand::GetRand(1, 5));
}
