#include<Windows.h>
#include<iostream>
#include<vector>
#include <tchar.h>

using namespace std;


void writeToRegistry(TCHAR* str, const char* file, bool is_file, DWORD data)
{
	DWORD lRv;
	HKEY hKey;
	DWORD dwDisposition;

	// Creeaza cheia
	lRv = RegCreateKeyEx(
		HKEY_CURRENT_USER,
		str,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition
	);

	DWORD dwValue = 1;
	//daca e fisier => Setare valoare registru fisier
	if (is_file) 
	{
		RegSetValueEx(
			hKey,
			file,
			0,
			REG_DWORD,
			(LPBYTE)&data,
			sizeof(data)
		);
	}
	//daca este director=>Setare valoare registru director
	else 
	{
		RegSetValueEx(
			hKey,
			file,
			0,
			REG_DWORD,
			NULL,
			sizeof(dwValue)
		);
		cout << "am ajuns in writeToRegistry \n";
	}
	RegCloseKey(hKey); //inchidem
}
//imi ia doar de la tema1\\...
char* substr(TCHAR* arr, int begin, int len)
{
	char* res = new char[len];
	for (int i = 0; i < len; i++)
		res[i] = *(arr + begin + i);
	res[len] = 0;
	cout <<"in substr: "<< res<<'\n';
	return res;
}

void findFile(TCHAR* file_name) {

	string sep = "\\";
	string search_string = file_name + sep + '*';
	char* sbstr = substr(file_name, 3, _tcslen(file_name));
	string s = sbstr;
	string temp_for_reg = "Software\\CSSO\\" + s;
	cout << "\n" <<"Registru: "<< temp_for_reg.c_str() << "\n";
	WIN32_FIND_DATA file_data;
	HANDLE find_file_handle = FindFirstFile(search_string.c_str(), &file_data);
	//daca nu "gaseste"
	if (find_file_handle == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	//daca "gaseste" primul fisier
	else
	{
		
		vector<string> directories; // stochez subdirectoarele
		do {
			if (strcmp(file_data.cFileName, ".") != 0 && strcmp(file_data.cFileName, "..") != 0) { //Pentru a evita parcurgerea infinita

				if ((file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // daca este folder
				{
					string temp = file_name + sep + file_data.cFileName;
					string temp_2 = temp_for_reg + sep + file_data.cFileName;
					directories.push_back(temp);
					writeToRegistry((TCHAR*)temp_2.c_str(), NULL, false, 0);
				}
				else {  //daca este fisier
					LARGE_INTEGER large;
					large.u.HighPart = file_data.nFileSizeHigh;
					large.u.LowPart = file_data.nFileSizeLow;
					writeToRegistry((TCHAR*)temp_for_reg.c_str(), file_data.cFileName, true, large.QuadPart);
				}
			}

		} while (FindNextFile(find_file_handle, &file_data) != ERROR_SUCCESS);

		FindClose(find_file_handle);

		//parcurg vectorul directories
		for (vector<string>::iterator iter = directories.begin(), end = directories.end(); iter != end; ++iter) {
			TCHAR* var = (TCHAR*)(*iter).c_str();
			cout << var << "\n";
			findFile(var);
		}
	}
}

int main() {

	TCHAR* path = "E:\\tema1";
	findFile(path);
	cin.get();
	return 0;
	
}