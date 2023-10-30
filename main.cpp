#include <stdio.h>
#include <neurons.h>
#include <grid.h>
#include <vector>

int main(std::vector<std::vector<float>> inputVect, int gridLen, int gridWid, float lr, float lmda)
{
	mySOFM = Grid(gridLen, gridWid, std::inputVect.at(0)::size(), lr, lmda);
	mySOFM.randomizeWeights(float lowBound, float highBound)
	
	for(int i = 0; i < std::inputVect::size(); i++) {
		mySOFM.chooseBMU(inputVect.at(i));
		mySOFM.updateNeighborhood(inputVect.at(i), i);
	}
}
