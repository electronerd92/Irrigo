#include "System.h"

// Initialize the static member
System* System::instance = nullptr;

System& System::getInstance() {
    if (instance == nullptr) {
        instance = new System();
    }
    return *instance;
}