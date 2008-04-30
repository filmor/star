#ifndef STAR_MIDI_DATA_HPP
#define STAR_MIDI_DATA_HPP

#include <string>
#include <vector>

#include <boost/variant.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/integer.hpp>

namespace star
{

    /// Forward declaration for friendship
    template <typename>
    class midi_dispatcher;

    /**
     * Class for midi tracks and their additional information.
     */
    class midi_data
    {
    public:
        template <typename>
        friend class midi_dispatcher;

        template <typename IteratorT>
        friend midi_data parse_midi (IteratorT, IteratorT);

        /// Type for midi ticks, the common unit for time durations.
        typedef boost::uint_t<32>::fast ticks_t;
        /// A byte.
        typedef boost::uint_t<8>::least byte_t;

        /// Base midi event. All events have a delay value.
        struct midi_event { ticks_t delay; };
            /// All non-meta events operate on a specific channel
            struct non_meta_event : public midi_event { byte_t channel; };
                struct key_event : public non_meta_event
                { byte_t note; byte_t velocity; };
                    struct key_release : public key_event {};
                    struct key_press : public key_event {};
                    struct key_aftertouch : public key_event {};
                struct control_change : public non_meta_event
                { byte_t controller; byte_t value; };
                struct patch_change : public non_meta_event { byte_t program; };
                struct channel_aftertouch : public non_meta_event
                { byte_t touched_channel; };
                struct pitch_wheel_change : public non_meta_event
                { boost::uint_t<14>::least value; };
            struct meta_event : public midi_event
            { std::string data; byte_t type; };

        ticks_t get_division () const { return _delta_time; }

    private:
        /// The event can be (exactly) any of the ones listed here, so its
        /// implemented as a variant instead of some polymorphic bloatware.
        typedef boost::variant<
                    key_release,
                    key_press,
                    key_aftertouch,
                    control_change,
                    patch_change,
                    channel_aftertouch,
                    pitch_wheel_change,
                    meta_event
                >
                event_type;
        /// A track is a sequence of events.
        typedef std::vector<event_type> track;

        std::vector<track> _tracks;

        ticks_t _delta_time;
        boost::uint_t<16>::least _format;
    };

}

#endif
