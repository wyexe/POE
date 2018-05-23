// LoadDLL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <InjectorLib/ModuleInjector/NoTraceModuleInjector.h>
#include <FileLib/File.h>

#ifdef _DEBUG
#pragma comment(lib,"FileLib_Debug.lib")
#pragma comment(lib,"InjectorLib_Debug.lib")
#else
#pragma comment(lib,"FileLib.lib")
#pragma comment(lib,"InjectorLib.lib")
#endif // _DEBUG


int main()
{
	libTools::CNoTraceModuleInjector NoTraceModuleInjector;

	std::wstring wsPath = L"C:\\Share\\DLL\\CheatDLL.dll";
	if (NoTraceModuleInjector.SetModuleContent(wsPath))
	{
		if (!NoTraceModuleInjector.LoadModule())
		{
			std::wcout << L"LoadModule Falid!" << std::endl;
		}
		else
		{
			std::wcout << L"LoadModule Succ!" << std::endl;
		}
		::DeleteFileW(wsPath.c_str());
	}
	else
	{
		std::wcout << L"UnExist DLL!" << std::endl;
	}
	
	while (true)
	{
		::Sleep(1000);
	}
    return 0;
}

