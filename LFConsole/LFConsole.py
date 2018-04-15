#coding:utf-8
from Launcher.GameLauncher import EchoWeGameLogin

# 依赖项 autopy,cv2,wmi,pywin32  
def GetEnvVar():
    configer = ConfigParser.ConfigParser();
    configer.read("C:\\CLLF\\Console.ini");
    WorkDir = configer.get("Config","WorkDir");
    return { \
            "WorkDir" : configer.get("Config","WorkDir"), \
            "WaitToEnableCheatTimeoutSec" : configer.get("Config","WaitToEnableCheatTimeoutSec"), \
            "RestartWeGameTimeout" : configer.get("Config","RestartWeGameTimeout"), \
            "WeGameDir" : configer.get("Config","WeGameDir"), \
            }

def main():
    EnvVar = GetEnvVar();

    # set WorkDir
    if(EchoWeGameLogin(EnvVar)):
        pass; 
    
    print("End!!!");

if __name__ == "__main__":
    main();
