#include <algorithm>
#include <vector>
#include "dictionary.hpp"
#include "triad.hpp"

Triad::Triad(note_t root, quality_t qual, inversion_t inv)
{
	_root = root;
	_qual = qual;
	_inv = inv;
}

Triad::~Triad()
{
}

template <class T>
void Triad::reorder(std::vector<T> &vec)
{
	T first;
	for (int i = 0; i < (int) _inv; i++)
	{
		first = *vec.begin();
		vec.erase(vec.begin());
		vec.push_back(first);
	}
}

std::vector<note_t> Triad::notes(bool dont_reorder = false)
{
	note_t current_note = _root;
	std::vector<note_t> notes_vec { current_note };

	auto intervals = Triad::intervals(_qual);
	for (std::size_t i = 0; i < intervals.size(); i++)
	{
		int note_index = (int)(current_note) + intervals[i];
		if (note_index >= 12)
		{
			note_index %= 12;
		}
		current_note = (note_t)(note_index);
		notes_vec.push_back(current_note);
	}
	if (!dont_reorder)
	{
		reorder(notes_vec);
	}
	return notes_vec;
}

std::string Triad::fmt_note_name(std::string natural_note, note_t triad_note)
{
	// format the note using a flat, sharp, double flat/sharp -
	// whatever is needed given that the letter must be 2 higher
	// than the last
	auto it = std::find(::notes.begin(), ::notes.end(), natural_note);
	int diff = (int) triad_note - (it - ::notes.begin());
	if (diff > 6)
	{
		diff = diff - 12;
	}
	else if (diff < -6)
	{
		diff = diff + 12;
	}
	char accidental = diff < 0 ? 'b' : '#';
	std::string fmt = natural_note;
	for (int i = 0; i < std::abs(diff); i++)
	{
		fmt += accidental;
	}
	return fmt;
}

std::vector<std::string> Triad::note_names(std::string root_fmt)
{
	std::vector<std::string> vec { root_fmt };
	std::vector<note_t> notes_unordered = notes(true);
	for (std::size_t i = 1; i < notes_unordered.size(); i++)
	{
		std::string natural_note(1, (root_fmt[0] - 'A' + i * 2) % 7 + 'A');
		vec.push_back(fmt_note_name(natural_note, notes_unordered[i]));
	}
	reorder(vec);
	return vec;
}

std::vector<int> Triad::intervals(quality_t qual)
{
	auto it = ::intervals_map.find(qual);
	return it->second;
}
