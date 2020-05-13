#pragma once
#include <string>
#include <vector>
#include "dictionary.hpp"

// enums
typedef enum Note {
	A, A_SHARP, B, C, C_SHARP, D, D_SHARP,
	E, F, F_SHARP, G, G_SHARP, INVALID_NOTE
} note_t;

typedef enum Quality {
	MAJOR, MINOR, DIMINISHED, AUGMENTED
} quality_t;

typedef enum Inversion {
	ROOT, FIRST, SECOND, THIRD
} inversion_t;

// triad class
typedef class Triad
{
public:
	Triad(note_t, quality_t, inversion_t);
	~Triad();
	std::vector<note_t> notes(bool);
	std::vector<std::string> note_names(std::string);
private:
	template <class T> void reorder(std::vector<T>&);
	static std::string fmt_note_name(std::string, note_t);
	static std::vector<int> intervals(quality_t);
	note_t _root;
	quality_t _qual;
	inversion_t _inv;
} triad_t;
