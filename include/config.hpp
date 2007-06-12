#ifndef STAR_CONFIG_HPP
#define STAR_CONFIG_HPP

#include <string>

#include <boost/utility.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>

namespace star
{

    /// \todo Options provided by different facilities (i.e. soundcards from FMOD
    class config : boost::noncopyable
    {
    public:
        typedef boost::python::dict data_type;

        static config& instance ()
        {
            static config _instance;
            return _instance;
        }

        template <typename T>
        T get (std::string const& name) const
        {
            return boost::python::extract<T> (_data[name]);
        }

        template <typename T>
        void set (std::string const& name, T const& value)
        {
            _data[name] = value;
        }

    protected:
        void load_source (std::string const&);

    private:
        config ();
        ~config ();

        data_type _data;
    };

}

#endif
