from ctypes import cdll
from datetime import datetime 
import time
from Console.con_buffers import ConsoleBuffer, Buffer_State

#Load the C++ console library
buffers = cdll.LoadLibrary(r"C:\Users\David\source\repos\LifeGame\x64\Release\ConsoleBufferDrawer.dll")

#Sandbox of the cells
sandbox = [[ ConsoleBuffer() for y in range(0, 40)] for x in range(0, 80)]

#Update() - Update the screen each generetion
def Update():

    for x in range(0, 80):
        for y in range(0,40):
            buffers.SendWithPos(sandbox[x][y].GetCharacter(), x, y)

#Start() - Set up the first draw
def Start():
    #Draw the empty space
    Update()

    #Set up the first generation
    sandbox[39][20].SetState(Buffer_State.LIVE)
    buffers.SendWithPos(sandbox[39][20].GetCharacter(), 39, 20)

    sandbox[40][19].SetState(Buffer_State.LIVE)
    buffers.SendWithPos(sandbox[40][20].GetCharacter(), 40, 19)

    sandbox[40][20].SetState(Buffer_State.LIVE)
    buffers.SendWithPos(sandbox[40][20].GetCharacter(), 40, 20)

    sandbox[40][21].SetState(Buffer_State.LIVE)
    buffers.SendWithPos(sandbox[40][20].GetCharacter(), 40, 21)

    sandbox[41][20].SetState(Buffer_State.LIVE)
    buffers.SendWithPos(sandbox[39][20].GetCharacter(), 39, 20)

#PopulationCheck() - Update the current generation
def PopulationCheck():
    #Get the global variable
    global sandbox

    #Init a new matrix for the new generation
    result_sandbox = [[ ConsoleBuffer() for y in range(0, 40)] for x in range(0, 80)]

    for x in range(1, 79):
        for y in range(1, 39):
            lives: int = 0

            #If the actual cell is alive, don't count it
            if sandbox[x][y].GetState() == Buffer_State.LIVE:
                lives = -1

            #Check the neighbors based on the rules
            for i in range(x - 1, x + 2):
                for j in range(y - 1, y + 2):

                    #Increase the neighbors count
                    if sandbox[i][j].GetState() == Buffer_State.LIVE:
                        lives += 1
                    
            #Check, which rules valid in this case
            if sandbox[x][y].GetState() == Buffer_State.LIVE:
                if lives < 2 or lives > 3:
                    result_sandbox[x][y].SetState(Buffer_State.DEAD)
                    continue;
                else:
                    result_sandbox[x][y].SetState(Buffer_State.LIVE)
                    continue

            if sandbox[x][y].GetState() == Buffer_State.DEAD or sandbox[x][y].GetState() == Buffer_State.OTHER:
                if lives == 3:
                    result_sandbox[x][y].SetState(Buffer_State.LIVE)
                    continue;
                else:
                    result_sandbox[x][y].SetState(Buffer_State.OTHER)

    #Update the generation
    sandbox = result_sandbox


#Set up the C++ library & play area
buffers.Init(80, 40)

#Ask the max. fps
wait_time = 1 / float(input("FPS Limit: "))
pre_frame_time = 0

#Draw the first generation
Start()

#Start the "game" loop
while True:
    new_frame_time = time.time()

    Update() #Update the screen
    PopulationCheck() #Update the generation
    end = 1 / (new_frame_time - pre_frame_time)

    time.sleep(wait_time) #Wait some time (~8ms == 120 FPS)

    pre_frame_time = new_frame_time

    buffers.DrawFPS(int(end))