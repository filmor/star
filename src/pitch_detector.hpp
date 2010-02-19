#ifndef STAR_PITCH_DETECTOR_HPP
#define STAR_PITCH_DETECTOR_HPP

#include <cmath>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "basic_types.hpp"

namespace star
{

    template <class DetectorPolicy>
    class pitch_detector : public DetectorPolicy
    {
    public:
        note_t operator () (time_duration d)
        {
            const int a = 9;
            const double eps = 0.01;
            const static double log2 = std::log (2.0);
            const static double log2_440 = std::log (440.0) / log2;

            typename DetectorPolicy::frequency_type f
                = DetectorPolicy::get_frequency (0, d);

            note_t result;
            float k = std::log (f) / log2 - log2_440;
            result.value = std::fmod (k, 12) + 9.0f; //  Addition nicht davor?!
            result.octave = static_cast<unsigned> (k + a/12.0f + eps);
            return result;
        }
    };

}

#endif

