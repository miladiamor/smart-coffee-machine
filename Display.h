#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display
{
public:
    virtual ~Display() = default;

    virtual void displayFrame() = 0;               // Display something (can be more complex later)
    virtual void showWarning(const std::string& message) = 0; // Show warnings like "Wasser leer!" etc.
};

#endif // DISPLAY_H
