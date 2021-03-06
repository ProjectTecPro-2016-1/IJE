#include "core/game.h"
#include "core/video.h"
#include "core/environment.h"
#include "core/systemevent.h"
#include "core/keyboardevent.h"
#include "core/settings.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Game::Game(const string& id) : m_id(id), m_level(nullptr), m_done(false){
    env = Environment::get_instance();
}

Game::~Game() {
    if (m_level) {
        delete m_level;
    }

    env->events_manager->unregister_listener(this);
    Environment::release_instance();
}

void Game::init(const string& title, int w, int h, double scale, bool fullscreen, int volume)
                throw (Exception) {
    env->video->set_resolution(w, h, scale);
    env->video->set_window_name(title);
    env->video->set_fullscreen(fullscreen);
    env->music->set_volume(volume);
    env->sfx->set_volume(volume);

    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

    if (SDL_NumJoysticks() > 0) {
        SDL_GameControllerOpen(0);
    }

    env->events_manager->register_listener(this);
    m_level = load_level(m_id);
}

void Game::init(const string& path) throw (Exception) {
    env->m_settings_path = path;

    shared_ptr<Settings> settings = env->resources_manager->get_settings(path);

    string title = settings->read<string>("Game", "title", "Test Game");
    int w = settings->read<int>("Game", "w", 800);
    int h = settings->read<int>("Game", "h", 600);
    double scale = settings->read<double>("Game", "scale", 1);
    bool fullscreen = settings->read<bool>("Game", "fullscreen", false);
    int volume = settings->read<int>("Game", "volume", 50);

    init(title, w, h, scale, fullscreen, volume);
}

void Game::run() {
    while (m_level and not m_done) {
        unsigned long now = update_timestep();
        env->events_manager->dispatch_pending_events();

        m_level->update(now);
        env->camera->update(now);

        m_level->draw();
        update_screen();
        delay(1);

        if (m_level->finished()) {
            string next = m_level->next();
            delete m_level;
            m_level = load_level(next);
        }
    }
}

unsigned long Game::update_timestep() const {
    return SDL_GetTicks();
}

bool Game::on_event(const SystemEvent& event) {
    if (event.type() == SystemEvent::QUIT) {
        m_done = true;
        return true;
    }

    return false;
}

bool Game::on_event(const KeyboardEvent& event) {
    if (event.state() == KeyboardEvent::PRESSED and event.key() == KeyboardEvent::ESCAPE) {
        m_done = true;
        return true;
    }

    return false;
}

void Game::update_screen() {
    Environment *env = Environment::get_instance();
    env->canvas->update();
}

void Game::delay(unsigned long ms) {
    SDL_Delay(ms);
}

Level * Game::load_level(const string&) {
    return nullptr;
}
