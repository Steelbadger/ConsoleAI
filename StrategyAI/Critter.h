#pragma once


class Critter
{
public:
	Critter();
	~Critter();

	void Initialise();

	void Update();
	void Draw();

	void Feed();
	void Pet();
private:

	int happiness;
	int hunger;



};