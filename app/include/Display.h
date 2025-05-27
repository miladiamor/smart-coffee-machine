// Display.h
#pragma once
#include <string>
#include "Position.h"

class Display
{
public:
    virtual ~Display() = default;

    virtual void displayFrame() = 0;
    virtual void showWarning(const std::string& message) = 0;
    virtual Position getTouchEvent() = 0;
};
