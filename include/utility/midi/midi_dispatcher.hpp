#ifndef STAR_MIDI_DISPATCHER_HPP
#define STAR_MIDI_DISPATCHER_HPP

#include "midi_data.hpp"

namespace star
{

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

        midi_dispatcher () {}
        midi_dispatcher (visitor_type const& v) : _visitor (v) {}

        void dispatch (midi_data& data, short track_number);
        
        void timed_dispatch (midi_data& data, short track_number);
        
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

#include "midi_dispatcher.ipp"

#endif
