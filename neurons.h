#include <vector.h>
#include <lfsr.h>

class Neuron {
	public:
		Neuron(int numWeights, int xCoord, int yCoord);
		void initWeights(float lowBound, float highBound);
		float euclidDist(std::vector<float> inputVect);
		void updateWeights(std::vector<float>inputVect, float learn_rate, float lmda, float dist);
		
		std::vector<float> getWeights();
		int getXCoord(); //FIXME: Might not need this (see updateNeighborhood function for Grid)
		int getYCoord(); //FIXME: Might not need this (see updateNeighborhood function for Grid)
		
	private:
		int	num_weights;
		int x_coord;
		int y_coord;
		std::vector<float> weights;
};

Neuron::Neuron(int numWeights, int xCoord, int yCoord) {
	this->num_weights = numWeights;
	this->x_coord = xCoord;
	this->y_coord = yCoord;
	
}

void Neuron::initWeights(float lowBound, float highBound) {
	float temp;
	
	for(int i = 0; i < this->num_weights; i++){ // FIXME: Replace with vector operation
		temp = (rand() % (highBound - lowBound + 1)) + lowBound;
		weights.push_back(temp);
	}
}

float Neuron::euclidDist(std::vector<float> inputVect) {
	float mySum = 0;
	
	for(int i = 0; i < this->num_weights; i++) { //FIXME: Replace with vector operation
		mySum += std::pow((inputVect.at(i) - this->weights.at(i), 2));
	}
	
	return std::sqrt(mySum);
}

void Neuron::updateWeights(std::vector<float>inputVect, float learn_rate, float lmda, float dist) {
	float theta = std::exp(-1 * (std::pow(dist, 2) /(2 * std::pow(lmda, 2))));
	
	for(int i = 0; i < this->numWeights; i++) { //FIXME: Replace with vector operation
		this->weights.at(i) += theta * learn_rate * (inputVect.at(i) - this->weights.at(i));
	}
}

int Neuron::getXCoord() {
	return this->x_coord;
}

int Neuron::getYCoord() {
	return this->y_coord;
}

std::vector<float> Neuron::getWeights() {
	return this->weights;
}
