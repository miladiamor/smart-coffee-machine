#pragma once

enum class TankTyp { wasser, milch, kaffee, zucker, restkaffee };

inline const char* toString(TankTyp typ) {
    switch (typ) {
    case TankTyp::wasser: return "Wasser";
    case TankTyp::milch: return "Milch";
    case TankTyp::kaffee: return "Kaffee";
    case TankTyp::zucker: return "Zucker";
    case TankTyp::restkaffee: return "Restkaffee";
    default: return "Unbekannt";
    }
}
