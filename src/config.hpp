#ifndef STAR_CONFIG_HPP
#define STAR_CONFIG_HPP

#include <string>
#include <vector>

#include <boost/utility.hpp>
#include <boost/any.hpp>
#include <tr1/unordered_map>
#include <boost/shared_ptr.hpp>

namespace star
{

    /// \todo Options provided by different facilities (i.e. soundcards from FMOD
    /// \todo config_facility, static_choice, dynamic_choice, template option
    ///       (same as static_choice with the whole set of values)
    /// \info config_facility should register itself to the config singleton and ask
    ///       for values. If the values are wrong, fallback (maybe correcting or
    ///       warning them), don't throw or exit!
    /// \todo Be more generic (if needed) as strings, doubles and ints are not the
    ///       only values to be in a config file. Add at least a list and dict type.
    /// \todo config sinks
    class config : boost::noncopyable
    {
    public:
        typedef std::tr1::unordered_map<std::string, boost::any> data_type;
        class facility;

        /// \todo Type checking should be done as soon as possible!
        class source
        {
            friend class config;
        protected:
            virtual int get_int(std::string const&) = 0;
            virtual double get_double(std::string const&) = 0;
            virtual std::string get_string(std::string const&) = 0;
            virtual ~source() {}
        };

        typedef boost::shared_ptr<source> source_ptr;

        static config& instance ()
        {
            static config instance_;
            return instance_;
        }

    private:
        template <typename T>
        T get (std::string const& name) const
        {
            // return boost::any_cast<T>(data_[name]);
        }

        // template <typename T>
        // void set (std::string const& name, T const& value)
        // {
            /// Write to current sink
        // }

    public:
        void enqueue_source(source_ptr);

    private:
        config ();
        ~config ();

        std::vector<source_ptr> sources_;
    };

}

#include "config_facility.hpp"

#endif
