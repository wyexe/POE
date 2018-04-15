#coding:utf-8
import WeGameAttribute;
import PicMatch;
import time;
import ConfigParser;
import MouseAction
import autopy


def WaitToEnableCheat(TimeoutSec):
    StartTick = time.time();
    while IsExistCheat() == 0:
        time.sleep(1000);
        if((int)(time.time() - StartTick) >= TimeoutSec):
            print("WaitToEnableCheat Timeout:{0}".format(TimeoutSec));
            return 0;
    
    
def EchoWeGameLauncher(EnvConfig):
    if(PicMatch.IsNotExistQuickLogin()[0] != -1):
        print("NotExistQuickLogin in Lanuncher");
        return 0;

    if(PicMatch.IsCheckingEnv()[0] != -1):
        print("Env Checking ...");
        return 1;

    loc = PicMatch.IsExistQuickLogin();
    if(loc[0] != -1):
        # 点击头像快速登陆
        MouseAction.EmulateMouseMove(loc[0] + 76, loc[1] + 73)
        MouseAction.EmulateMouseClick();
        pass;

    return 1;



def EchoWeGame(EnvConfig):
    if(WeGame.IsExistWeGame() == False):
        print("UnExist Game Process when Echo WeGame");
        return False;
    

    loc = PicMatch.IsNotWeGameMainPage();
    if(loc[0] != -1):
         print("Click Main Page");
         MouseAction.EmulateMouseMove(loc[0] + 5, loc[1] + 5)
         MouseAction.EmulateMouseClick();
         time.sleep(3);
         return True;

    
    loc = PicMatch.IsExistWeGameList();
    if(loc[0] != -1):
         MouseAction.EmulateMouseMove(loc[0] + 3, loc[1] + 10)
         MouseAction.EmulateMouseClick();
         time.sleep(3);
         return True;
    if(PicMatch.IsInWeGameMainUi()[0] != -1):
        loc = PicMatch.IsExistRunGameButton();
        if(loc[0] == -1):
            PathOfExileOnWeGameLoc = PicMatch.IsExistPathOfExileOnWeGame();
            if(PathOfExileOnWeGameLoc[0] != -1):
                print("Game Menu List");
                MouseAction.EmulateMouseMove(loc[0] + 60, loc[1] + 20)
                MouseAction.EmulateMouseClick();
                time.sleep(3);
                return True;

        RunAsx86Loc = PicMatch.IsExistRunAs32();
        if (RunAsx86Loc[0] != -1):
            print("Click Run as x86");
            MouseAction.EmulateMouseMove(RunAsx86Loc[0] + 40, RunAsx86Loc[1] + 20)
            autopy.alert.alert("Click Run Game");
            MouseAction.EmulateMouseClick();
            time.sleep(3);
            return True;
      
        if(loc[0] != -1):
            print("Click Run Game Button");
            MouseAction.EmulateMouseMove(loc[0] + 40, loc[1] + 20)
            MouseAction.EmulateMouseClick();
            time.sleep(3);
            return True;
        
    
    return True;

def InitializeLauncherVar(EnvConfig):
    WeGameAttribute.WorkDir = EnvVar["WorkDir"];
    PicMatch.WorkDir = EnvVar["WorkDir"];

    if(WeGameAttribute.IsExistConsole() == 1):
        print("Already Exist Console...");
        return False;

    # Create Console Instance Mutex ...
    WeGameAttribute.CreateConsoleMutex();
    return True;

def EchoWeGameLogin(EnvConfig):
    if(not InitializeLauncherVar()):
        return False;

    StartTick = time.time();
    RestartWeGameTimeout = EnvConfig["EnvConfig"];
    while True:
        # 已经开启作弊器
        if(WeGame.IsExistCheat()):
            print("Already Exist Cheat ...");
            break;

        # 游戏进程已经存在
        if(WeGame.IsExistGame()):
            print("Exist game process ... ");
            return WaitToEnableCheat(EnvConfig["WaitToEnableCheatTimeoutSec"]);

        # WeGame的主UI
        if(WeGame.IsExistWeGame() and WeGame.IsExistWeGameLauncher() == False):
            WeGame.ActiveWeGame();
            EchoWeGame(EnvConfig);
            continue;

        # 还没登陆!
        if(WeGame.IsExistWeGameLauncher()):
            print("EchoWeGameLauncher");
            WeGame.ActiveWeGame();
            if(EchoWeGameLauncher(EnvConfig) == 0):
                print("EchoWeGameLauncher = 0");
                return 0;

        else:
            print("Run WeGame...");
            WeGame.RunWeGame(EnvConfig["WeGameDir"])
       
        time.sleep(1);
        if((int)(time.time() - StartTick) >= RestartWeGameTimeout):
            print("WeGame Login Timeout[{0}]".format(RestartWeGameTimeout));
            WeGame.TerminateWeGame();
            StartTick = time.time();

    return 1;