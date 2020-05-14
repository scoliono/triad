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

// a map of intervals (in half-steps) for every quality
const static std::map<quality_t, std::vector<int>> intervals_map {
    {quality_t::MAJOR, {4, 3}},
    {quality_t::MINOR, {3, 4}},
    {quality_t::DIMINISHED, {3, 3}},
    {quality_t::AUGMENTED, {4, 4}},
};
