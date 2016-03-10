#include "xParseMessage.hpp"

int main(){
	clearCoordinate();
	writeCoordinate(6,5,4,3,2,1);
	writeCoordinate(1,2,3,4,5,6);
	int* p;
	p = readCoordinate();
	cout << "read:";
	for(int i=0; i < 12; i++)
	{
		cout << *(p + i);
	}
//	std::cout << "\n Test";
	return 0;
}
