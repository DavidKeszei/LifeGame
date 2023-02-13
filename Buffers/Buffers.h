#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

class Buffers {
	static COORD _actualCoord;
	static COORD _consoleSize;

	public:
		static void Init(int sizeX, int sizeY);
		static void Send(WCHAR value);
		static void Send(WCHAR value, COORD pos);
		static void IncreasePositionX();
		static void IncreasePositionY();
		static void DrawFPS(int milliseconds);
		static void SetBack();
};

DLL_EXPORT void Init(int sizeX, int sizeY) {
	Buffers::Init(sizeX, sizeY);
}

DLL_EXPORT void Send(std::wstring value) {
	Buffers::Send(value[0]);
}

DLL_EXPORT void SendWithPos(std::wstring value, int x, int y) {
	COORD pos = { x, y };
	Buffers::Send(value[0], pos);
}

DLL_EXPORT void IncreasePositionX() {
	Buffers::IncreasePositionX();
}

DLL_EXPORT void IncreasePositionY() {
	Buffers::IncreasePositionY();
}

DLL_EXPORT void DrawFPS(int milliseconds) {
	Buffers::DrawFPS(milliseconds);
}

DLL_EXPORT void SetBack() {
	Buffers::SetBack();
}