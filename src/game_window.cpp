#include "game_window.hpp"

#include <boost/bind.hpp>
#include <iostream>
#include <GL/glfw.h>

namespace star
{

    /**
     * Open the main window with a ready gl context.
     *
     * \param x Width of the window
     * \param y Height of the window
     * \param windowed Start in windowed mode
     */    
    void game_window::open (std::size_t x, std::size_t y, bool windowed = true)
    {
        glfwOpenWindowHint (GLFW_WINDOW_NO_RESIZE, GL_TRUE);
        if (!glfwOpenWindow (x, y, 8, 8, 8, 8, 24, 0,
                             windowed ? GLFW_WINDOW : GLFW_FULLSCREEN))
        {
            glfwTerminate ();
            throw graphics_exception ("Could not open window.");
        }

        _dimensions = std::make_pair (x, y);

        glfwSwapInterval (1);

        glShadeModel (GL_SMOOTH);
        glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glClearColor (0, 0, 0, 0);

        // GLfloat afLightDiffuse[4] = {0.76, 0.75, 0.65, 1.0};

        glEnable (GL_TEXTURE_2D);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, 1);

        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);
        // glLightfv (GL_LIGHT0, GL_DIFFUSE, afLightDiffuse);

        glClearDepth(1);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	    gluPerspective (45.0f, static_cast<GLfloat> (_dimensions.first) 
                              / _dimensions.second, 0.1f, 100.0f);

	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
    }

    void game_window::close ()
    {
        _drawing = false;

        { write_lock l1 (_drawer_mutex); write_lock l2 (_inits_mutex); }
    }

    void game_window::draw ()
    {
        _drawing = true;

        open (640, 480);

        while (_drawing &= 
                !glfwGetKey (GLFW_KEY_ESC) && glfwGetWindowParam (GLFW_OPENED))
            do_draw ();

        glfwCloseWindow ();
    }

    game_window::game_window ()
        : _dimensions (0, 0)//, _mutex (boost::writer_priority)
          //read_write_mutex is broken
    {
        glfwInit ();
    }

    game_window::~game_window ()
    {
        close ();

        glfwTerminate ();
    }

    void game_window::do_draw ()
    {
        glClear (GL_COLOR_BUFFER_BIT);

        {
            read_lock l (_inits_mutex);

            while (!_inits.empty ())
            {
                (_inits.front ()) ();
                _inits.pop ();
            }
        }

        if (_drawer)
        {
            read_lock l (_drawer_mutex);
            _drawer ();
        }

        glfwSwapBuffers ();
    }

    void game_window::set_key_callback (key_callback_type cb,
                                        key_callback_mode mode)
    {
        _key_callback = cb;
        if (mode == KEY_MODE)
            glfwSetKeyCallback (&detail::glfw_key_callback);
        else if (mode == CHAR_MODE)
            glfwSetCharCallback (&detail::glfw_key_callback);
    }

    void game_window::clear_key_callback ()
    {
        /// It might be necessary to call SetCharCallback(0) if this mode was used.
        glfwSetKeyCallback (0);
    }

    namespace detail
    {
        void glfw_key_callback (int key, int state)
        { game_window::instance ()._key_callback (key, state); }   
    }

}
