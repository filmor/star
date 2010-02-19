#ifndef STAR_MIDI_PARSER_HPP
#define STAR_MIDI_PARSER_HPP

#include "midi_data.hpp"
#include <stdexcept>

namespace star
{

    /// Base midi exception thrown by parse_midi
    struct midi_exception : public std::exception {};
    /// The provided data is not a midi file (or its header is corrupted)
    struct not_a_midi_file : public midi_exception {};
    /// The currently parsed track is corrupted
    struct invalid_track : public midi_exception {};

    /// Parse a midi file and return it as a midi_data object
    template <typename IteratorT>
    midi_data parse_midi (IteratorT begin, IteratorT end);

    template <typename RangeT>
    midi_data parse_midi (RangeT const& range)
    {
        return parse_midi (range.begin (), range.end ());
    }

}

#include "parser.ipp"

#endif
