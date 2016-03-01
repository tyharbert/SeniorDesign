#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class parser{

public:
	void writeCoordinate(int pan1, int pan2, int pan3, int tilt1, int tilt2, int tilt3);
	int[] readCoordinate(int num);
	void clearCoordinate();


};

void writeCoordinate(int pan1, int pan2, int pan3, int tilt1, int tilt2, int tilt3)
{
	std::string p1 = std::to_string(pan1);
	std::string p2 = std::to_string(pan2);
	std::string p3 = std::to_string(pan3);
	std::string t1 = std::to_string(tilt1);
	std::string t2 = std::to_string(tilt2);
	std::string t3 = std::to_string(tilt3);
	std::string coord = p1 + ',' + p2 + ',' + p3 + ',' + t1 + ',' + t2 + ',' + t3 + '\n';

	  ofstream myfile ("config.txt", std::ios::app);
	  if (myfile.is_open())
	  {
	    myfile << coord;
	    myfile.close();
	  }
	}

void clearCoordinate(){
	std::ofstream ofs;
	ofs.open("config.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}


int[] readCoordinate(int num){





}
