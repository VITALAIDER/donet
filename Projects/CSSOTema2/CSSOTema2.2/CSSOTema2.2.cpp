// CSSOTema2.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <wchar.h>
#include <WinBase.h>
#include <string>
using namespace std;
//#pragma comment(lib, "cmcfg32.lib")

	BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(
		NULL,            // lookup privilege on local system
		lpszPrivilege,   // privilege to lookup 
		&luid))        // receives LUID of privilege
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.

	if (!AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)

	{
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}

	HANDLE WINAPI OpenFileMapping(
		_In_ DWORD   dwDesiredAccess,
		_In_ BOOL    bInheritHandle,
		_In_ LPCTSTR lpName
	)		;

	HANDLE open_process_token() {
		HANDLE token_handle;
		if (!OpenProcessToken(
			GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&token_handle
		)) {
			printf("OpenProcessToken error: %u\n", GetLastError());
		}
		return token_handle;
	}

int main()
{
	 HANDLE hFileMapping = OpenFileMapping(	FILE_MAP_ALL_ACCESS , FALSE, "Buffer.txt");
	// MapViewOfFile :
	 if (hFileMapping==NULL){
		 cout << "eroare la OpenFileMapping" << endl;
	 }
	 cout << "pb2: " << hFileMapping << endl;
	 LPCSTR lpFileMap = (LPCSTR) MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	
	SetPrivilege(open_process_token(), SE_DEBUG_NAME, TRUE);
	cout << "PB2: "<<lpFileMap << endl;
	int x;
	cin >> x;
    return 0;
}

