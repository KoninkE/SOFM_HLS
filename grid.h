#include <"neurons.h">
#include <vector.h>

class Grid {
	public:
		Grid(int gridLen, int gridWid, int inputSize, float learnRate, float lmda);
		void randomizeWeights(float lowBound, float highBound);
		void chooseBMU(std::vector<float> inputVect);
		void updateNeighborhood(std::vector<float> inputVect, int iterNum):
		
	private:
		std::vector<std::vector<Neuron>> sofm;
	
		float base_lr; // Base learning rate (it decays over every training epoch)
		float base_lmda; // Base lamda (it decays over every training epoch)
		int input_size;
		int grid_len;
		int grid_wid;
		int bmu_x;
		int bmu_y;
		float bmu_dist;
//		float min_dist;
};

Grid::Grid(int gridLen, int gridWid, int inputSize, float learnRate, float lmda) {
	this->grid_len = gridLen;
	this->grid_wid = gridWid;
	this->input_size = inputSize;
	this->base_lr = learnRate;
	this->grid_wid = gridWid;
	
	for(int i = 0; i < this->grid_len; i++) { //FIXME: Potentially make vector operation
		std::vector<Neuron> row;
		
		for(int j = 0; j < this->grid_wid; j++) {
			row.push_back(Neuron(this->input_size, j, i));
		}
		
		this->sofm.push_back(row);
	}
	
//	this->min_dist = std::sqrt(std::pow(this->grid_len, 2) + std::pow(this->grid_wid, 2));
}

void Grid::randomizeWeights(float lowBound, float highBound) {
	for(int i = 0; i < this->grid_len; i++) {
		for(int j = 0; j < this->grid_wid; j++) {
			this->sofm.at(i).at(j).initWeights(lowBound, highBound);
		}
	}
}

void Grid::chooseBMU(std::vector<float> inputVect) {
	float neuronDist;
	float minDist = 1000;
	
	for(int i = 0; i < this->grid_len; i++) { // FIXME: Replace with vector operation
		for(int j = 0; i < this->grid_wid; j++) {
			neuronDist = this->sofm.at(i).at(j).euclidDist(inputVect);
			
			// Assume the first neuron is the BMU so we have a value to compare for future neurons
			if(i == 0 and j == 0) {
				minDist = neuronDist;
				this->bmu_x = j;
				this->bmu_y = i;
			}
			
			else {
				if(neuronDist < minDist) {
					minDist = neuronDist;
					this->bmu_x = j;
					this->bmu_y = i;
				}
			}
		}
	}
	
	this->bmu_dist = minDist;
}

void Grid::updateNeighborhood(std::vector<float> inputVect, int iterNum) {
	int x1, x2, y1, y2;
	float dist;
	
	x1 = this->bmu_x;
	y1 = this->bmu_y;
	
	float learn_rate = this->base_lr * std::exp((-1 * iterNum) / 225);
	float lm = this->base_lmda * std::exp((-1 * iterNum) / 225);
	
	for(int i = 0; i < this->grid_len; i++) { // FIXME: Replace with vector operation
		for(int j = 0; i < this->grid_wid; j++) {
			x2 = this->sofm.at(i).at(j).getXCoord(); // This looks redundant: just use j
			y2 = this->sofm.at(i).at(j).getYCoord(); // This looks redundant: just use i
			dist = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
			
			this->sofm.at(i).at(j).updateWeights(inputVect, learn_rate, lm, dist);
		}
	}
	
}