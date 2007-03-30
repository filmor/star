#ifndef STAR_GRAPHICS_HPP
#define STAR_GRAPHICS_HPP

namespace star
{

    struct coords
    {
        float x; // 1.0 => rechts, -1.0 => links
        float y; // 1.0 => oben, -1.0 => unten
        float z; // Wertebereich beliebig
    };

    class plane
    {
    public:
        void render (output& o)
        {
            if (!o.root.rendered (this))
                this->do_render (o);
            else
                o.draw (o.root.cache[this]);
        }

    protected:
        virtual void do_render (output&) = 0;
    };

    class composable_plane : public plane
    {
    public:
        typedef boost::tuple<coords, coords, coords, coords> dim;
        typedef std::vector<std::pair<dim, plane*> > planes_type;

        void add_plane (plane* other, dim);

    protected:
        virtual void do_render (output& o) = 0
        {
            for (planes_type::const_iterator i = _planes.begin ();
                    i != _planes.end (); ++i)
            {
                output& r = o.rectangle (i->first);
                i->second->render (r);
            }
        }

    private:
        planes_type _planes;
    };

    class notes_output : public plane
    {
    protected:
        virtual void do_render (output& o);
    };

    class text_output : public plane
    {
    public:
        text_output (std::string const& s) : _string (s) {}

    protected:
        virtual void do_render (output& o)
        {
            o.draw_text (_string);
        }

    private:
        std::string const& _string;
    };

    class lyrics_output : public text_output
    {};

}

#endif

