#include "imglib.hpp"

#include <vector>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[])
{   
	bool assisted = false;
	std::vector<std::string> args;
	std::string in_file = "";
	std::string out_file = "out.bmp";

	// make all arguments strings
	for (int i=0; i < argc; i++)
		args.push_back(argv[i]);

	// check arguments
	for (int i=0; i < args.size(); i++) {
		if (args[i] == "-a")
			assisted = true;
		else if (args[i] == "-i")
			in_file = args[++i];
		else if (args[i] == "-o")
			out_file = args[++i];
	}

	if (in_file == "")
		throw std::runtime_error("Must specify input file name using the -i command line flag.");

    transformGusset(in_file.c_str(), out_file.c_str(), assisted);

    return 0;
}