#pragma once
#include <vector>

class Image
{
public:
	Image();
	~Image();

	void CreateImageFrom2DArray(char* loc, int x, int y);

	std::vector< std::vector<char> > GetImage();

private:
	std::vector< std::vector<char> > imageArray;	
};