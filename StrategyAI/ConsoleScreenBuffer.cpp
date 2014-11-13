#include "ConsoleScreenBuffer.h"
#include <iostream>
#include "Image.h"

const COORD ConsoleScreenBuffer::zero = {0,0};


ConsoleScreenBuffer::ConsoleScreenBuffer()
{
}

ConsoleScreenBuffer::~ConsoleScreenBuffer()
{

}

bool ConsoleScreenBuffer::Initialise()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(consoleHandle,&info);

	bufferSize = info.dwMaximumWindowSize;
	bufferSize.X = info.srWindow.Right;
	bufferSize.Y = info.srWindow.Bottom;
	bufferArray.resize(bufferSize.Y, std::vector<char>(bufferSize.X, 32));

	CONSOLE_CURSOR_INFO cursor = {0};
	GetConsoleCursorInfo(consoleHandle, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursor);
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);

	return true;
}

void ConsoleScreenBuffer::ClearBuffer()
{
	for (auto i = bufferArray.begin(); i != bufferArray.end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			(*j) = 32;
		}
	}

	for (int i = 0; i < currentTextBuffer.length(); ++i){
		bufferArray[(i) / bufferSize.Y][(i) % bufferSize.X] = currentTextBuffer[i];
	}
}

void ConsoleScreenBuffer::FlipBuffers()
{
	SetConsoleCursorPosition(consoleHandle,zero);
	for (int i = 0; i < bufferSize.Y; i++) {
		for (int j = 0; j < bufferSize.X; j++){
			std::cout << bufferArray[i][j];
		}
		std::cout << std::endl;
	}
}

void ConsoleScreenBuffer::ResetTextCursor()
{
	cursorPos = zero;
	currentTextBuffer = std::string();
}

bool ConsoleScreenBuffer::Render(Image& img, COORD loc)
{
	auto arr = img.GetImage();

	for (int i = 0; i != arr.size(); i++) {
		for (int j = 0; j != arr[i].size(); j++) {
			bufferArray[loc.Y+j][loc.X+i] = arr[i][j];
		}
	}

	return true;
}

void ConsoleScreenBuffer::operator<<(const char* out)
{
	int base = cursorPos.Y*bufferSize.X + cursorPos.X;

	for (int i = 0; i < strlen(out); ++i){
		bufferArray[(base+i)/bufferSize.Y][(base+i) % bufferSize.X] = out[i];
	}
	cursorPos.X = (base + strlen(out)) % bufferSize.X;
	cursorPos.Y = (base + strlen(out)) / bufferSize.Y;
	currentTextBuffer.append(out);

}

void ConsoleScreenBuffer::operator<<(char out)
{
	int base = cursorPos.Y*bufferSize.X + cursorPos.X;

	bufferArray[(base) / bufferSize.Y][(base) % bufferSize.X] = out;

	cursorPos.X = (base + 1) % bufferSize.X;
	cursorPos.Y = (base + 1) / bufferSize.Y;
	currentTextBuffer += out;
}