#include <fstream>
#include <iostream>
#include <string>
namespace FileSystem{
	void ParseFile(std::string path, int& w, int &h, int &flag)
	{
		std::ifstream rSettings(path);
		// Begin Parsing
		std::string temp;
		if (rSettings.is_open()){
				rSettings >> temp;
				rSettings >> w;
				rSettings >> temp;
				rSettings >> h;
				rSettings >> temp;
				rSettings >> flag;
		}
		rSettings.close();
	}
};