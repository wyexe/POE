#ifndef __LFZL_CHEATDLL_EXPR_CMDEXPR_H__
#define __LFZL_CHEATDLL_EXPR_CMDEXPR_H__

#include <LogLib/LogExpression.h>


class CCmdExpr : public libTools::CExprFunBase
{
public:
	CCmdExpr();
	virtual ~CCmdExpr();

	static CCmdExpr& GetInstance();
public:
	virtual std::vector<libTools::ExpressionFunPtr>& GetVec() override;

	virtual VOID Release() override;

private:
	virtual VOID Help(CONST std::vector<std::wstring>&) override;

	virtual VOID PrintPerson(CONST std::vector<std::wstring>&);

	virtual VOID PrintBag(CONST std::vector<std::wstring>&);

	virtual VOID PrintWarehouse(CONST std::vector<std::wstring>&);

	virtual VOID PrintAroundObject(CONST std::vector<std::wstring>&);

	virtual VOID PrintChest(CONST std::vector<std::wstring>&);

	virtual VOID PrintNpc(CONST std::vector<std::wstring>&);

	virtual VOID PrintMonster(CONST std::vector<std::wstring>&);

	virtual VOID PrintPlayer(CONST std::vector<std::wstring>&);

	virtual VOID PrintWorldItem(CONST std::vector<std::wstring>&);

	virtual VOID MouseMove(CONST std::vector<std::wstring>&);

	virtual VOID PrintUi(CONST std::vector<std::wstring>&);

	virtual VOID WatchUi(CONST std::vector<std::wstring>&);

	virtual VOID PrintItem(CONST std::vector<std::wstring>&);

	virtual VOID PrintBuff(CONST std::vector<std::wstring>&);

	virtual VOID PrintEffect(CONST std::vector<std::wstring>&);

	virtual VOID Test(CONST std::vector<std::wstring>&);
};



#endif // !__LFZL_CHEATDLL_EXPR_CMDEXPR_H__
