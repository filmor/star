#include "song.hpp"
#include "python.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include <vector>
#include <iterator>
#include <algorithm>

#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

#include "fmod.hpp"
#define STAR_DETECTOR_POLICY fmod_detector

#include "utility/midi/midi_parser.hpp"

namespace bf = boost::filesystem;
namespace bp = boost::python;

namespace star
{

    namespace 
    {
        inline note_t midi_to_note_t (midi_data::byte_t b)
        {
            /// \todo
            note_t res = {b % 12, b / 12};
            return res;
        }

        struct lyrics_getter_visitor : public midi_visitor<void>
        {
            lyrics_getter_visitor (song::data_type& data, midi_data::ticks_t division)
                : ticks_per_ms (5e5 / division), _duration (0.), _vector (data)
            {}

            void operator () (midi_data::key_press const& ev)
            {
                add_ticks (ev.delay);
                _note = midi_to_note_t (ev.note);
            }

            void operator () (midi_data::meta_event const& ev)
            {
                add_ticks (ev.delay);
                if (ev.type == 0x05) // lyric event
                {
                    _vector.push_back (
                            boost::make_tuple ( duration_t (_duration)
                                              , _note, ev.data)
                            );
                    _duration = 0.;
                };
            }

            void operator () (midi_data::midi_event const& ev)
            { add_ticks (ev.delay); }

        private:
            void add_ticks (midi_data::ticks_t t)
            {
                _duration += t * ticks_per_ms;
            }

            double ticks_per_ms;
            note_t _note;
            double _duration;
            song::data_type& _vector;
        };
    }
    
    /// \todo Implement converters (from UltraStar to smf)
    song::song (bf::path const& path)
        : _path (path)
    {
        bf::ifstream lyrics (_path / "lyrics", std::ios::binary);
        lyrics.unsetf (std::ios::skipws);

        /// istream_iterator is not bidirectional, but currently midi_data requires
        /// op-- for running statusses.
        std::vector<unsigned char> d;
        std::copy (std::istream_iterator<unsigned char> (lyrics),
                   std::istream_iterator<unsigned char> (), std::back_inserter (d));

        midi_data data (d);

        (make_dispatcher (lyrics_getter_visitor (_lyrics_data, data.get_division ())))
            (data, 0);

        {
            python::restricted_env env;
            python::exec_file((python::str ((_path / "description").file_string ())),
                              _desc, _desc);
        }
    }

    audio_stream song::get_audio_stream (unsigned char s) const
    {
        /// \todo Restrict also the extraction?!
        return audio_stream (python::extract<std::string> (_desc["audio_type"]),
                             _path / "audio");
    }

    song::notes song::get_notes (unsigned char s) const
    {
        return boost::make_iterator_range (notes_iterator (_lyrics_data.begin ()),
                                           notes_iterator (_lyrics_data.end ())
                                          );
    }

    song::lyrics song::get_lyrics (unsigned char track) const
    {
        return boost::make_iterator_range (_lyrics_data.begin (), _lyrics_data.end ());
    }

}
