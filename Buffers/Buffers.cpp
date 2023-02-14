#include "pch.h"
#include "Buffers.h"
#include <iostream>

COORD _actualCoord = { 0, 0 };
COORD _consoleSize = { 0, 0 };
COORD center = { 0, 3 };
RECT playArea = { 0, 0, 0, 0 };

void Buffers::Init(int sizeX, int sizeY) {
	//Maximaze the console window
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	//Set the cursor to invisible
	CONSOLE_CURSOR_INFO _cursorInfo = { 1 };

	//Get current console window output stream
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get inforation of the console buffer matrix
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

	//Set the cursor properties
	SetConsoleCursorInfo(_out, &_cursorInfo);

	//Get the console buffer informations
	if (!GetConsoleScreenBufferInfo(_out, &bufferInfo)) {
		printf("Something wrong...\n Quit...\n (Exit code: %i) ", GetLastError());
		return;
	}

	//Sandbox size
	_consoleSize.X = sizeX;
	_consoleSize.Y = sizeY;

	//Center of the buffer matrix
	center.X = bufferInfo.dwSize.X / 2;

	//Calc. the start position for drawing
	_actualCoord.X = center.X - sizeX / 2;
	_actualCoord.Y = center.Y;

	//Calc the sandbox start & end position
	playArea.left = center.X - sizeX / 2;
	playArea.right = center.X + sizeX / 2;
	playArea.top = center.Y;
	playArea.bottom = center.Y + sizeY;
}

void Buffers::Send(WCHAR value, COORD pos) {
	//Get current console window output stream
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);

	//[Optional] Get the writted character count
	DWORD writted = 0;

	//Current buffer position
	pos.X += playArea.left;
	pos.Y += playArea.top;

	//Draw the buffer to the screen
	if (!FillConsoleOutputCharacter(_out, value, 1, pos, &writted)) {
		printf("Something wrong...\n Quit...\n (Exit code: %i) ", GetLastError());
		return;
	}
}

void Buffers::DrawFPS(int milliseconds) {
	//Get current console window output stream
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD start = { 0, 0 };
	DWORD writted = 0;

	for (size_t i = 0; i < center.X *2; i++) {
		FillConsoleOutputCharacter(_out, ' ', 1, start, &writted);
		start.X++;
	}

	std::wstring frameText = L"PLAY AREA: " + std::to_wstring(playArea.right - playArea.left) + L"x" + std::to_wstring(playArea.bottom - playArea.top);
	frameText += L" | DRAW TIME: " + std::to_wstring(milliseconds) + L"ms";

	start.X = center.X - frameText.size() / 2;

	for (const WCHAR &character : frameText) {
		FillConsoleOutputCharacter(_out, character, 1, start, &writted);
		start.X++;
	}
}
