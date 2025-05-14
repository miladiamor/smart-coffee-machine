#include "bruehgruppe.h"

Bruehgruppe::Bruehgruppe() :
    tropfstopfventil(new Ventil), wasserzufuhr(new Ventil), kaffeezufuhr(new Ventil),
    entleerklappe(new Klappe),
    stampfer(new Kolbenmotor),
    inkrementalencoder(new Inkrementalencoder(stampfer)) {}
