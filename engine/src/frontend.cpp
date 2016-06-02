#include "core/rect.h"
#include "core/environment.h"
#include "util/frontend.h"
#include "core/joystickevent.h"
#include "core/keyboardevent.h"
#include "core/mousebuttonevent.h"
#include "core/texture.h"

class FrontEnd::Impl {
    
    public:
        
        // -------------------------------------------------------------  
        // Function: Impl()  
        // Description: Implements the frontend.
        // Parameters:
        //      Level * parent;         
        //      const string& texture;      
        //      unsigned long duration;     
        //      const Color& background;    Backgroung color
        // -------------------------------------------------------------   
        Impl(Level * parent, const string& texture, unsigned long duration,
            const Color& background)
            : m_parent(parent), m_texture(nullptr), m_background(background),
            m_fad(), m_start(0), m_duration(duration) {

            Environment *env = Environment::get_instance();
            m_texture = env->resources_manager->get_texture(texture);

            m_in = m_duration / 3;
            m_out = m_duration - m_in;
        }

        // -------------------------------------------------------------  
        // Function: ~Impl()  
        // Observations:
        //      Funtion not implemented 
        // -------------------------------------------------------------   
        ~Impl() {
        }

        // -------------------------------------------------------------  
        // Function: on_event()  
        // Description: Check if the mouse button was pressed or not.
        // Parameters:
        //      const MouseButtonEvent& event;     Event of click on 
        //                                         mouse button
        // Return: bool
        // -------------------------------------------------------------   
        bool on_event(const MouseButtonEvent& event) {
            if (event.state() == MouseButtonEvent::PRESSED) {
                m_parent->finish();
                return true;
            }

            return false;
        }

        // -------------------------------------------------------------  
        // Function: on_event()  
        // Description: Check if keyboard was pressed or not.
        // Parameters:
        //      const KeyboardEvent& event;     Event of action on 
        //                                      keyboard
        // Return: bool
        // -------------------------------------------------------------   
        bool on_event(const KeyboardEvent& event) {
            if (event.state() == KeyboardEvent::PRESSED) {
                m_parent->finish();
                return true;
            } else {
                // Nothing to do
            }

            return false;
        }

        // -------------------------------------------------------------  
        // Function: on_event()  
        // Description: Check the if JoyStick was pressed or not.
        // Parameters:
        //      const JoyStickEvent& event;     Event of action on 
        //                                      JoyStick
        // Return: bool
        // -------------------------------------------------------------   
        bool on_event(const JoyStickEvent& event) {
            if (event.state() == JoyStickEvent::PRESSED) {
                m_parent->finish();
                return true;
            } else {
                // Nothing to do
            }

            return false;
        }

        // -------------------------------------------------------------  
        // Function: update_self()  
        // Description: 
        // Parameters:
        //      unsigned long elapsed;     
        // Return: void
        // -------------------------------------------------------------   
        void update_self(unsigned long elapsed) {
            if (not m_start) {
                m_start = elapsed;
            } else {
                // Nothing to do
            }

            unsigned long now = elapsed - m_start;

            if (now <= m_in) {
                unsigned char a = (255 * (100 - (100*now)/m_in))/100;
                m_fad.set_a(a);

            } else if (now >= m_out) {
                unsigned char a = (255 * (100*(now - m_out))/m_in)/100;
                m_fad.set_a(a);

            } else {
                m_fad.set_a(0);

            }

            if (now > m_duration) {
                m_parent->finish();
            } else {
                // NOthing to do
            }

            Environment *env = Environment::get_instance();

            m_x = (env->camera->w() - m_texture->w())/2 + env->camera->x();
            m_y = (env->camera->h() - m_texture->h())/2 + env->camera->y();
        }

        // -------------------------------------------------------------  
        // Function: draw_self()  
        // Description: Clear and selfs draw the background.
        // Return: void
        // -------------------------------------------------------------   
        void draw_self() {
            Environment *env = Environment::get_instance();

            env->canvas->clear(m_background);
            env->canvas->draw(m_texture.get(), m_x, m_y);

            env->canvas->set_blend_mode(Canvas::BLEND);
            Rect r { 0, 0, (double) env->canvas->w(), (double) env->canvas->h() };
            env->canvas->fill(r, m_fad);
            env->canvas->set_blend_mode(Canvas::NONE);
        }

    private:
        Level *m_parent;
        shared_ptr<Texture> m_texture;
        Color m_background, m_fad;
        unsigned long m_start, m_duration;
        unsigned long m_in, m_out;
        int m_x, m_y;
};

// -------------------------------------------------------------  
// Function: FrontEnd()  
// Description: Set the FrontEnd.
// Parameters:
//      const string& id;           I
//      const string& next;         
//      const string& texture;      
//      unsigned long duration;     Duration of FrontEnd.
//      const Color& bg;            Color of FrontEnd.
// -------------------------------------------------------------   
FrontEnd::FrontEnd(const string& id, const string& next, const string& texture,
                   unsigned long duration, const Color& bg)
                   : Level(id, next), m_impl(new Impl(this, texture, duration,
                   bg)) {
    Environment *env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

// -------------------------------------------------------------  
// Function: ~FrontEnd()  
// Description: Destructor of FrontEnd.
// -------------------------------------------------------------   
FrontEnd::~FrontEnd() {
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_listener(this);
}

// -------------------------------------------------------------  
// Function: draw_self()  
// Description: Selfs draw the FrontEnd.
// -------------------------------------------------------------   
void FrontEnd::draw_self() {
    m_impl->draw_self();
}

// -------------------------------------------------------------  
// Function: update_self()  
// Description: 
// Parameters:
//      unsigned long elapsed;     
// -------------------------------------------------------------   
void FrontEnd::update_self(unsigned long elapsed) {
    m_impl->update_self(elapsed);
}

// -------------------------------------------------------------  
// Function: on_event()  
// Description: Return a event in the impl according to the 
//              action on mouse button.
// Parameters:
//      const MouseButtonEvent& event;     Mouse button related 
//                                         event.
// Return: m_impl->on_event
// -------------------------------------------------------------   
bool FrontEnd::on_event(const MouseButtonEvent& event) {
    return m_impl->on_event(event);
}

// -------------------------------------------------------------  
// Function: on_event()  
// Description: Return a event in the impl according to the 
//              action on JoyStick.
// Parameters:
//      const JoyStickEvent& event;     JOyStick related event.
// Return: m_impl->on_event
// -------------------------------------------------------------   
bool FrontEnd::on_event(const JoyStickEvent& event) {
    return m_impl->on_event(event);
}

// -------------------------------------------------------------  
// Function: on_event()  
// Description: Return a event in the impl according to the 
//              action on keyboard.
// Parameters:
//      const KeyboardEvent& event;     Keyboard related event.
// Return: m_impl->on_event
// -------------------------------------------------------------   
bool FrontEnd::on_event(const KeyboardEvent& event) {
    return m_impl->on_event(event);
}