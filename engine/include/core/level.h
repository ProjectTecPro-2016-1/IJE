#ifndef LEVEL_H
#define LEVEL_H

#include "object.h"
#include "environment.h"

#include <string>

using std::string;

class Level : public Object {
public:
    Level(const string& id, const string& next = "");

    string next() const;
    bool finished() const;

    void finish();
    void set_next(const string& next);

private:
    string m_next;
    bool m_done;
};

#endif
