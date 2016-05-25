#include "core/level.h"

// -------------------------------------------------------------
// Function: Level
// Description: Class constructor
// Parameters:
//      const string& id;
//      const string& next = "";
// Return: void
// Observation: without implementation.
// -------------------------------------------------------------
Level::Level(const string& id, const string& next) : Object(nullptr, id), m_next(next),
                                                    m_done(false){
}


// -------------------------------------------------------------
// Function: next()
// Description: Function that returns class m_next attribute
// Return: string
// -------------------------------------------------------------
string Level::next() const {
    return m_next;
}

// -------------------------------------------------------------
// Function: finished()
// Description: Function that returns class attribute m_done attribute
// Return: bool
// -------------------------------------------------------------
bool Level::finished() const {
    return m_done;
}

// -------------------------------------------------------------
// Function: finish()
// Description: Function that sets class attribute m_done as true
// Return: void
// -------------------------------------------------------------
void Level::finish() {
    m_done = true;
}

// -------------------------------------------------------------
// Function: set_next()
// Description: Function that sets a value to class attribute m_next
// Parameters:
//      const string& next;     value that the attribute in question will receive.
// Return: void
// -------------------------------------------------------------
void Level::set_next(const string& next) {
    m_next = next;
}
