#ifndef STAR_MIDI_PARSER_HPP

#include <string>
#include <vector>

#include <boost/variant.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range.hpp>
#include <boost/integer.hpp>

namespace star
{

    template <typename>
    class midi_dispatcher;

    class midi_data
    {
    public:
        template <typename>
        friend class midi_dispatcher;

        typedef boost::uint_t<32>::fast ticks_t;
        typedef boost::uint_t<8>::least byte_t;
        typedef byte_t channel_t;

        struct midi_event { ticks_t delay; };
            struct non_meta_event : public midi_event { channel_t channel; };
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

        template <typename RangeT>
        midi_data (RangeT const& range)
        {
            parse_data (range.begin (), range.end ());
        }

        template <typename IteratorT>
        midi_data (IteratorT begin, IteratorT end)
        {
            parse_data (begin, end);
        }

        ticks_t get_division () const { return _delta_time; }

    private:
        template <typename IteratorT>
        void parse_data (IteratorT begin, IteratorT end);

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
        typedef std::vector<event_type> track;

        std::vector<track> _tracks;
        ticks_t _delta_time;
        boost::uint_t<16>::least _format;
    };

    /// Currently only ReturnType = void is meaningful
    template <typename ReturnType>
    struct midi_visitor : public boost::static_visitor<ReturnType>
    {
        typedef ReturnType return_type;
        return_type operator () (midi_data::midi_event const&)
        { return return_type (); }
        return_type operator () (midi_data::midi_event&) { return return_type (); }
    };

    template <class VisitorType>
    class midi_dispatcher
    {
    public:
        typedef VisitorType visitor_type;
        typedef typename VisitorType::return_type return_type;

        midi_dispatcher () {}
        midi_dispatcher (visitor_type const& v) : _visitor (v) {}

        void operator () (midi_data& data, short track_number)
        {
            midi_data::track& track = data._tracks.at (track_number);
            std::for_each (track.begin (), track.end (),
                           boost::apply_visitor (_visitor)
                    );
        }

    private:
        visitor_type _visitor;
    };

    template <class VisitorType>
    midi_dispatcher<VisitorType> make_dispatcher (VisitorType const& visitor)
    {
        return midi_dispatcher<VisitorType> (visitor);
    }

//    void dispatch_midi (bla blubb, midi_data& data, short track_number)
//    {
//        midi_dispatcher d (generate_visitor ());
//        try
//        {
//            d (data, track_number);
//        }
//        catch (std::out_of_bounds&)
//        {
//            throw invalid_track ();
//        }
//    }

}

#include "midi_parser.ipp"

#endif
