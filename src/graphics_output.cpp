#include "graphics_output.hpp"

#include <boost/bind.hpp>
#include <boost/python.hpp>
#include <iostream>
#include <GL/glfw.h>

namespace star
{

    void graphics_output::open_window (std::size_t x, std::size_t y,
                                       bool windowed = true)
    {
        // glfwOpenWindowHint (GLFW_WINDOW_NO_RESIZE);
        if (!glfwOpenWindow (x, y, 8, 8, 8, 8, 24, 0,
                             windowed ? GLFW_WINDOW : GLFW_FULLSCREEN))
        {
            glfwTerminate ();
            throw "blah";
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

    void graphics_output::close_window ()
    {
        _drawing = false;

        { write_lock l1 (_drawer_mutex); write_lock l2 (_inits_mutex); }
    }

    void graphics_output::draw ()
    {
        _drawing = true;

        open_window (640, 480);

        while (_drawing/* &= 
                !glfwGetKey (GLFW_KEY_ESC) && glfwGetWindowParam (GLFW_OPENED)*/)
            do_draw ();

        glfwCloseWindow ();
    }

    graphics_output::graphics_output ()
        : _dimensions (0, 0)//, _mutex (boost::writer_priority)
          //read_write_mutex is broken
    {
        glfwInit ();
    }

    graphics_output::~graphics_output ()
    {
        close_window ();

        glfwTerminate ();
    }

    void graphics_output::do_draw ()
    {
        glClear (GL_COLOR_BUFFER_BIT);

        {
            read_lock l (_inits_mutex);

            while (!_inits.empty ())
            {
                boost::python::handle_exception (_inits.front ());
                _inits.pop ();
            }
        }

        if (_drawer)
        {
            read_lock l (_drawer_mutex);
            boost::python::handle_exception (_drawer);
        }

        glfwSwapBuffers ();
    }

}
