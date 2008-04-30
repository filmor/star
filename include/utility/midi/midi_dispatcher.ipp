#include "midi_dispatcher.hpp"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>

namespace star
{

    template <class VisitorType>
    void midi_dispatcher<VisitorType>::dispatch (midi_data& data, short track_number)
    {
        midi_data::track& track = data._tracks.at (track_number);

        std::for_each (track.begin (), track.end (),
                       boost::apply_visitor (_visitor)
                      );
    }

    namespace
    {
        template <typename VisitorT>
        class timed_apply
        {
        public:
            typedef VisitorT visitor_type;

            timed_apply (visitor_type const& visitor, midi_data::ticks_t delta)
                : _delta (delta), _apply (visitor)
            {}

            template <typename Variant>
            void operator () (Variant& operand)
            {
                midi_data::ticks_t delay
                    = operand.template get<midi_data::midi_event> ().delay;

                _apply (operand);

                boost::thread::sleep (_time);
            }

        private:
            midi_data::ticks_t _delta;
            boost::xtime _time;
            boost::apply_visitor_delayed_t<visitor_type> _apply;
        };

    }
        
    
    template <class VisitorType>
    void midi_dispatcher<VisitorType>::timed_dispatch
        (midi_data& data, short track_number)
    {
        midi_data::track& track = data._tracks.at (track_number);
        std::for_each (track.begin (), track.end (),
                       timed_apply<visitor_type> (_visitor, data.get_division ())
                );
    }

}
        
