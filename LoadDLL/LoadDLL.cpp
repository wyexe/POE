// LoadDLL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <InjectorLib/ModuleInjector/NoTraceModuleInjector.h>


#pragma comment(lib,"InjectorLib.lib")
int main()
{
	libTools::CNoTraceModuleInjector NoTraceModuleInjector;

	std::wstring wsPath = L"C:\\DLL\\CheatDLL.dll";
	if (NoTraceModuleInjector.SetModuleContent(wsPath))
	{
		::DeleteFileW(wsPath.c_str());
		if (!NoTraceModuleInjector.LoadModule())
		{
			std::wcout << L"LoadModule Falid!" << std::endl;
		}
		else
		{
			std::wcout << L"LoadModule Succ!" << std::endl;
		}
	}
	else
	{
		std::wcout << L"UnExist DLL!" << std::endl;
	}
	
	system("pause");
    return 0;
}

