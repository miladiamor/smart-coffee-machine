#pragma once

class Heizelemente {

private:
    bool eingeschaltet;

public:
    Heizelemente(): eingeschaltet(false) {}
    void einschalten();
    void ausschalten();
    bool istEingeschaltet() const;
};

