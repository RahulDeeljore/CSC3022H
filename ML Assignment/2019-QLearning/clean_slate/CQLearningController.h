#pragma once
#include "cdisccontroller.h"
#include "CParams.h"
#include "CDiscCollisionObject.h"
#include <cmath>

typedef unsigned int uint;
class CQLearningController :
	public CDiscController
{
private:
	uint _grid_size_x;
	uint _grid_size_y;

	double learningRate = 0.1;	
	double discountFactor = 0.5;

	// Sweepers Q Tables
	std::vector<std::vector<std::vector<double>>> QTables;

public:
	CQLearningController(HWND hwndMain);
	virtual void InitializeLearningAlgorithm(void);

	double R(uint x, uint y, uint sweeper_no);

	virtual bool Update(void);

	virtual int getMaxAction(std::vector<double> actions);

	virtual double getMaxActionValue(std::vector<double> actions);

	virtual ~CQLearningController(void);
};

