// dllmain.cpp: DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"


HWND hWnd;

extern "C"
{
	_declspec(dllexport)  int __cdecl ODBG_Plugindata(char shortname[32])
	{
		strcpy(shortname, "ImmWoW64");
		return 110;
	}
	_declspec(dllexport) int __cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, ulong *features)
	{
		DWORD Addr = (DWORD)GetModuleHandle(NULL) + 0x44D72;
		DWORD oldProtect;

		Addtolist(0, 0, "ImmWoW64");

		VirtualProtect((void*)Addr, 0x1, PAGE_EXECUTE_READWRITE, &oldProtect);
		if (*(DWORD *)Addr == 0x88831174)
		{
			*(unsigned char*)(Addr) = 0xEB;
			Addtolist(0, -1, "Patch Ok!");
		}
		else
			Addtolist(0, -1, "Path Faild..");
		VirtualProtect((void*)Addr, 0x1, oldProtect, &oldProtect);
		hWnd = hw;
		return 0;
	}
	_declspec(dllexport) int __cdecl ODBG_Pluginmenu(int origin, char data[4096], void *item)
	{
		if (origin == PM_MAIN)
		{
			strcpy(data, "0 &About");
			return 1;
		}
		return 0;
	}


	_declspec(dllexport) void __cdecl ODBG_Pluginaction(int origin, int action, void *item)
	{
		if (origin == PM_MAIN && action == 0)
				MessageBox(hWnd, L"ImmWoW64 plugin v0.1 by cha5126568\r\n ** Only For Immunity Debugger 1.85 ** \r\n", L"ImmWoW64", MB_OK | MB_ICONINFORMATION);
	}

}
BOOL APIENTRY Dllmain(HMODULE hModule, int reason, LPVOID lpReserved)
{
	return TRUE;
}

