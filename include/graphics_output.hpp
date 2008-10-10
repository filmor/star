#ifndef STAR_GRAPHICS_OUTPUT_HPP
#define STAR_GRAPHICS_OUTPUT_HPP

#include <queue>
#include <utility>

#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "basic_types.hpp"

namespace star
{

    class graphics_output : boost::noncopyable
    {
        typedef boost::mutex                mutex_type;
        typedef boost::try_mutex            draw_mutex_type;
        typedef mutex_type::scoped_lock     read_lock;
        typedef mutex_type::scoped_lock     write_lock;
    public:
        typedef boost::function<void ()>    initializer_type;
        typedef boost::function<void ()>    drawer_type;
        typedef std::pair<std::size_t, std::size_t> dimensions_type;

        static graphics_output& instance ()
        {
            static graphics_output _instance;
            return _instance;
        }

        void draw ();

        void close_window ();

        void enqueue_init (initializer_type const& f)
        { write_lock l (_inits_mutex); _inits.push (f); }
        
        void set_drawer (drawer_type const& f)
        { write_lock l (_drawer_mutex); _drawer = f; }

        void clear_drawer () { write_lock l (_drawer_mutex); _drawer.clear (); }
        bool is_drawing () const { return _drawing; }
        dimensions_type get_dimensions () const { return _dimensions; }

    private:
        graphics_output ();
        ~graphics_output ();

        void open_window (std::size_t x, std::size_t y, bool windowed);        

        void do_draw ();

        drawer_type _drawer;
        std::queue<initializer_type> _inits;
        
        mutex_type _drawer_mutex;
        mutex_type _inits_mutex;

        bool _drawing;
        dimensions_type _dimensions;
    };

}

#endif