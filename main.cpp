#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "dictionary.hpp"
#include "triad.cpp"

note_t parse_note_name(std::string str)
{	
	// verify the natural note actually exists
	auto it = std::find(notes.begin(), notes.end(), str.substr(0, 1));
	if (it == notes.end())
	{
		return Note::INVALID_NOTE;
	}
	
	int offset = it - notes.begin();
	for (std::size_t i = 1; i < str.size(); i++)
	{
		switch (str[i])
		{
			case '#':
				offset++;
				break;
			case 'b':
				offset--;
				break;
			default:
				return Note::INVALID_NOTE;
		}
	}
	offset %= (offset < 0 ? -12 : 12);
	return (note_t)(offset);
}

template <class T>
T random_item(std::vector<T> vec)
{
	return vec[std::rand() % vec.size()];
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::srand(unsigned(std::time(NULL)));
		std::cout << "Usage: triad <root note> [quality] [inversion]" << std::endl;
		std::cout << "Example: triad " << random_item(notes) << " "
				  << random_item(qualities) << " "
				  << random_item(inversions) << std::endl; 
		return -1;
	}
	
	std::string root_str = argv[1];
	std::string qual_str = argc >= 3 ? argv[2] : qualities[0];
	std::string inv_str = argc >= 4 ? argv[3] : inversions[0];
	
	// capitalize input strings
	root_str[0] = toupper((int) root_str[0]);
	std::transform(root_str.begin() + 1, root_str.end(), root_str.begin() + 1, tolower);
	qual_str[0] = toupper((int) qual_str[0]);
	std::transform(qual_str.begin() + 1, qual_str.end(), qual_str.begin() + 1, tolower);
	
	note_t root = parse_note_name(root_str);
	if (root == Note::INVALID_NOTE)
	{
		std::cerr << "bad key: unknown note " << root_str << std::endl;
		return 1;
	}
	
	// verify the key quality actually exists
	auto it = std::find(qualities.begin(), qualities.end(), qual_str);
	if (it == qualities.end())
	{
		std::cerr << "bad key: unknown quality " << qual_str << std::endl;
		return 2;
	}
	quality_t qual = (quality_t)(it - qualities.begin());
	
	// make sense of the inversion
	it = std::find(inversions.begin(), inversions.end(), inv_str);
	if (it == inversions.end())
	{
		std::cerr << "bad key: unknown inversion " << inv_str << std::endl;
		return 3;
	}
	inversion_t inv = (inversion_t)(it - inversions.begin());
	
	std::cout << "The notes in a " << root_str << " " << qual_str << " " << inv_str << " triad are" << std::endl;
	
	triad_t triad(root, qual, inv);
	std::vector<std::string> triad_notes = triad.note_names(root_str);
	for (std::size_t i = 0; i < triad_notes.size(); i++)
	{
		std::cout << triad_notes[i];
		if (i == triad_notes.size() - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << " ";
		}
	}
	return 0;
}
