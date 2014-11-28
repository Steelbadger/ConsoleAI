#pragma once

class FuzzyInputInterface
{
public:
	FuzzyInputInterface(){};
	virtual ~FuzzyInputInterface(){};

	virtual float operator()(float in) = 0;
	virtual float Evaluate(float in) = 0;
};
