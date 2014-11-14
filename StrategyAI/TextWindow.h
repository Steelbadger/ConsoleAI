#pragma once

#include <Windows.h>

//╔══════╗
//║ Help ║
//╚══════╝
//┌──────┐
//│ Help │
//└──────┘


class TextWindow
{
public:
	enum BorderType {NONE, SINGLE, DOUBLE};

	TextWindow();
	~TextWindow();

	void Render();
	void SetLocation(int x, int y);
	void SetSize(int x, int y);
	void SetMaxSize(int x, int y);
	void SetDynamic(bool dyn);
	void SetBorder(BorderType t);

private:
	COORD position;
	COORD size;
	COORD maxSize;
	bool dynamic;
	BorderType borders;

	char doubleBorder[6] = { '╔', '╗', '╝', '╚', '═', '║' };
	char singleBorder[6] = { '┌', '┐', '┘', '└', '─', '│' };
	char noBorder[6] = {' '};

	char* border;
};