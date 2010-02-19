#ifndef STAR_SCREEN_OBJECT_HPP
#define STAR_SCREEN_OBJECT_HPP

namespace star
{
    class screen_manager;

    class screen_object
    {
    public:
        friend class screen_manager;

    protected:
        virtual void do_draw() const = 0;

    private:
        void draw() const;
    };
    
    class layoutbox : public screen_object
    {
    public:

    protected:
        virtual void do_draw() const;

    private:
        std::vector<std::pair<position_object, screen_object> > elements_;
        /// Effects? Maybe join with position_object to prepare_object
    }


    
