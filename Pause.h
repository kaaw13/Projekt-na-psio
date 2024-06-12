#pragma once

#include <iostream>

class Pause
{
private:
    bool paused;
    

public:
    Pause();
    ~Pause();

    void pause();
    void resume();
    

    bool isPaused() const;
    
};


