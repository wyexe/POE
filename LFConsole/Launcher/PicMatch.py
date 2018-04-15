#coding:utf-8
import autopy
import cv2

# global variable
WorkDir = ""

def screenshot():
    autopy.bitmap.capture_screen().save(WorkDir + "capture.png");
    return cv2.imread(WorkDir + "capture.png");

def Match(PicName):
    res = cv2.matchTemplate(screenshot(), cv2.imread(WorkDir + "MatchPic\\" + PicName), cv2.TM_SQDIFF);
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res);
   
    if(min_val < 20 * 10000 and min_val >= -100):
        return  [min_loc[0],min_loc[1],min_val];

    return [-1,-1, min_val];

# WeGame 检查环境
def IsCheckingEnv():
    return Match("CheckingEnv.png");

# WeGame 快速登陆
def IsExistQuickLogin():
     return Match("ExistQuickLogin.png");

# WeGame 没有快速登陆
def IsNotExistQuickLogin():
     return Match("NotExistQuickLogin.png");

# 在WeGame的登陆界面
def IsInWeGameLoginUi():
     return Match("InWeGameLoginUi.png");

# 在WeGame的主界面
def IsInWeGameMainUi():
     return Match("InWeGameMainUi.png");

# 没进主页
def IsNotWeGameMainPage():
     return Match("WeGameMainPage.png");

# 选择游戏
def IsExistWeGameList():
     return Match("WeGameList.png");

# 可以点击开始游戏
def IsExistRunGameButton():
     return Match("ExistRunGameButton.png");

# 还没选择游戏
def IsExistPathOfExileOnWeGame():
     return Match("ExistPathOfExileOnWeGame.png");

# 选择x86
def IsExistRunAs32():
     return Match("ExistRunAs32.png");
