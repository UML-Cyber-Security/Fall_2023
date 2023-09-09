Sub DownloadFile()
    Dim myURL As String
    myURL = "https://YourWebSite.com/?your_query_parameters" ' specify the URL of the file you want to download

    Dim WinHttpReq As Object
    Set WinHttpReq = CreateObject("Microsoft.XMLHTTP")
    WinHttpReq.Open "GET", myURL, False, "username", "password" ' specify any username and password if required
    WinHttpReq.send

    If WinHttpReq.Status = 200 Then ' check if the request was successful
        Dim oStream As Object
        Set oStream = CreateObject("ADODB.Stream")
        oStream.Open
        oStream.Type = 1
        oStream.Write WinHttpReq.responseBody
        oStream.SaveToFile "C:\file.csv", 2 ' specify the location and name of the file you want to save, 2 means overwrite existing file
        oStream.Close
    End If
End Sub

Sub DownloadFile()
    Dim objShell As Object
    Set objShell = CreateObject("WScript.Shell")
    
    Dim strCommand As String
    strCommand = "powershell -command ""Invoke-WebRequest -Uri 'http://example.com/file.zip' -OutFile 'C:\path\to\save\location\file.zip'"""
    
    objShell.Run strCommand
    
    Set objShell = Nothing
End Sub

