#include <iostream>
#include <windows.h>

int main() {
    // Try to run notepad.exe
    if (ShellExecuteA(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32) {
        std::cerr << "Failed to open Notepad" << std::endl;
        return 1;
    }

    return 0;
}
