#include <Windows.h>
#include <iostream>
#include <conio.h>

#include "ConsoleScreenBuffer.h"
#include "Image.h"


char MYIMG[35] =		{' ', ' ', ' ', '.', ' ', ' ', ' ',
						 ' ', ' ', ' ', '|', ' ', ' ', ' ',
						 '+','-','-','-','-','-','+',
						 '|','.',' ','o','.',' ','|',
						 '+', '-', '-', '-', '-', '-', '+'};

int main()
{
	char input = 0;

	ConsoleScreenBuffer buff;
	Image img;
	img.CreateImageFrom2DArray(MYIMG, 7, 5);
	buff.Initialise();

	COORD nope = {10,5};

	while(input != 27) {
		if (_kbhit()) {
			input = _getch();
			buff << input;
			if (input == '\r')
				buff.ResetTextCursor();
		}
		if (input == '#') {
			buff.Render(img, nope);
			input = 0;
		}
		if (buff.BufferChange()) {
			buff.FlipBuffers();
		}
	}


};

