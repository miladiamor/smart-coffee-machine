#ifndef PROGRAMMSTEUERUNG_H
#define PROGRAMMSTEUERUNG_H

class Programmsteuerung {

    private:
        int status;
        int kaffeeprogramm;
        Heizregler *temp_regler;
        Zuckerdispenser *zucker;
        Schaeumer *milchschaeumen;
        Brühgruppe *brühgruppe;
        Pumpsteuerung *steuerung;
        Fuelstandmessung *messung;

    public:
        Programmsteuerung();
        void ausfuehren(int programm);
};

#endif // PROGRAMMSTEUERUNG_H