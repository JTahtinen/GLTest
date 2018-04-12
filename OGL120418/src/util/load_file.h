#pragma once
#include <string>
#include <fstream>
#include <iostream>

inline std::string load_text_file(const std::string& filename)
{
	std::string output;
	std::string line;

	std::ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			output.append(line + "\n");
		}
		file.close();
		return output;
	}
	std::cout << "[ERROR] Could not open file: " << filename << std::endl;
	return "";
}