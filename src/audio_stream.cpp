#include "audio_stream.hpp"

#include <iostream>
#include <iterator>

#include <algorithm>

namespace fs = boost::filesystem;

namespace star
{
    audio_stream::registry_type audio_stream::_registered;

    audio_stream::audio_stream (std::string const& mime_type, fs::path const& path)
    {
        registry_type::const_iterator creator = _registered.find (mime_type);

        std::cout << mime_type << std::endl;

        for (registry_type::const_iterator i = _registered.begin (); i != _registered.end (); ++i)
            std::cout << i->first << std::endl;

        if (creator != _registered.end ())
            _impl = boost::shared_ptr<stream_impl> (
                        (creator->second) (path.string ())
                    );
        else
            // \todo Ausnahme-Klasse
            throw mime_type;
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

}
