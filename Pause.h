#pragma once

#include <iostream>

class Pause
{
private:
    // VARIABLES
    bool paused;  

public:
    // CONSTRUCTORS AND DESTRUCTORS
    Pause();
    ~Pause();

    // GETTERS
    bool isPaused() const;  

    // FUNCTIONS
    void pause();
    void resume();

};


