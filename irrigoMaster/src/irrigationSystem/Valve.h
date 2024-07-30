#ifndef VALVE_H
#define VALVE_H

class Valve
{
public:
    Valve();
    // Assuming some methods for Valve class
    void open();
    void close();
    Valve &operator=(const Valve &other); // Copy assignment operator
};

#endif // VALVE_H