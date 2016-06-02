#include "core/video.h"
#include "core/camera.h"
#include "core/canvas.h"
#include "core/environment.h"
#include <SDL2/SDL_ttf.h>

using std::make_pair;

Video::Video()
    : m_window(nullptr), m_renderer(nullptr), m_canvas(nullptr),
    m_camera(nullptr), m_w(800), m_h(600) {
}

Video::~Video() {
    if (m_camera) {
        delete m_camera;
    } else {
        // Nothing to do
    }

    if (m_canvas) {
        delete m_canvas;
    } else {
        // Nothing to do
    }

    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
    } else {
        // Nothing to do
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
    } else {
        // Nothing to do
    }

    if (TTF_WasInit()) {
        TTF_Quit();
    } else {
        // Nothing to do
    }

    if (SDL_WasInit(SDL_INIT_EVERYTHING)) {
        SDL_Quit();
    } else {
        // Nothing to do
    }
}

void Video::init() throw (Exception) {
    int rc = SDL_Init(SDL_INIT_VIDEO);

    if (rc) {
        throw Exception(SDL_GetError());
    } else {
        // Nothing to do
    }

    rc = TTF_Init();

    if (rc) {
        throw Exception(TTF_GetError());
    } else {
        // Nothing to do
    }

    rc = SDL_CreateWindowAndRenderer(m_w, m_h, 0, &m_window, &m_renderer);

    if (rc or not m_window or not m_renderer) {
        throw Exception(SDL_GetError());
    } else {
        // Nothing to do
    }

    m_canvas = new Canvas(m_renderer, m_w, m_h);

    if (not m_canvas) {
        throw Exception("Out of memory for a new Canvas");
    } else {
        // Nothing to do
    }

    m_camera = new Camera(0, 0, m_w, m_h);

    if (not m_camera) {
        throw Exception("Out of memory for a new Camera");
    } else {
        // Nothing to do
    }
}

void Video::set_resolution(int w, int h, double scale) throw (Exception) {
    if (m_window and w > 0 and h > 0) {
        m_w = w;
        m_h = h;
        SDL_SetWindowSize(m_window, w, h);

        int rc = SDL_RenderSetLogicalSize(m_renderer, m_w, m_h);

        if (rc != 0) {
            throw Exception(SDL_GetError());
        } else {
            // Nothing to do
        }

        m_canvas->set_resolution(w, h);
        m_camera->set_dimensions(w, h);

        Environment *env = Environment::get_instance();
        env->resources_manager->scale(scale);
    } else {
        // Nothing to do
    }
}

void Video::set_fullscreen(bool fullscreen) throw (Exception) {
    if (not m_window) {
        return;
    } else {
        // Nothing to do
    }

    int flag = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

    int rc = SDL_SetWindowFullscreen(m_window, flag);

    if (rc != 0) {
        throw Exception(SDL_GetError());
    } else {
        // Nothing to do
    }
}

bool Video::fullscreen() const {
    int flag = SDL_GetWindowFlags(m_window);

    if (flag & SDL_WINDOW_FULLSCREEN) {
        return true;
    } else {
        // Nothing to do
    }

    return false;
}

void Video::set_window_name(const string& name) {
    if (m_window) {
        SDL_SetWindowTitle(m_window, name.c_str());
    } else {
        // Nothing to do
    }
}

pair<int, int> Video::resolution() const {
    return make_pair(m_w, m_h);
}

Canvas * Video::canvas() const {
    return m_canvas;
}

Camera * Video::camera() const {
    return m_camera;
}