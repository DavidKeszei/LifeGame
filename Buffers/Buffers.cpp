#include "pch.h"
#include "Buffers.h"
#include <iostream>

COORD Buffers::_actualCoord = { 0, 0 };
COORD Buffers::_consoleSize = { 0, 0 };
COORD center = { 0, 3 };
RECT playArea = { 0, 0, 0, 0 };

void Buffers::Init(int sizeX, int sizeY) {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	CONSOLE_CURSOR_INFO _cursorInfo = { 1 };
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

	SetConsoleCursorInfo(_out, &_cursorInfo);

	if (!GetConsoleScreenBufferInfo(_out, &bufferInfo)) {
		printf("Something wrong...\n Quit...\n (Exit code: %i) ", GetLastError());
		return;
	}

	_consoleSize.X = sizeX;
	_consoleSize.Y = sizeY;

	center.X = bufferInfo.dwSize.X / 2;

	Buffers::_actualCoord.X = center.X - sizeX / 2;
	Buffers::_actualCoord.Y = center.Y;

	playArea.left = center.X - sizeX / 2;
	playArea.right = center.X + sizeX / 2;
	playArea.top = center.Y;
	playArea.bottom = center.Y + sizeY;
}

void Buffers::Send(WCHAR value) {
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD writted = 0;

	if (!FillConsoleOutputCharacter(_out, value, 1, Buffers::_actualCoord, &writted)) {
		printf("Something wrong...\n Quit...\n (Exit code: %i) ", GetLastError());
		return;
	}
}

void Buffers::Send(WCHAR value, COORD pos) {
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD writted = 0;

	pos.X += playArea.left;
	pos.Y += playArea.top;

	if (!FillConsoleOutputCharacter(_out, value, 1, pos, &writted)) {
		printf("Something wrong...\n Quit...\n (Exit code: %i) ", GetLastError());
		return;
	}
}

void Buffers::IncreasePositionX() {
	Buffers::_actualCoord.X++;
}

void Buffers::IncreasePositionY() {
	Buffers::_actualCoord.Y++;
}

void Buffers::SetBack() {
	Buffers::_actualCoord.X = center.X - Buffers::_consoleSize.X / 2;
	Buffers::_actualCoord.Y = center.Y;
}

void Buffers::DrawFPS(int milliseconds) {
	HANDLE _out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD start = { 0, 0 };
	DWORD writted = 0;

	for (size_t i = 0; i < center.X *2; i++) {
		FillConsoleOutputCharacter(_out, ' ', 1, start, &writted);
		start.X++;
	}

	std::wstring frameText = L"PLAY AREA: " + std::to_wstring(playArea.right - playArea.left) + L"x" + std::to_wstring(playArea.bottom - playArea.top);
	frameText += L" | DRAW TIME: " + std::to_wstring(milliseconds / (float)1000) + L"ms";

	start.X = center.X - frameText.size() / 2;

	for (const WCHAR &character : frameText) {
		FillConsoleOutputCharacter(_out, character, 1, start, &writted);
		start.X++;
	}
}
