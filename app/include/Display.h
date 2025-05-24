@#pragma once
#include <string>

class Display
{
public:
    virtual ~Display() = default;

    virtual void displayFrame() = 0;
    virtual void showWarning(const std::string& message) = 0;
};

