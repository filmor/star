#ifndef STAR_PLAYER_HPP
#define STAR_PLAYER_HPP

#include <boost/function.hpp>
#include "basic_types.hpp"
#include "song.hpp"

namespace star
{

    /// \todo Reformat & define correct copy behaviour
    class player
    {
    public:
        /// \todo Rename! (candidates: lyrics_item, )
        struct syllable_t
        {
            duration_t start;
            duration_t pos;
            duration_t end;
        };

        typedef boost::function<void (note_t, note_t, syllable_t)>
            notes_callback_type;

        player () : _playing (false) {}

        /// \attention This is not in any way connected to song::syllable!
        typedef boost::function<void ()> syllable_callback_type;

        void set_notes_callback (notes_callback_type const& c)
        { _notes_callback = c; }

        /// Callback whenever the next syllable starts.
        void add_syllable_callback (syllable_callback_type const& c)
        { _syllable_callbacks.push_back (c); }

        void reset_syllable_callbacks () { _syllable_callbacks.clear (); }

        void start (song const&) const;

        bool is_playing () const { return _playing; }

    private:
        mutable bool _playing;

        /// The one and only notes callback function.
        notes_callback_type _notes_callback;
        /// A vector of syllable callbacks.
        std::vector<syllable_callback_type> _syllable_callbacks;
    };

}

#endif

