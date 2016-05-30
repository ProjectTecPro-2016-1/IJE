 // Class implementation Button
 // Author: Edson Alves
 // Date: 29/04/2015
 // Licence: LGPL. Sem copyright

#include "core/color.h"
#include "core/rect.h"
#include "core/text.h"
#include "core/texture.h"
#include "util/button.h"
#include "core/environment.h"
#include "core/mousebuttonevent.h"
#include "core/mousemotionevent.h"
#include <cstdio>

class Button::Impl {
public:
    typedef enum { IDLE, ACTIVE } State;

    Impl(Button * button)
        : m_button(button), m_text(nullptr), m_idle(Color::GREEN),
        m_active(Color::BLUE), m_border(Color::BLACK), m_thickness(1),
        m_state(IDLE), m_idle_texture(nullptr), m_active_texture(nullptr) {
    }

// -------------------------------------------------------------
// Function: Impl()
// Description: Impl class builder where the initializations of the variables happen.
// Parameters:
//      Button * button;        Description
//      const string& idle_image_id;
//      const string& active_image_id;
//
// Return: void
// -------------------------------------------------------------
    Impl(Button * button, const string& idle_image_id,
        const string& active_image_id)
        : m_button(button), m_text(nullptr), m_idle(Color::GREEN),
        m_active(Color::BLUE), m_border(Color::BLACK), m_thickness(1),
        m_state(IDLE) {
        Environment * env = Environment::get_instance();

        m_idle_texture = env->resources_manager->get_texture(idle_image_id);
        m_active_texture = env->resources_manager->get_texture(active_image_id);

        m_button->set_position(0.0, 0.0);
        m_button->set_dimensions(m_idle_texture->w(), m_idle_texture->h());
    }

// -------------------------------------------------------------
// Function: ~Impl()
// Description: Impl class destructor in which images files free themselves.
//
// Return: void
// -------------------------------------------------------------
    ~Impl() {
        delete m_text;
    }

// -------------------------------------------------------------
// Function: set_text()
// Description:
// Parameters:
//      const string& text;        Description
//      const Color& color;
//
// Return: void
// -------------------------------------------------------------
    void set_text(const string& text, const Color& color) {
        if (text.size() > 0) {
            delete m_text;
            m_text = new Text(m_button, text, color);
        } else {
            // Nothing to do
        }
    }

// -------------------------------------------------------------
// Function: set_color()
// Description:
// Parameters:
//      const Color& idle;        Description
//      const Color& active;
//
// Return: void
// -------------------------------------------------------------
    void set_color(const Color& idle, const Color& active) {
        m_idle = idle;
        m_active = active;
    }

// -------------------------------------------------------------
// Function: set_border()
// Description:
// Parameters:
//      int thickness;        Description
//      const Color& color;
//
// Return: void
// -------------------------------------------------------------
    void set_border(int thickness, const Color& color) {
        m_border = color;
        m_thickness = thickness;
    }

// -------------------------------------------------------------
// Function: on_event()
// Description:
// Parameters:
//      const MouseButtonEvent& event;        Description
//
// Return: bool
// -------------------------------------------------------------
    bool on_event(const MouseButtonEvent& event) {
        if (event.state() == MouseButtonEvent::PRESSED and
            event.button() == MouseButtonEvent::LEFT and
            m_button->bounding_box().contains(event.x(), event.y())) {
            char coords[64];
            sprintf(coords, "%.2f, %.2f", event.x(), event.y());
            m_button->notify(clickedID, coords);

            return true;
        } else {
            // Nothing to do
        }

        return false;
    }

// -------------------------------------------------------------
// Function: on_event()
// Description:
// Parameters:
//      const MouseMotionEvent& event        Description
//
// Return: bool
// -------------------------------------------------------------
    bool on_event(const MouseMotionEvent& event) {
        if (m_button->bounding_box().contains(event.x(), event.y())) {
            m_state = ACTIVE;

            if (m_active_texture.get()) {
                m_button->set_dimensions(m_active_texture->w(), m_active_texture->h());
            } else {
                // Nothing to do
            }

            return true;
        } else  {
            m_state = IDLE;

            if (m_idle_texture.get()) {
                m_button->set_dimensions(m_idle_texture->w(), m_idle_texture->h());
            } else {
                // Nothing to do
            }
        }

        return false;
    }

// -------------------------------------------------------------
// Function: draw_self()
// Description:
//
// Return: void
// -------------------------------------------------------------
    void draw_self() {
        Environment * env = Environment::get_instance();
        shared_ptr<Texture> image;
        Color color;

        switch (m_state) {
        case IDLE:
            image = m_idle_texture;
            color = m_idle;
            break;

        case ACTIVE:
            image = m_active_texture;
            color = m_active;
            break;

        default:
            // Nothing to do
            break;
        }

        if (image.get()) {
            env->canvas->draw(image.get(), m_button->x(), m_button->y());
        } else {
            env->canvas->set_blend_mode(Canvas::BLEND);

            Rect r = m_button->bounding_box();

            for (int i = 0; i < m_thickness; ++i) {
                env->canvas->draw(r, m_border);

                r.set_position(r.x() + 1, r.y() + 1);
                r.set_dimensions(r.w() - 2, r.h() - 2);
            }

            env->canvas->fill(r, color);
            env->canvas->set_blend_mode(Canvas::NONE);
        }

        if (m_text) {
            m_text->align_to(m_button, Object::CENTER, Object::MIDDLE);
            m_text->draw();
        } else {
            // Nothing to do
        }
    }

private:
    Button * m_button;
    Text * m_text;
    Color m_idle, m_active, m_border;
    int m_thickness;
    State m_state;
    shared_ptr<Texture> m_idle_texture, m_active_texture;
};

ActionID Button::clickedID = "clicked()";

Button::Button(Object * parent, ObjectID id, double w, double h)
    : Object(parent, id, 0, 0, w, h), m_impl(new Impl(this)) {
    Environment * env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

// -------------------------------------------------------------
// Function: Button()
// Description: Button class builder where the initializations os the variables happen.
// Parameters:
//      Object * parent;        Description
//      ObjectID id;
//      const string& idle_image_id;
//      const string& active_image_id;
//
// Return: void
// -------------------------------------------------------------
Button::Button(Object * parent, ObjectID id, const string& idle_image_id,
    const string& active_image_id)
    : Object(parent, id), m_impl(new Impl(this, idle_image_id, active_image_id)) {
    Environment * env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

// -------------------------------------------------------------
// Function: ~Button()
// Description: Button class destructor in which images files free themselves.
//
// Return: void
// -------------------------------------------------------------
Button::~Button() {
    Environment * env = Environment::get_instance();
    env->events_manager->unregister_listener(this);
}

// -------------------------------------------------------------
// Function: draw_self()
// Description:
//
// Return: void
// -------------------------------------------------------------
void Button::draw_self() {
    m_impl->draw_self();
}

// -------------------------------------------------------------
// Function: on_event()
// Description:
// Parameters:
//      const MouseButtonEvent& event;        Description
//
// Return: bool
// -------------------------------------------------------------
bool Button::on_event(const MouseButtonEvent& event) {
    return m_impl->on_event(event);
}

// -------------------------------------------------------------
// Function: set_text();
// Description:
// Parameters:
//      const strung& text;        Description
//      const Color& color;
//
// Return: void
// -------------------------------------------------------------
void Button::set_text(const string& text, const Color& color) {
    return m_impl->set_text(text, color);
}

// -------------------------------------------------------------
// Function: set_color();
// Description:
// Parameters:
//      const Color& idle;        Description
//      const Color& active;
//
// Return: void
// -------------------------------------------------------------
void Button::set_color(const Color& idle, const Color& active) {
    return m_impl->set_color(idle, active);
}

// -------------------------------------------------------------
// Function: set_border();
// Description:
// Parameters:
//      int thickness;        Description
//      const Color& color;
//
// Return: void
// -------------------------------------------------------------
void Button::set_border(int thickness, const Color& color) {
    return m_impl->set_border(thickness, color);
}
