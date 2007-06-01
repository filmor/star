#ifndef STAR_SONG_HPP
#define STAR_SONG_HPP

#include <boost/function.hpp>
#include "basic_types.hpp"
#include "song_info.hpp"

namespace star
{

    /**
     * \todo Rename to player
     */
    class song
    {
    public:
        /// \todo Rename!
        struct syllable_t
        {
            duration_t start;
            duration_t pos;
            duration_t end;
        };

        typedef boost::function<void (note_t, note_t, syllable_t)> notes_callback_type;

        /// \attention This is not in any way connected to song::syllable!
        typedef boost::function<void ()> syllable_callback_type;

        void set_notes_callback (notes_callback_type const& c)
        { _notes_callback = c; }

        /// Callback whenever the next syllable starts.
        void add_syllable_callback (syllable_callback_type const& c)
        { _syllable_callbacks.push_back (c); }

        void reset_syllable_callbacks () { _syllable_callbacks.clear (); }

        void start (song_info const&) const;

        /// \todo This member is not really needed. Rename the class and let the
        ///       song_info be passed by reference to song::start.
        // song_info const& _info;

    private:
        /// The one and only notes callback function.
        notes_callback_type _notes_callback;
        /// A vector of syllable callbacks.
        std::vector<syllable_callback_type> _syllable_callbacks;
    };

}

#endif

