#pragma once

enum class TankTyp {
    wasser,
    milch,
    kaffee,
    zucker,
    restkaffee
};


const char* toString(TankTyp typ);
