'Xshell vb script
'
Sub Main

xsh.Screen.Synchronous = true

Do
While true

xsh.Screen.Synchronous = true

xsh.Session.Sleep 10000

'xsh.Screen.WaitForString "Username: "

xsh.Screen.Send "admin"
xsh.Screen.Send VbCr

xsh.Session.Sleep 100
xsh.Screen.Send "admin"
xsh.Screen.Send VbCr

xsh.Screen.Send "show cell 1 card-information"
xsh.Screen.Send VbCr
xsh.Session.Sleep 100
xsh.Screen.Send "show cell 1 statistics-information"
xsh.Screen.Send VbCr
xsh.Session.Sleep 100

xsh.Screen.Send "reboot"
xsh.Screen.Send VbCr
xsh.Session.Sleep 100
xsh.Screen.Send "y"
xsh.Screen.Send VbCr
xsh.Session.Sleep 100000

Wend
Loop

End Sub
