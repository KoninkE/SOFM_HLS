#include <vector.h>

class LFSR {
	public:
		LFSR(std::vector<bool> tapProg, std::vector<bool> initialVal);
		
	private:
		std::vector<bool> values;
		std::vector<bool> taps;
};

LFSR::LFSR(std::vector<bool> tapProg, std::vector<bool> initialVal) {
	this->values = initialVal;
	this->taps = tapProg;
}