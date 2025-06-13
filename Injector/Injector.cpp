#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <iomanip>
#include <tchar.h>
#include <string>

DWORD GetProcIdByName(const TCHAR* procName) 
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // получаем снимки процессов всех
	if (hSnap == INVALID_HANDLE_VALUE) // если hSnap не получилось, возвращаем 10 код ошибки
	{
		return 10;
	}
	
	PROCESSENTRY32W pe32; // открываем pe32

	pe32.dwSize = sizeof(PROCESSENTRY32W); // об€зательно

	if (Process32First(hSnap, &pe32))  // —равнение процесса
	{
		do // делать
		{
			if (_tcscmp(pe32.szExeFile, procName) == 0)  // сравниваем название файла с нашим procName, если да - возвращаем 0
			{
				CloseHandle(hSnap);
				return pe32.th32ProcessID; // наш процесс
			}
		} 
		while (Process32Next(hSnap, &pe32)); // продолжаем пока не найдем
	}
	CloseHandle(hSnap); // нашли
	return 0;
}

int main() {
	
	BOOL WPM = 0;
	TCHAR targetProcess[260];  // Ѕуфер под им€ процесса (260 Ч MAX_PATH)
	std::wcout << L"Enter process name (example: notepad.exe): ";
	std::wcin.getline(targetProcess, 260); // читаем строку

	DWORD procId = GetProcIdByName(targetProcess);

	if (procId == 0) {
		std::wcout << L"Process not found!" << std::endl;
		return 1;
	}

	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procId);

	if (hProcess == NULL) {
		std::wcout << L"No access to process!" << std::endl;
		return 1;
	}

	std::wcout << L"Process found! ID: " << procId << std::endl;

	wchar_t pathDll[260];
	std::wcout << L"Enter path to dll: ";
	std::wcin.getline(pathDll, 260);
	size_t pathSize = (wcslen(pathDll) + 1) * sizeof(wchar_t);
	void* loc = VirtualAllocEx(hProcess, NULL, pathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WPM = WriteProcessMemory(hProcess, loc, pathDll, pathSize, 0);

	if (!WPM) {
		CloseHandle(hProcess);
		return -1;
	}

	LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
	if (loadLibraryAddr == NULL) {
		std::wcout << L"loadlibraryaddr = 0" << std::endl;
		return -1;
	}

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, loc, 0, NULL);

	if (hThread == NULL) {
		std::wcout << "Process failed to create remote thread!" << std::endl;
		VirtualFreeEx(hProcess, loc, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return -1;
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	VirtualFreeEx(hProcess, loc, 0, MEM_RELEASE);
	CloseHandle(hProcess);
	return 0;
}