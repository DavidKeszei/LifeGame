from ctypes import cdll
from datetime import datetime 
from random import randint
import time

buffers = cdll.LoadLibrary(r"C:\Users\David\source\repos\LifeGame\x64\Release\Buffers.dll")

dead = " "
live =  "█"
other = "░"

sandbox = [[ other for y in range(0, 40)] for x in range(0, 80)]
index = 0

def Start():

    for x in range(0, 80):
        for y in range(0,40):
            buffers.SendWithPos(sandbox[x][y], x, y)

    buffers.SendWithPos(live, 40, 20)
    sandbox[40][20] = live

    buffers.SendWithPos(live, 40, 21)
    sandbox[40][21] = live

    buffers.SendWithPos(live, 41, 20)
    sandbox[41][20] = live

    buffers.SendWithPos(live, 41, 21)
    sandbox[41][21] = live


def Draw():
    for x in range(0, 80):
        for y in range(0,40):
            buffers.SendWithPos(sandbox[x][y], x, y)

    for x in range(1, 79):
        for y in range(1, 39):
            lives = 0

            if sandbox[x - 1][y] == live:
                lives = lives + 1

            if sandbox[x + 1][y] == live:
                lives = lives + 1

            if sandbox[x][y - 1] == live:
                lives = lives + 1

            if sandbox[x][y + 1] == live:
                lives = lives + 1

            if sandbox[x][y] == other:
                if lives == 2 or lives == 3:
                    sandbox[x][y] = live
                    continue;

            if sandbox[x][y] == live:
                if lives < 2 or lives > 3:
                    sandbox[x][y] = dead
                    continue;

            if sandbox[x][y] == dead:
                if lives == 2 or lives == 3:
                    sandbox[x][y] = live
                    continue;
                else:
                    sandbox[x][y] = other


buffers.Init(80, 40)

Start()

while True:
    start = datetime.now()

    Draw()
    buffers.DrawFPS(datetime.now().microsecond - start.microsecond)