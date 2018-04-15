#coding:utf-8
import autopy

def EmulateMouseMove(x,y):
    autopy.mouse.smooth_move(x, y);

def EmulateMouseClick():
    autopy.mouse.click();
