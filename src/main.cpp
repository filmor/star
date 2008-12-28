#include <boost/filesystem.hpp>
#include <iostream>

#include "game_window.hpp"
#include "screen_manager.hpp"
#include "config.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

namespace bf = boost::filesystem;

using namespace star;

void game_thread()
{
    {
        screen_manager manager(game_window::instance());

        config& cfg = config::instance ();

/*      cfg.add_source (new command_line_source (argc, argv));
        try
        {
            cfg.add_source (new python_source (cfg.get<bf::path> ("config_file")));
        }
        catch (file_not_found&) {} */

        bf::directory_iterator end;

        for (bf::directory_iterator i(bf::path("screens")); i != end; ++i)
        {
            //try
            //{
                if (bf::is_regular(i->status()))
                {
                    bf::ifstream file(*i);
                    manager.load_screen(i->leaf(), file);
                }
            //}
        }

        manager.show_screen("main");
    }

    game_window::instance().close();
}

int main (int argc, char** argv)
{
    boost::thread thread(&game_thread);

    try
    {
        game_window::instance().draw();
        thread.join();
    }
    catch (window_closed_exception const&)
    {
        // Kill game thread
    }
}

