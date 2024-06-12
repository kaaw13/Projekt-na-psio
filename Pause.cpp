#include "Pause.h"

/// CONSTRUCTOR AND DESTRUCTOR
Pause::Pause() : paused(false) {}
Pause::~Pause() {}

/// GETTERS
bool Pause::isPaused() const {
    return paused;
}

/// FUNCTIONS

//pauzowanie
void Pause::pause() {
    
        paused = true;
        std::cout << "Pauza" << std::endl;
   
}
//odpauzowanie
void Pause::resume() {
  
        paused = false;
        std::cout << "Wznowienie" << std::endl;
    
    
}



