#include "Pause.h"

Pause::Pause() : paused(false) {}

Pause::~Pause() {}
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



bool Pause::isPaused() const {
    return paused;
}


