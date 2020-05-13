#pragma once
#include <string>
#include <vector>

// dictionaries for our enums
const static std::vector<std::string> notes {
	"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"
};

const static std::vector<std::string> qualities {
	"Major", "Minor", "Diminished", "Augmented"
};

const static std::vector<std::string> inversions {
	"5/3", "6/3", "6/4"
};
