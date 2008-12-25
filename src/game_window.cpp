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
    void game_window::open(std::size_t x, std::size_t y, bool windowed = true)
    {
        glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
        if (!glfwOpenWindow(x, y, 8, 8, 8, 8, 24, 0,
                             windowed ? GLFW_WINDOW : GLFW_FULLSCREEN))
        {
            glfwTerminate();
            throw graphics_exception("Could not open window.");
        }

        dimensions_ = std::make_pair(x, y);

        glfwSwapInterval(1);

        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glClearColor(0, 0, 0, 0);

        // GLfloat afLightDiffuse[4] = {0.76, 0.75, 0.65, 1.0};

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        // glLightfv(GL_LIGHT0, GL_DIFFUSE, afLightDiffuse);

        glClearDepth(1);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	    gluPerspective(45.0f, static_cast<GLfloat>(dimensions_.first) 
                             / dimensions_.second, 0.1f, 100.0f);

	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
    }

    void game_window::close()
    {
        drawing_ = false;

        { write_lock l1(drawer_mutex_); write_lock l2(inits_mutex_); }
    }

    void game_window::draw()
    {
        drawing_ = true;

        open(640, 480);

        while (drawing_ &= 
                !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED))
            do_draw();

        glfwCloseWindow();
    }

    game_window::game_window()
        : dimensions_(0, 0)//, _mutex(boost::writer_priority)
          //read_write_mutex is broken
    {
        glfwInit();
    }

    game_window::~game_window()
    {
        close();

        glfwTerminate();
    }

    void game_window::do_draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (!inits_.empty())
        {
            read_lock l(inits_mutex_);

            do
            {
                inits_.front()();
                inits_.pop();
            }
            while (!inits_.empty());

        }

        if (drawer_)
        {
            read_lock l(drawer_mutex_);
            drawer_();
        }

        glfwSwapBuffers();
    }

    void game_window::set_key_callback(key_callback_type cb,
                                       key_callback_mode mode)
    {
        key_callback_ = cb;
        if (mode == KEY_MODE)
            glfwSetKeyCallback(&detail::glfw_key_callback);
        else if (mode == CHAR_MODE)
            glfwSetCharCallback(&detail::glfw_key_callback);
    }

    void game_window::clear_key_callback()
    {
        /// It might be necessary to call SetCharCallback(0) if this mode was used.
        glfwSetKeyCallback(0);
    }

    namespace detail
    {
        void glfw_key_callback(int key, int state)
        {
            game_window::instance().key_callback_(key, state);
        }   
    }

}
