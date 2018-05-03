#ifndef __LFZL_CHEATDLL_CORE_FEATURE_POINTCONVERT_POINTCONVERTER_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_POINTCONVERT_POINTCONVERTER_H__

#include <GameStruct.h>


class CPointConverter
{
public:
	CPointConverter() = default;
	~CPointConverter() = default;

	// 获取当前鼠标的屏幕坐标
	static Point GetCursorClientPos();

	// 获取当前鼠标的游戏坐标
	static Point GetCursorGamePos();

	// 将屏幕坐标转换成游戏坐标
	static Point ConvertClientPosToGamePos(_In_ CONST Point& ClientPos);

	// 将游戏坐标转换成屏幕坐标
	static BOOL ConvertGamePosToClientPos(_In_ CONST Point& ClientPos, _Out_ Point& GamePos);
private:

};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_POINTCONVERT_POINTCONVERTER_H__
