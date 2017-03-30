// CSSOTema2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <wchar.h>
#include <WinBase.h>
#include <string>
using namespace std;

#define BUFFER_SIZE 1024
#define COPY_SIZE 512
#define BUF_SIZE 256
TCHAR szName[] = TEXT("C:\\Users\\sava\\Documents\\Visual Studio 2015\\Projects\\CSSOTema2\\mapa1");
TCHAR szMsg[] = TEXT("Message from first process.");

#define ROUND_UP_SIZE(Value,Pow2) ((SIZE_T) ((((ULONG)(Value)) + (Pow2) - 1) & (~(((LONG)(Pow2)) - 1))))

#define ROUND_UP_PTR(Ptr,Pow2)  ((void *) ((((ULONG_PTR)(Ptr)) + (Pow2) - 1) & (~(((LONG_PTR)(Pow2)) - 1))))

HANDLE WINAPI CreateFileMapping(
	_In_ HANDLE hFile,
	_In_opt_ LPSECURITY_ATTRIBUTES lpAttributes,
	_In_ DWORD flProtect,
	_In_ DWORD dwMaximumSizeHigh,
	_In_ DWORD dwMaximumSizeLow,
	_In_opt_ LPCTSTR lpName
);

LPVOID WINAPI MapViewOfFile(
	_In_ HANDLE hFileMappingObject,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwFileOffsetHigh,
	_In_ DWORD dwFileOffsetLow,
	_In_ SIZE_T dwNumberOfBytesToMap
);


HANDLE WINAPI CreateToolhelp32Snapshot(
 _In_ DWORD dwFlags,
 _In_ DWORD th32ProcessID
);



string PrintProcess()
{
	

	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	string output;
	//cer un snapshot la procese
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return to_string(-1);
	}
	//initializez dwSize cu dimensiunea structurii.
	pe32.dwSize = sizeof(PROCESSENTRY32);
	//obtin informatii despre primul proces
	if (!Process32First(hProcessSnap, &pe32))
	{
		printf("Process32First failed. err = %d \n", GetLastError());
		CloseHandle(hProcessSnap); //inchidem snapshot-ul
		return to_string(-1);
	}
	do
	{
		//afisez pid-ul si executabilul
		
		string temp = to_string (pe32.th32ProcessID);
		string temp2 = to_string(pe32.th32ParentProcessID);
		
		//strcat(output, temp);
		output = output + ' ' + temp + ' ';
		output = output + ' ' + temp2 + ' ';
		output = output + ' ' + pe32.szExeFile + ' ';



	//	printf("Process <[%d]> <[%d]> < [%s]> \n", pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);
	} while (Process32Next(hProcessSnap, &pe32)); //trec la urmatorul proces
	
	CloseHandle(hProcessSnap); //inchid handle-ul catre snapshot

	cout << "OUTPUT: " << endl;
	cout << output;
	

	//return 1;
	return output;
}
TCHAR * createMapFile()
{

	int x;
	
	
	string temp = PrintProcess();
	TCHAR* temp2 = (TCHAR*)temp.c_str();
	DWORD dwBytesWritten;
	HANDLE hf, hm, wf;
	TCHAR* mapview;
	//dwBytesWritten = sizeof(int)*N;
	dwBytesWritten = strlen(temp2) * sizeof(TCHAR);
//	hf = CreateFile("Buffer.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hm = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, dwBytesWritten, "Buffer.txt");
	mapview = (TCHAR*)MapViewOfFile(hm, FILE_MAP_ALL_ACCESS, 0, 0, dwBytesWritten);

	//
	if (mapview == NULL)
	{
		cout << endl << "eroare la creare" << endl;
	}
	
//	cout << "strlen(temp2) * sizeof(TCHAR): " << strlen(temp2) * sizeof(TCHAR);
	CopyMemory(mapview, temp2, strlen(temp2) * sizeof(TCHAR));
	

	cin >> x;
	UnmapViewOfFile(hm);
//	CloseHandle(hf);
	return mapview;
}



int main()
{

	int x;

	createMapFile();

	return 0;


}

