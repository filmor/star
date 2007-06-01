#include "audio_stream.hpp"

#include <iostream>
#include <iterator>

#include <algorithm>

namespace fs = boost::filesystem;

namespace star
{
    audio_stream::audio_stream (std::string const& type, fs::path const& path)
    {
        registry_type const& registered = *_get_registered ();
        registry_type::const_iterator creator = registered.find (type);

        if (creator != registered.end ())
            _impl = boost::shared_ptr<stream_impl> (
                        (creator->second) (path.string ())
                    );
        else
            // \todo proper exception class 
            throw type;
    }

    audio_stream::~audio_stream ()
    {
    }

    void audio_stream::play ()
    {
        _impl->play ();
    }

    void audio_stream::stop ()
    {
        _impl->stop ();
    }

    void audio_stream::wait ()
    {
        _impl->wait ();
    }

}
