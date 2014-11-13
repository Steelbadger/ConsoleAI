#include "Image.h"


Image::Image()
{

}

Image::~Image()
{
}

void Image::CreateImageFrom2DArray(char* loc, int x, int y)
{
	imageArray.resize(y, std::vector<char>(x,32));
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			imageArray[i][j] = loc[j*x+i];
		}
	}

}

std::vector< std::vector<char> > Image::GetImage()
{
	return imageArray;
}
