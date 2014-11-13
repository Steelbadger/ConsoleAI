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
		buff.ClearBuffer();
		if (_kbhit()) {
			input = _getch();
			buff << input;
			if (input == '/n')
				buff.ResetTextCursor();
		}
		if (input == 'm') {
			buff.Render(img, nope);
			input = 0;
		}
		buff.FlipBuffers();
	}


};

