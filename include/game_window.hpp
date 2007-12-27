#ifndef STAR_GRAPHICS_OUTPUT_HPP
#define STAR_GRAPHICS_OUTPUT_HPP

#include "basic_types.hpp"

#include <queue>
#include <utility>
#include <stdexcept>

#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace star
{

    struct graphics_exception : std::runtime_error
    {
        graphics_exception (std::string const& s) : std::runtime_error (s)
        {}
    };

    namespace detail { void glfw_key_callback (int, int); }
    
    /**
     * Game window singleton.
     *
     * This class handles all window-related I/O as OpenGL graphics and
     * keyboard input. It is currently implemented using GLFW.
     * \todo Window closing signal
     */
    class game_window : boost::noncopyable
    {
        friend void detail::glfw_key_callback (int, int);

        /// Private typedefs.
        /// \{
        typedef boost::mutex                mutex_type;
        typedef boost::try_mutex            draw_mutex_type;
        typedef mutex_type::scoped_lock     read_lock;
        typedef mutex_type::scoped_lock     write_lock;
        /// \)

    public:
        typedef int             key_type;
        typedef int             key_state_type;
        enum key_callback_mode { KEY_MODE, CHAR_MODE };

        typedef boost::function<void ()>    initializer_type;

        /// Functor type for drawers
        typedef boost::function<void ()>    drawer_type;
        
        /// Functor type for keyboard callbacks
        typedef boost::function<void (key_type, key_state_type)>
            key_callback_type;
        
        /// Type for window dimensions (width, height)
        typedef std::pair<std::size_t, std::size_t>
            dimensions_type;

        /// Singleton instance method
        static game_window& instance ()
        {
            static game_window _instance;
            return _instance;
        }

        /// Start the drawing loop
        void draw ();

        /// Close the window and stop the drawing loop
        void close ();

        /// \todo Rename, init is not appropriate
        void enqueue_init (initializer_type const& f)
        { write_lock l (_inits_mutex); _inits.push (f); }
        
        /// Set the current drawing function to f
        void set_drawer (drawer_type const& f)
        { write_lock l (_drawer_mutex); _drawer = f; }

        /// Clear the current drawer (does not stop the drawing loop!)
        void clear_drawer () { write_lock l (_drawer_mutex); _drawer.clear (); }

        /// \returns if currently the drawing loop is running
        bool is_drawing () const { return _drawing; }

        void set_key_callback (key_callback_type cb, key_callback_mode mode);
        void clear_key_callback ();

        dimensions_type get_dimensions () const { return _dimensions; }

    private:
        game_window ();
        ~game_window ();

        /// Open a window and prepare the OpenGL context.
        void open (std::size_t x, std::size_t y, bool windowed);        

        /// Draw a frame.
        void do_draw ();

        /// The current drawing functor, called every frame.
        drawer_type _drawer;

        key_callback_type _key_callback;

        /// Queue of functions to run once
        std::queue<initializer_type> _inits;
        
        mutex_type _drawer_mutex;
        mutex_type _inits_mutex;

        volatile bool _drawing;
        
        /// Window x and y sizes
        dimensions_type _dimensions;
    };

}

#endif
