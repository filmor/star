#ifndef STAR_GRAPHICS_HPP
#define STAR_GRAPHICS_HPP

namespace star
{

    class plane
    {
    public:
        void render ();

        void update ();
    };

    class lyrics_output : public plane
    {};

    class notes_output : public plane
    {};

    class text_output : public plane
    {
    public:
        text_output (std::string const&);
    };

    class display : public plane
    {};

}

#endif

