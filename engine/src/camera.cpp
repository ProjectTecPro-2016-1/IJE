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

// -------------------------------------------------------------
// Function: set_mode();
// Description:
// Parameters:
//      Mode mode;        Description
//
// Return: void
// -------------------------------------------------------------
    void set_mode(Mode mode) {
        m_mode = mode;
    }

// -------------------------------------------------------------
// Function: follow();
// Description:
// Parameters:
//      const Object * target;        Description
//
// Return: void
// -------------------------------------------------------------
    void follow(const Object * target) {
        m_target = target;
    }

// -------------------------------------------------------------
// Function: update_self();
// Description:
// Parameters:
//      unsigned long;        Description
//
// Return: void
// -------------------------------------------------------------
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

// -------------------------------------------------------------
// Function: draw_self();
// Description:
//
// Return: void
// -------------------------------------------------------------
    void draw_self() {
    }

// -------------------------------------------------------------
// Function: set_limits();
// Description:
// Parameters:
//      const Rect& limits;        Description
//
// Return: void
// -------------------------------------------------------------
    void set_limits(const Rect& limits) {
        m_limits = limits;
    }

private:
    Camera * m_camera;
    Mode m_mode;
    const Object * m_target;
    Rect m_limits;
};

// -------------------------------------------------------------
// Function: Camera();
// Description: Camera class builder where the initializations os the variables happnen;
// Parameters:
//      double x;        Description
//      double y;
//      double w;
//      double h;
//      Mode mode;
//
// Return: void
// -------------------------------------------------------------
Camera::Camera(double x, double y, double w, double h, Mode mode)
    : Object(nullptr, "", x, y, w, h), m_impl(new Camera::Impl(this, mode)) {
}

// -------------------------------------------------------------
// Function: ~Camera();
// Description: Camera class destructor in which images files free themselves;
//
// Return: void
// -------------------------------------------------------------
Camera::~Camera() {
}

Camera::Mode Camera::mode() const {
    return m_impl->mode();
}

// -------------------------------------------------------------
// Function: set_mode()
// Description:
// Parameters:
//      Mode mode;        Description
//
// Return: void
// -------------------------------------------------------------
void Camera::set_mode(Mode mode) {
    m_impl->set_mode(mode);
}

// -------------------------------------------------------------
// Function: update_self();
// Description:
// Parameters:
//      unsigned long elapsed;        Description
//
// Return: void
// -------------------------------------------------------------
void Camera::update_self(unsigned long elapsed) {
    m_impl->update_self(elapsed);
}

// -------------------------------------------------------------
// Function: draw_self();
// Description:
//
// Return: void
// -------------------------------------------------------------
void Camera::draw_self() {
    m_impl->draw_self();
}

// -------------------------------------------------------------
// Function: follow();
// Description:
// Parameters:
//      const Object * object;        Description
//
// Return: void
// -------------------------------------------------------------
void Camera::follow(const Object * object) {
    m_impl->follow(object);
}

// -------------------------------------------------------------
// Function: set_limits();
// Description:
// Parameters:
//      const Rect& limits;        Description
//
// Return: void
// -------------------------------------------------------------
void Camera::set_limits(const Rect& limits) {
    m_impl->set_limits(limits);
}
