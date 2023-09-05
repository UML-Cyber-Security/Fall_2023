# Speaker Notes Meeting 1

## Member Prereqs (stuff they should have for meeting to be smooth)
+ Web Version does not support VBA macros, does not support .docm files.
+ Download Word for free as a student: <https://www.microsoft.com/en-us/education/products/office>

## Speaker Prereqs (before meeting)
+ Have several windows VMs set up, in case one breaks. Can use Proxmox for this.
+ Do I need to set up windows VMs on the Cyber Range machines?

## DMARC explanation
<https://www.learndmarc.com/>

### .scr/.exe files
mingw-w64 that provides a cross-compiler for Windows.

### Website setup?
+ Setup website as a payload they can download & run if they want to

## Windows Coding Setup
I used a proxmox VM for access to a windows machine.
To use C++ I had to download mingw from their github. I used the 
x86_64-13.1.0-release-win32-seh-msvcrt-rt_v11-rev1.7z  for a broader compatibility.

I had to install 7zip to extract the file.

Edit the system environment variables, and add mingw/bin directory to System -> Path.


Shell execute signature:

HINSTANCE ShellExecute(
  HWND     hwnd,
  LPCTSTR  lpOperation,
  LPCTSTR  lpFile,
  LPCTSTR  lpParameters,
  LPCTSTR  lpDirectory,
  INT      nShowCmd
);

Parameters

    hwnd: This is a handle to the parent window of the dialog box that might appear (for example, a file dialog if the file doesn't exist). Generally, this can be NULL.

    lpOperation: This specifies the action to be performed. Common strings for this parameter are "open", "edit", "runas", etc. If this parameter is NULL, "open" is the default value.
        "open": Opens the file (the file can be an executable, a document file, or a folder).
        "edit": Opens the file for editing; only used when the file is not an executable.
        "runas": Uses elevated permissions (like "Run as administrator").

    lpFile: This is the name of the file to be executed, opened, or printed. This can be an executable, a document file, or a URL.

    lpParameters: If lpFile is an executable file, this parameter specifies the command-line parameters to be passed to the application. This is usually NULL or an empty string unless you're passing parameters to an executable.

    lpDirectory: This is the default directory for the action. If the action takes place on a file, this is typically the folder where the file is located. This can be NULL.

    nShowCmd: Flags that specify how an application window should be displayed if a new instance of the application is started. Common values are SW_HIDE, SW_MAXIMIZE, SW_MINIMIZE, SW_RESTORE, SW_SHOW, SW_SHOWDEFAULT, etc. If the file is not an executable, this parameter is often set to SW_SHOW.

Return Value

    If the function succeeds, the return value is greater than 32.
    If the function fails, the return value is an error code (less than or equal to 32).
