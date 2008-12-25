#ifndef STAR_CONFIG_SOURCES_HPP
#define STAR_CONFIG_SOURCES_HPP

#include "config.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>

namespace star
{

    /// \todo Become also a sink
    class python_source : public config::source
    {
    public:
        python_source (boost::filesystem::path const&);
        python_source (boost::python::dict);

        virtual std::string get_string (std::string const&);
        virtual int get_int (std::string const&);
        virtual double get_double (std::string const&);

    private:
        boost::python::dict _dict;
    };


    /// \todo GNU-Style command line source (--help etc.) as a replacement for
    ///       Boost.ProgramOptions.
    /// \todo generic Spirit source.

}

#endif

