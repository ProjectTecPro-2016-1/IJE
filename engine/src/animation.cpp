// Class implementation Animation
// Author: Edson Alves
// Date: 05/05/2015
// Licence: LGPL. Sem copyright

#include "core/animation.h"
#include "core/rect.h"
#include "core/texture.h"
#include "core/environment.h"

class Animation::Impl {
public:
    Impl(const string& id, double x_, double y_, double w_, double h_, int f,
        unsigned long s, bool l_)
        : x(x_), y(y_), w(w_), h(h_), frames(f), speed(s), loop(l_),
        done(false), last(0), frame(0) {
        Environment * env = Environment::get_instance();
        texture = env->resources_manager->get_texture(id);
    }

    void reset() {
        last = frame = 0;
    }

    double x, y, w, h;
    int frames;
    unsigned long speed;
    bool loop, done;
    unsigned long last;
    int frame;
    shared_ptr<Texture> texture;
};

Animation::Animation(const string& texture, double x, double y, double w,
    double h, int frames, unsigned long speed_in_ms, bool loop)
    : m_impl(new Animation::Impl(texture, x, y, w, h, frames, speed_in_ms, loop)) {
}

Animation::~Animation() {
}

bool Animation::is_done() const {
    return m_impl->done;
}

void Animation::update(unsigned long elapsed) {
    if (not m_impl->last) {
        m_impl->last = elapsed;
    } else {
        // Nothing to do
    }

    if (elapsed - m_impl->last > m_impl->speed) {
        ++m_impl->frame;
        m_impl->last += m_impl->speed;

        if (m_impl->loop) {
            m_impl->frame %= m_impl->frames;
        } else if (m_impl->frame == m_impl->frames) {
            --m_impl->frame;
            m_impl->done = true;
        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }
}

void Animation::draw(double x, double y) {
    if (m_impl->done) {
        return;
    } else {
        // Nothing to do
    }

    Rect clip { m_impl->x + m_impl->frame * m_impl->w, m_impl->y, m_impl->w,
        m_impl->h
              };

    Environment *env = Environment::get_instance();
    env->canvas->draw(m_impl->texture.get(), clip, x, y, clip.w(), clip.h());
}

double Animation::w() const {
    return m_impl->w;
}

double Animation::h() const {
    return m_impl->h;
}

void Animation::set_row(int row) {
    int y = row * m_impl->h;

    if (m_impl->y != y) {
        m_impl->frame = 0;
    } else {
        // Nothing to do
    }

    m_impl->y = y;
}

void Animation::reset() {
    m_impl->reset();
}
