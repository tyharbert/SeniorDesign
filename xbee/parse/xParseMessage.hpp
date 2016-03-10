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
	int* readCoordinate();
	void clearCoordinate();
	vector<string> split(string str, char delimiter);

};

vector<string> split(string str, char delimiter){
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}


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


int* readCoordinate(){

	int coords [12];
	ifstream myfile("config.txt");
	string line;
	vector<string> sep;
	if(myfile.is_open())
	{
		int count = 0;
		while(getline(myfile,line))
		{
		  sep = split(line, ',');
		  count++;
		  int j = 0;
		  for(int k=0; k<6; k++)
		  {
			j=k;
			if(count == 2)
			{
				j = k+6;
			}
			std::string tempStr = sep.at(k);
			coords[j] = atoi(tempStr.c_str());
//			std::cout << coords[j];

		}
//		atoi(myString.c_str());
		cout << "\n";
		}
		myfile.close();
	}

	return coords;

}
