#include "core/camera.h"
#include "core/environment.h"
#include "core/video.h"

static Environment *env = nullptr;

// -------------------------------------------------------------  
// Function: Environment()  
// Description: Implements the environment.
// -------------------------------------------------------------   
Environment::Environment()
    : video(nullptr), resources_manager(nullptr), events_manager(nullptr),
    audio_manager(nullptr), canvas(nullptr), camera(nullptr), music(nullptr),
    sfx(nullptr), m_settings_path("") {
}

// -------------------------------------------------------------  
// Function: ~Environment()  
// Description: Destructor of environment.
// -------------------------------------------------------------   
Environment::~Environment() {
    delete audio_manager;
    delete events_manager;
    delete resources_manager;
    delete video;
}

// -------------------------------------------------------------  
// Function: Environment::get_instance()  
// Description: Escrever aqui.
// Return: Environment *
// -------------------------------------------------------------   
Environment * Environment::get_instance() throw (Exception) {
    if (not env) {
            env = new Environment();

            if (not env) {
                throw Exception("Out of memory for a new Environment");
            } else {
                // Nothing to
            }

            env->init();
    } else {
        // Nothing to do
    }

    return env;
}


// -------------------------------------------------------------  
// Function: release_instance()  
// Description: Escrever aqui.
// Return: void
// -------------------------------------------------------------   
void Environment::release_instance() {
    delete env;
    env = nullptr;
}

// -------------------------------------------------------------  
// Function: init()  
// Description: Escrever aqui.
// Return: void
// -------------------------------------------------------------   
void Environment::init() throw (Exception) {
    video = new Video();

    if (not video) {
        throw Exception("Out of memory for a new Video");
    } else {
        // Nothing to do
    }

    video->init();
    
    canvas = video->canvas();
    camera = video->camera();

    resources_manager = new ResourcesManager();

    if (not resources_manager) {
        throw Exception("Out of memory for a new ResourcesManager");
    } else {
        // Nothing to do
    }

    events_manager = new EventsManager();

    if (not events_manager) {
        throw Exception("Out of memory for a new EventsManager");
    } else {
        //Nothing to do
    }

    audio_manager = new AudioManagerWrapper();

    if (not audio_manager) {
        throw Exception("Out of memory for a new AudioManagerSfx");
    } else {
        // Nothing to do
    }

    audio_manager->init();

    music = audio_manager->music();
    sfx = audio_manager->sfx();
}