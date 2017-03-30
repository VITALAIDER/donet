#include "stdafx.h"
#include <windows.h>
#include<iostream>

#include <ctime>

using namespace std;

//un handle catre obiectul de tip event folosit
HANDLE hEvent;
//zona de date comuna
int a = 1, b = 2;
#define NR_THREADS 4
HANDLE hthreads[NR_THREADS];


DWORD WINAPI citeste_date(LPVOID lpParam)
{

	WaitForSingleObject(hEvent, INFINITE);

	HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _T("Buffer.txt"));
	// MapViewOfFile :
	if (hFileMapping == NULL) {
		cout << "eroare la OpenFileMapping in write" << endl;
	}
	LPVOID result = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	DWORD* ForRead = static_cast<DWORD*>(result);
	int a1 = static_cast<int>(ForRead[0]);
	int b1 = static_cast<int>(ForRead[1]);
	//aici e problema
	if (a1 == 2 *b1)
	{
		cout << "correct\n";
	}
	cout << "Citire: " << ForRead[0] << " " << ForRead[1] << endl;
	
	return 0;
}

void modifica_date()
{
	srand(time(NULL));
	int a = rand() % 100 + 1;
	int ForWrite[2];
	ForWrite[0] = a;
	ForWrite[1] = 2 * a;
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
}
DWORD WINAPI scrie_date(LPVOID lpParam)
{

	WaitForSingleObject(hEvent, INFINITE);
	modifica_date();
	
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{	
	
	//creare semafor
	hEvent = CreateEvent(NULL, true, false, NULL);
	int nr = 5;
	while(nr>0){
	hthreads[0] = CreateThread(NULL, NULL, scrie_date, (LPVOID)0, NULL, NULL);
	SetEvent(hEvent);
	Sleep(2000);
	//crearea firelor de executie
	
		//trimit si numarul firului pentru a identifica ce fir face printare
		hthreads[1] = CreateThread(NULL, NULL, citeste_date, (LPVOID)1, NULL, NULL);
	

	//asteptam 2 secunde sa vedem ca firele care citesc asteapta si ele;
	Sleep(2000);
	//modificam datele si setam evenimentul:

	}
	//asteptam cele 4 fire de executie sa termine 
	WaitForMultipleObjects(NR_THREADS, hthreads, true, INFINITE);

	int x;
	cin >> x;
	//deinitializare obiect de tip event
	CloseHandle(hEvent);
	return 0;
}