#coding:utf-8
import win32com.client
import wmi
import time
import ctypes;

# global variable
WorkDir = ""

def GetProcArray(ProcName):
     w = wmi.WMI();
     return w.Win32_process(name = ProcName);

# 是否运行了WeGame的主进程
def IsExistWeGame():
    return len(GetProcArray("tgp_daemon.exe")) != 0

# WeGame 的登录器
def IsExistWeGameLauncher():
    return len(GetProcArray("launcher.exe")) != 0

# 是否有游戏主进程
def IsExistGame():
     return len(GetProcArray("PathOfExile.exe")) != 0

# 是否开启了作弊
def IsExistCheat():
    return ctypes.cdll.LoadLibrary(WorkDir + "DLL\\CppInterface.dll").ExistCheatMutex();

# 是否已经开启了控制台了
def IsExistConsole():
    return ctypes.cdll.LoadLibrary(WorkDir + "DLL\\CppInterface.dll").ExistInstanceMutex()

# 创建控制台互斥
def CreateConsoleMutex():
    ctypes.cdll.LoadLibrary(WorkDir + "DLL\\CppInterface.dll").CreateInstanceMutex()

# 前置显示
def ActiveWeGame():
    ctypes.cdll.LoadLibrary(WorkDir + "DLL\\CppInterface.dll").ShowWeGame()

# 结束WeGame进程
def TerminateWeGame():
    while(IsExistWeGame()):
         ProcArray = GetProcArray("tgp_daemon.exe");
         if(len(ProcArray) > 0):
            ProcArray[0].Terminate();
            time.sleep(3); # 3 * 1000 ms
            continue;

         ProcArray = GetProcArray("launcher.exe");
         if(len(ProcArray) > 0):
            ProcArray[0].Terminate();
            time.sleep(3); # 3 * 1000 ms
            continue;

# 启动WeGame
def RunWeGame(WeGamePath):
    c = wmi.WMI();
    v = c.Win32_Process.Create(CommandLine=WeGamePath)
    # administrator Token...
    return v[1];