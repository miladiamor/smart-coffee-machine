#pragma once

class Heizelemente {

private:
    bool eingeschaltet;

public:
    Heizelemente();
    void einschalten();
    void ausschalten();
    bool istEingeschaltet() const;
};

