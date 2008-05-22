#include <stdexcept>

#include <boost/foreach.hpp>

#define ASSERT(expression, exception) \
    if (!(expression)) \
        throw exception ();

/// \todo Document!

#if 0 // ndef NDEBUG
#include <boost/preprocessor.hpp>
#include <iostream>
#define SHOW(expression) \
    std::cout << BOOST_PP_STRINGIZE(expression) << " = " << std::hex << expression << std::endl;
#else
#define SHOW(expression)
#endif
#include "iterators.hpp"

namespace star
{
    namespace
    {
        /// Reads an unsigned integer in big endian format while moving the
        /// iterator.
        template <typename IteratorT>
        boost::uint_t<32>::least read_integer (IteratorT& i, std::size_t Size)
        {
            boost::uint_t<32>::least result = 0;

            for (; Size != 0; --Size)
                (result <<= 8) |= (*i++ & 0xff);

            return result;
        }

        /// Reads exactly one byte (often needed).
        template <typename IteratorT>
        boost::uint_t<8>::least read_byte (IteratorT& i)
        {
            return read_integer (i, 1);
        }

        /// Reads a string.
        template <typename IteratorT>
        std::string read_string (IteratorT& i, std::size_t Size)
        {
            std::string result;
            for (; Size; --Size)
                result.push_back (*i++);
            SHOW(result);
            return result;
        }

        /// Reads a variable length integer from the midi stream.
        template <typename IteratorT>
        boost::uint_t<32>::least read_var_len (IteratorT& i)
        {
            boost::uint_t<32>::least result = 0;

            do
                (result <<= 7) |= (*i & 0x7F);
            while (*i++ & 0x80);

            return result;
        }

        template <typename ContainerT, typename IteratorT>
        void parse_track (ContainerT& container, IteratorT& iter)
        {
            /// Define byte type and status type for later use.
            typedef midi_data::byte_t byte_t;
            typedef boost::uint_t<32>::least uint32_t;
            /// Bitmasks don't seem to be portable
            typedef struct { byte_t channel; byte_t opcode; } status_type;

            /// Read the track header.
            ASSERT(read_string (iter, 4) == "MTrk", invalid_track);
            const uint32_t length = read_integer (iter, 4);

            SHOW(length)

            /// length checking currently doesn't work very well. Just hope ;) 
            // length_checking_iterator<IteratorT> i (iter, length);
            IteratorT& i = iter;
            container.reserve (length);

            status_type running_status = { 0, 0 };

            for (;;)
            {
                midi_data::ticks_t ticks = read_var_len (i);

                SHOW(ticks);

                IteratorT prev = i;

                byte_t status_byte = read_byte (i);

                SHOW(unsigned(status_byte))

                status_type status = { status_byte & 0x0f
                                     , (status_byte & 0xf0) >> 4
                                     };

#define MIDI_EVENT(OPCODE, TYPE, CODE) \
    case OPCODE: \
        { \
            TYPE ev; \
            ev.channel = status.channel; \
            ev.delay = ticks; \
            CODE; \
            container.push_back (ev); \
        } \
        break;

                switch (status.opcode)
                {
                MIDI_EVENT(0x8, midi_data::key_release, 
                        ev.note = read_byte (i); ev.velocity = read_byte (i)
                        )

                case 0x9:
                    {
                        midi_data::key_press ev;
                        ev.channel = status.channel;
                        ev.delay = ticks;
                        ev.note = read_byte (i); ev.velocity = read_byte (i);
                        if (ev.velocity == 0)
                            container.push_back (
                                    *reinterpret_cast<midi_data::key_release*> (&ev)
                                    );
                        else
                            container.push_back (ev);
                    }
                    break;

                MIDI_EVENT(0xa, midi_data::key_aftertouch,
                        ev.note = read_byte (i); ev.velocity = read_byte (i)
                        )

                MIDI_EVENT(0xb, midi_data::control_change, 
                        ev.controller = read_byte (i); ev.value = read_byte (i)
                        )

                MIDI_EVENT(0xc, midi_data::patch_change, 
                        ev.program = read_byte (i);
                        )
                
                MIDI_EVENT(0xd, midi_data::channel_aftertouch,
                        ev.touched_channel = read_byte (i)
                        )

                MIDI_EVENT(0xe, midi_data::pitch_wheel_change,
                        ev.value = (read_byte (i) << 7) | read_byte (i)
                        )

                /// \todo Handle Sequence Number, Trackname, and End-of-Track properly
                case 0xf:
                    if (status.channel == 0xf)
                    {
                        midi_data::meta_event ev;
                        ev.delay = ticks;
                        ev.type = read_byte (i);
                        SHOW(unsigned(ev.type));
                        /// \todo End-of-Track handling (by policy?)
                        if (ev.type == 0x2f)
                        {
                            read_byte (i);
                            break;
                        }
                        const uint32_t len = read_var_len (i);
                        ev.data = read_string (i, len);
                        container.push_back (ev);
                    }
                    /// Ignore SYSEX for now
                    else if (status_byte == 0xf0)
                        while ((status_byte = read_byte (i)) != 0xf7)
                            ;
                    break;

                default:
                    i = prev;
                    status = running_status;
                    SHOW("===");
                }

                running_status = status;
            }
        }

    }

    template <typename IteratorT>
    midi_data parse_midi (IteratorT begin, IteratorT end)
    {
        midi_data data;

        end_checking_iterator<IteratorT> i (begin, end);

        /// Parse the midi header
        ASSERT(read_string (i, 4) == "MThd", not_a_midi_file);
        ASSERT(read_integer (i, 4) == 6, not_a_midi_file);
        data._format = read_integer (i, 2);
        ASSERT(data._format < 3, not_a_midi_file);
        data._tracks.resize (read_integer (i, 2));
        data._delta_time = read_integer (i, 2);

        int k = 0;

        BOOST_FOREACH(midi_data::track& t, data._tracks)
        {
            SHOW(k)
            parse_track (t, i);
            ++k;
        }

        return data;
    }

}

#undef ASSERT

