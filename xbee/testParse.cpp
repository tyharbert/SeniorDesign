#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// I don't recommend using the std namespace in pppproduction code.
// For ease of reading here.
using namespace std;

// You could also take an existing vector as a parameter.
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

int main(int argc, char **argv) {
  string myCSV = "one,two,three,four";
  string line;
ifstream myfile("config.txt");
vector<string> sep;
if(myfile.is_open())
{
	while(getline(myfile,line))
		{
		  sep = split(line, ',');
		}
	myfile.close();
}


  // If using C++11 (which I recommend)
  /* for(string t : sep)
   *  cout << t << endl;
   */

  for(int i = 0; i < sep.size(); ++i)
    cout << sep[i] << endl;
}
