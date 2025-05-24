#include "Ressourcen.h"

void Ressourcen::setWassermenge_ml(int ml) { wassermenge_ml = ml; }
void Ressourcen::setMilchmenge_ml(int ml) { milchmenge_ml = ml; }
void Ressourcen::setKaffeemenge_g(int g) { kaffeemenge_g = g; }
void Ressourcen::setZuckermenge_TL(short tl) { zuckermenge_TL = tl; }
void Ressourcen::setRestkaffee_g(int g) { restkaffee_g = g; }

int Ressourcen::getWassermenge_ml() const { return wassermenge_ml; }
int Ressourcen::getMilchmenge_ml() const { return milchmenge_ml; }
int Ressourcen::getKaffeemenge_g() const { return kaffeemenge_g; }
short Ressourcen::getZuckermenge_TL() const { return zuckermenge_TL; }
int Ressourcen::getRestkaffee_g() const { return restkaffee_g; }

void Ressourcen::reset() {
    wassermenge_ml = 0;
    milchmenge_ml = 0;
    kaffeemenge_g = 0;
    zuckermenge_TL = 0;
    restkaffee_g = 0;
}
