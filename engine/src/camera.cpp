// Class implementation Camera
// Author: Edson Alves
// Date: 27/05/2015
// Licence: LGPL. Sem copyright

#include "core/camera.h"
#include "core/rect.h"
#include <iostream>

using namespace std;

class Camera::Impl {
public:
    Impl(Camera * camera, Mode mode)
        : m_camera(camera), m_mode(mode), m_target(nullptr),
        m_limits(-1000000, -1000000, 2000000, 2000000) {
        }

    Mode mode() const {
        return m_mode;
    }

    void set_mode(Mode mode) {
        m_mode = mode;
    }

    void follow(const Object * target) {
        m_target = target;
    }

    void update_self(unsigned long) {
        if (m_mode == Camera::FOLLOWING and m_target) {
            double x = m_target->x() + (m_target->w() - m_camera->w()) / 2;
            double y = m_target->y() + (m_target->h() - m_camera->h()) / 2;

            if (x < m_limits.x()) {
                x = m_limits.x();
            } else {
                // Nothing to do
            }

            if (x + m_camera->w() > m_limits.x() + m_limits.w()) {
                x = m_limits.x() + m_limits.w() - m_camera->w();
            } else {
                // Nothing to do
            }

            if (y < m_limits.y()) {
                y = m_limits.y();
            } else {
                // Nothing to do
            }

            if (y + m_camera->h() > m_limits.y() + m_limits.h()) {
                y = m_limits.y() + m_limits.h() - m_camera->h();
            } else {
                // Nothing to do
            }

            m_camera->set_position(x, y);
        } else {
            // Nothing to do
        }
    }

    void draw_self() {
    }

    void set_limits(const Rect& limits) {
        m_limits = limits;
    }

private:
    Camera * m_camera;
    Mode m_mode;
    const Object * m_target;
    Rect m_limits;
};

Camera::Camera(double x, double y, double w, double h, Mode mode)
    : Object(nullptr, "", x, y, w, h), m_impl(new Camera::Impl(this, mode)) {
}

Camera::~Camera() {
}

Camera::Mode Camera::mode() const {
    return m_impl->mode();
}

void Camera::set_mode(Mode mode) {
    m_impl->set_mode(mode);
}

void Camera::update_self(unsigned long elapsed) {
    m_impl->update_self(elapsed);
}

void Camera::draw_self() {
    m_impl->draw_self();
}

void Camera::follow(const Object * object) {
    m_impl->follow(object);
}

void Camera::set_limits(const Rect& limits) {
    m_impl->set_limits(limits);
}
