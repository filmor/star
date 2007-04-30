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
        note operator () (duration_t d)
        {
            const int a = 9;
            const float eps = 0.01;
            const static float log2 = std::log (2.0f);
            const static float log2_440 = std::log (440.0f) / log2;

            typename DetectorPolicy::frequency_type f
                = DetectorPolicy::get_frequency (0, d);

            note result;
            float k = std::log (f) / log2 - log2_440;
            result.value = std::fmod (k, 12) + 9.0f;
            result.octave = k + a/12.0f + eps;
            return result;
        }
    };

}

#endif

