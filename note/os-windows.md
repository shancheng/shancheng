The manifest file
http://mariusbancila.ro/blog/2010/03/24/visual-studio-2010-changes-for-vc-part-5/

# Core dump

"C:\Program Files\Debugging Tools For Windows (x64)\ntsd" -iaec "-c """.logopen /t C:\Corefiles\jit.log; !analyze -v; ~*k250; lmv; .dump /mA /u C:\Corefiles\jit.dmp; q""" -g"

https://blogs.msdn.microsoft.com/pfedev/2008/09/25/all-the-ways-to-capture-a-dump/

https://docs.microsoft.com/en-us/windows/win32/wer/collecting-user-mode-dumps
