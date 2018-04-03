#ifndef __LFZL_TESTDLL_EXPR_H__
#define __LFZL_TESTDLL_EXPR_H__

#include <LogLib/LogExpression.h>

class CExpr : public libTools::CExprFunBase 
{
public:
	CExpr();
	virtual ~CExpr();

	virtual std::vector<libTools::ExpressionFunPtr>& GetVec() override;

	virtual VOID Release() override;

	static CExpr& GetInstance();
private:
	virtual VOID Help(CONST std::vector<std::wstring>& Vec) override;

	VOID PrintPlayerAttribute(CONST std::vector<std::wstring>& Vec);

	VOID PrintItem(CONST std::vector<std::wstring>&);

	VOID SwapAlloc(CONST std::vector<std::wstring>&);

	VOID PrintWarehouse(CONST std::vector<std::wstring>&);

	VOID PrintAroundObject(CONST std::vector<std::wstring>&);

	VOID ScanBase(CONST std::vector<std::wstring>&);
};



#endif // !__LFZL_TESTDLL_EXPR_H__
