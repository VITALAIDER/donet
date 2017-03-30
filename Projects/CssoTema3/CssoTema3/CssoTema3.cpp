// CssoTema3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <wchar.h>
#include <WinBase.h>
#include <string>
#include<ctime>
using namespace std;

//un handle catre obiectul de tip mutex folosit
HANDLE hMutex;
//zona de date comuna
int a, b;

int returnA()
{
	srand(time(NULL));
	a = rand() % 100 ;
	return a;
}
TCHAR * createMapFileScriere()
{
	
	int ForWrite[2];
	a = returnA();
	ForWrite[0] = a;
	ForWrite[1] = 2 * a; //b
	DWORD dwBytesWritten;
	HANDLE  hm;
	TCHAR* mapview;
	dwBytesWritten = 8 * sizeof(TCHAR); //aici am hardcodat
	
	hm = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, dwBytesWritten, _T("Buffer.txt"));
	mapview = (TCHAR*)MapViewOfFile(hm, FILE_MAP_ALL_ACCESS, 0, 0, dwBytesWritten);

	//
	if (mapview == NULL)
	{
		cout << endl << "eroare la creare" << endl;
	}

	CopyMemory(mapview, ForWrite, 8 * sizeof(TCHAR));
	cout << "am iesit din scriere\n";

	UnmapViewOfFile(hm);
	//	CloseHandle(hf);
	return mapview;
}

DWORD WINAPI scrie_date(LPVOID lpParam)
{
	int nr = 200;
	while (nr > 0) {
		//se acceseaza datele comune pentru scriere, deci se intra in sectiune critica
		WaitForSingleObject(hMutex, INFINITE);
		createMapFileScriere();
		ReleaseMutex(hMutex);

		
		nr--;
	}
	return 0;
}

DWORD WINAPI citeste_date(LPVOID lpParam)
{
	int nr = 200;
	while(nr>0){
		//se acceseaza datele comune pentru citire, deci se intra in seciune critica
		WaitForSingleObject(hMutex, INFINITE);
		
		HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _T("Buffer.txt"));
		// MapViewOfFile :
		if (hFileMapping == NULL) {
			cout << "eroare la OpenFileMapping in write" << endl;
		}
		LPVOID result = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		DWORD* ForRead = static_cast<DWORD*>(result);
		if(ForRead[0] == 2* ForRead[1])
		{
			cout << "correct";
		}
		cout << "Citire: " << ForRead[0] <<" "<< ForRead[1]<< endl;
		
		ReleaseMutex(hMutex);
		cout << "am iesti din citire\n";

	nr--;
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread1, hThread2;
	//creare mutex
	hMutex = CreateMutex(NULL, false, NULL);
	

	//crearea firului de executie care va scrie date
	hThread1 = CreateThread(NULL, NULL, scrie_date, NULL, NULL, NULL);
	//creare firului de executie care va citi datele
	hThread2 = CreateThread(NULL, NULL, citeste_date, NULL, NULL, NULL);
	
	//asteptam cele 2 fire de executie sa termine
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	

	int x;
	cin >> x;
	//deinitializare obiect de tip mutex
	CloseHandle(hMutex);
	return 0;
}



	



	
