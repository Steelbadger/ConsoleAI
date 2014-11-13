#pragma once
#include <vector>
#include <Windows.h>
#include <string>

class Image;

class ConsoleScreenBuffer
{
public:
	ConsoleScreenBuffer();
	~ConsoleScreenBuffer();
	
	bool Initialise();

	void ClearBuffer();
	void FlipBuffers();
	void ResetTextCursor();

	bool Render(Image& img, COORD loc);

	void operator<<(const char* out);
	void operator<<(char out);

private:
	std::vector< std::vector<char> > bufferArray;
	std::string currentTextBuffer;
	HANDLE consoleHandle;
	COORD bufferSize;
	COORD cursorPos;
	static const COORD zero;
};