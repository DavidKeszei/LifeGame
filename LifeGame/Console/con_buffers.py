from enum import Enum

#States of the buffers in chars
_stateChars: list[str] = [ "█", "░"," "]

#Buffers state enum
class Buffer_State(Enum):
    LIVE = 0,
    DEAD = 1,
    OTHER = 2,

#Represent a "console buffer"
class ConsoleBuffer():
    _character: str #Actual character
    _bufferState: Buffer_State #Actual state of the buffer

    #Set a base constructor
    def __init__(self):
        self._character = "░"
        self._bufferState = Buffer_State.OTHER

    #Get current state of the console buffer
    def GetState(self) -> Buffer_State:
        return self._bufferState

    #Set the state & character of the buffer
    def SetState(self, state: Buffer_State) -> None:
        if state == Buffer_State.LIVE:
            self._character = _stateChars[0]
        elif state == Buffer_State.DEAD:
            self._character = _stateChars[2]
        else:
            self._character = _stateChars[1]

        self._bufferState = state

    #Get the current character
    def GetCharacter(self) -> str:
        return self._character


