#include "core/eventsmanager.h"
#include "core/joystickevent.h"
#include "core/listener.h"
#include "core/keyboardevent.h"
#include "core/mousebuttonevent.h"
#include "core/mousemotionevent.h"
#include "core/systemevent.h"
#include <list>

using std::list;

// -------------------------------------------------------------  
// Function: grab_SDL_events()  
// Description: Creates a list of events and returns 1 if there 
//              are pending events and 0 if there are no pending 
//              events.
// Return: list<SDL_Event>
// -------------------------------------------------------------   
list<SDL_Event> grab_SDL_events() {
    SDL_Event event;
    list<SDL_Event> events;

    while (SDL_PollEvent(&event)) {
        events.push_back(event);
    }

    return events;
}

class EventsManager::Impl {
    public:
        
        // -------------------------------------------------------------  
        // Function: Impl()  
        // Observations:
        //      Funtion not implemented
        // -------------------------------------------------------------  
        Impl() {}
        
        // -------------------------------------------------------------  
        // Function: ~Impl()  
        // Observations:
        //      Funtion not implemented
        // -------------------------------------------------------------
        ~Impl() {}

        // -------------------------------------------------------------  
        // Function: register_listener()  
        // Description: Checks the status of listener and logs an event.
        // Parameters:
        //      Listener *listener;     A listener that record actions
        //                              from user.
        // Return: void
        // -------------------------------------------------------------  
        void register_listener(Listener *listener) {
            if (listener) {
                m_listeners.push_back(listener);
            } else {
                // Nothing to do
            }
        }

        // -------------------------------------------------------------  
        // Function: unregister_listener()  
        // Description: Checks the status of listener and remove an event. 
        // Parameters:
        //      Listener *listener;     A listener that record actions
        //                              from user.
        // Return: void
        // -------------------------------------------------------------  
        void unregister_listener(Listener *listener) {
            m_listeners.remove(listener);
        }

        // -------------------------------------------------------------  
        // Function: dispatch_pending_events()
        // Description: Treats pendinfg events from actions made by user.
        // Return: void
        // -------------------------------------------------------------  
        void dispatch_pending_events() {
            list<SDL_Event> events = grab_SDL_events();

            for (auto e : events) {
                switch (e.type) {
                    case SDL_QUIT: {
                        SystemEvent se = SystemEvent::from_SDL(e);

                        for (auto ls : m_listeners) {
                            if (ls->active() and ls->on_event(se)) {
                                break;
                            } else {
                                // Nothing to do
                            }
                        }

                        break;
                    }

                    case SDL_MOUSEMOTION: {
                        MouseMotionEvent me = MouseMotionEvent::from_SDL(e);

                        for (auto ls : m_listeners) {
                            if (ls->active() and ls->on_event(me)) {
                                break;
                            } else {
                                // Nothing to do
                            }
                        }

                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN:
                        // Nothing to do
                    case SDL_MOUSEBUTTONUP: {
                        MouseButtonEvent me = MouseButtonEvent::from_SDL(e);

                        for (auto ls : m_listeners) {
                            if (ls->active() and ls->on_event(me)) {
                                break;
                            } else {
                                // Nothing to do
                            }
                        }

                        break;
                    }

                    case SDL_KEYDOWN:
                        // Nothing to do
                    case SDL_KEYUP: {
                        if (e.key.repeat != 0) {
                            break;
                        } else {
                            // Nothing to do
                        }

                        KeyboardEvent ke = KeyboardEvent::from_SDL(e);

                        for (auto ls : m_listeners) {
                            if (ls->active() and ls->on_event(ke)) {
                                break;
                            } else {
                                // Nothing to do
                            }
                        }

                        break;
                    }

                    case SDL_CONTROLLERBUTTONDOWN:
                        // Nothing to do
                    case SDL_CONTROLLERBUTTONUP: {
                        JoyStickEvent je = JoyStickEvent::from_SDL(e);

                        for (auto ls : m_listeners) {
                            if (ls->active() and ls->on_event(je)) {
                                break;
                            } else {
                                // Nothing to do
                            }
                        }

                        break;
                    }
                }
            }
        }

    private:
        list<Listener *> m_listeners;
};

// -------------------------------------------------------------  
// Function: EventsManager()
// Description: Implements de EventsManager.
// -------------------------------------------------------------  
EventsManager::EventsManager()
    : m_impl(new Impl()){
}

// -------------------------------------------------------------  
// Function: ~EventsManager
// Observations:
//      Funtion not implemented        
// -------------------------------------------------------------   
EventsManager::~EventsManager() {
}

// -------------------------------------------------------------  
// Function: dispatch_pending_events()  
// Description: Set the pending events.
// Return: void
// -------------------------------------------------------------  
void EventsManager::dispatch_pending_events() {
    m_impl->dispatch_pending_events();
}

// -------------------------------------------------------------  
// Function: register_listener()  
// Description: Set the register listener.
// Parameters:
//      Listener *listener;     A listener that record actions
//                              from user.
// Return: void
// -------------------------------------------------------------  
void EventsManager::register_listener(Listener *listener) {
    m_impl->register_listener(listener);
}

// -------------------------------------------------------------  
// Function: unregister_listener()  
// Description: Set the unregister listener.
// Parameters:
//      Listener *listener;     A listener that record actions
//                              from user.
// Return: void
// ------------------------------------------------------------- 
void EventsManager::unregister_listener(Listener *listener) {
    m_impl->unregister_listener(listener);
}