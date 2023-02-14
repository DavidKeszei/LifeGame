#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

class Buffers {
	public:
		static void Init(int sizeX, int sizeY);
		static void Send(WCHAR value, COORD pos);
		static void DrawFPS(int milliseconds);
};

DLL_EXPORT void Init(int sizeX, int sizeY) {
	Buffers::Init(sizeX, sizeY);
}

DLL_EXPORT void SendWithPos(std::wstring value, int x, int y) {
	COORD pos = { x, y };
	Buffers::Send(value[0], pos);
}

DLL_EXPORT void DrawFPS(int milliseconds) {
	Buffers::DrawFPS(milliseconds);
}