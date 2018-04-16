#ifndef __LFZL_CHEATDLL_CORE_FEATURE_SEARCHER_OBJECTSEARCHER_H__
#define __LFZL_CHEATDLL_CORE_FEATURE_SEARCHER_OBJECTSEARCHER_H__

#include <vector>
#include <queue>
#include <functional>
#include <GameStruct.h>
#include <Core/Object/Item.h>
#include <Core/Object/Chest.h>
#include <Core/Object/Monster.h>
#include <Core/Object/Npc.h>
#include <Core/Object/Player.h>
#include <Core/Object/WorldItem.h>

class CObjectSearcher
{
public:
	CObjectSearcher();
	~CObjectSearcher();

	// 物品
	static UINT GetVecItem(_In_ DWORD dwAddr, _Out_ std::vector<CItem>& Vec);

	// 箱子
	static UINT GetVecChest(_Out_ std::vector<CChest>& Vec);

	// Npc
	static UINT GetVecNpc(_Out_ std::vector<CNpc>& Vec);

	// 怪物
	static UINT GetVecMonster(_Out_ std::vector<CMonster>& Vec);

	// 玩家
	static UINT GetVecPlayer(_Out_ std::vector<CPlayer>& Vec);

	// 地面物品
	static UINT GetVecWorlditem(_Out_ std::vector<CWorldItem>& Vec);

	// 传送点
	//static UINT GetVecWaypoint();

	// 传送门
	//static UINT GetVecAreaTransition();
private:
	template<typename T>
	static UINT GetVecObject(_Out_ std::vector<T>& Vec, _In_ std::function<BOOL(DWORD)> Matcher)
	{
		DWORD dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(人物基址 + 人物基址偏移1) + 1 * 4) + 人物基址偏移2) - 人物基址偏移3) + 物品遍历偏移1);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 物品遍历偏移2 + 物品遍历偏移3) + 0 * 4) + 0x8 + 周围对象遍历偏移1);
		dwAddr = ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(dwAddr + 4 * 4) - 周围对象遍历偏移2) + 周围对象遍历偏移3) + 周围对象遍历偏移4) + 周围对象遍历偏移5 + 0xC) + 0x4/*RootNode*/);

		std::queue<DWORD> VecStack;
		VecStack.push(dwAddr);
		

		while (!VecStack.empty())
		{
			DWORD dwNode = VecStack.front();
			VecStack.pop();

			DWORD dwLeftNode = ReadDWORD(dwNode + 0x0);
			DWORD dwRightNode = ReadDWORD(dwNode + 0x8);
			if (ReadBYTE(dwLeftNode + 0xD) == 0)
			{
				VecStack.push(dwLeftNode);
			}
			if (ReadBYTE(dwRightNode + 0xD) == 0x0)
			{
				VecStack.push(dwRightNode);
			}


			if (Matcher(ReadDWORD(dwNode + 0x14)))
			{
				Vec.emplace_back(ReadDWORD(dwNode + 0x14));
			}
		}

		return Vec.size();
	}
};



#endif // !__LFZL_CHEATDLL_CORE_FEATURE_SEARCHER_OBJECTSEARCHER_H__
