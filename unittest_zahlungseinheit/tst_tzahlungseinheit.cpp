#include <QtTest>
#include <QObject>
#include <QPointF>

#include "zahlungseinheit.h"
#include "produkt.h"
#include "muenzroehre.h"
#include "muenzenschieber.h"
#include "muenzroehrenspeicher.h"
#include "muenzeingabesensor.h"
#include "muenzauswerfer.h"


// === GLOBALE FLAGS FÜR TEST-VERIFIKATION ===
float lastEingeworfeneMuenze = 0.0f;
bool wurdeMuenzeAusgeworfen = false;
bool wurdeBetragAusgeworfen = false;
float zuletztAusgeworfenerBetrag = 0.0f;
float zuletztAusgeworfeneMuenze = 0.0f;

float zuletztEingefuegteMuenze = 0.0f;
bool muenzeWurdeAkzeptiert = true;

int produktDekrementiert = 0;
float letzterPreis = 0.0f;

// === MOCK MuenzAuswerfer ===
void MuenzAuswerfer::auswerfen(float betrag) {
    wurdeBetragAusgeworfen = true;
    zuletztAusgeworfenerBetrag = betrag;
}

void MuenzAuswerfer::auswerfenMuenze(float wert) {
    wurdeMuenzeAusgeworfen = true;
    zuletztAusgeworfeneMuenze = wert;
}




// === MOCK MuenzEingabeSensor ===
float gemockteMuenze = 0.0f;

MuenzEingabeSensor::MuenzEingabeSensor() {}

float MuenzEingabeSensor::getEingeworfeneMuenze() {
    return gemockteMuenze;
}

bool MuenzEingabeSensor::getMuenzeGueltig() {
    // Im echten Code würde hier geprüft, ob der Wert zu den erlaubten gehört.
    // Im Test: Immer gültig oder nach Bedarf anpassbar.
    return true;
}

// Hilfsfunktion zur Steuerung des Mockverhaltens im Test
void MuenzEingabeSensor::simuliereMuenze(float wert) {
    gemockteMuenze = wert;
}




// === MOCK Muenzenschieber ===
Muenzroehre* zuletztGeschobenesRohr = nullptr;

Muenzenschieber::Muenzenschieber() {}

void Muenzenschieber::schiebeMuenzeInRoehre(Muenzroehre* muenzroehre) {
    // Wir merken uns nur, welche Röhre zuletzt benutzt wurde
    zuletztGeschobenesRohr = muenzroehre;
}





// === MOCK Muenzroehre ===
float mockRohrWert = 0.0f;
int mockKapazitaet = 10;
int mockAnzahl = 0;
int mockErhoeheAnzahlCount = 0;

Muenzroehre::Muenzroehre(float wert, int kapazitaet) {
    mockRohrWert = wert;
    mockKapazitaet = kapazitaet;
    mockAnzahl = 0;
    mockErhoeheAnzahlCount = 0;
}

bool Muenzroehre::istVoll() const {
    return mockAnzahl >= mockKapazitaet;
}

void Muenzroehre::leeren() {
    mockAnzahl = 0;
}

int Muenzroehre::getAktuelleAnzahl() const {
    return mockAnzahl;
}

int Muenzroehre::getKapazitaet() const {
    return mockKapazitaet;
}

float Muenzroehre::getWert() const {
    return mockRohrWert;
}

void Muenzroehre::erhoeheAnzahl() {
    mockAnzahl++;
    mockErhoeheAnzahlCount++;
}






// === MOCK Muenzroehrenspeicher ===
bool mockMuenzeAkzeptiert = true;
float mockGesamtwert = 0.0f;
bool mockRoehrenspeicherLeerCalled = false;
float zuletztEingefuegteMuenze = 0.0f;

Muenzroehrenspeicher::Muenzroehrenspeicher(
    Muenzroehre*, Muenzroehre*, Muenzroehre*,
    Muenzroehre*, Muenzroehre*,
    Muenzenschieber*, MuenzAuswerfer*) {}

Muenzroehrenspeicher::Muenzroehrenspeicher() {}

bool Muenzroehrenspeicher::fuegeMuenzeEin(float wert) {
    zuletztEingefuegteMuenze = wert;
    return mockMuenzeAkzeptiert;
}

float Muenzroehrenspeicher::gesamtWert() const {
    return mockGesamtwert;
}

void Muenzroehrenspeicher::leeren() {
    mockRoehrenspeicherLeerCalled = true;
}




// === MOCK Produkt ===
float mockProduktPreis = 1.0f;
int mockProduktAnzahl = 1;
bool mockDekrementAufgerufen = false;
std::string mockProduktName = "MockProdukt";

Produkt::Produkt(std::string name, float preis, int anzahl) {
    mockProduktName = name;
    mockProduktPreis = preis;
    mockProduktAnzahl = anzahl;
    mockDekrementAufgerufen = false;
}

std::string Produkt::getName() const {
    return mockProduktName;
}

float Produkt::getPreis() const {
    return mockProduktPreis;
}

int Produkt::getAnzahl() const {
    return mockProduktAnzahl;
}

void Produkt::dekrementiereAnzahl() {
    mockDekrementAufgerufen = true;
    if (mockProduktAnzahl > 0)
        mockProduktAnzahl--;
}





// === MOCK Zahlungseinheit ===
bool mockZahlungGestartet = false;
Produkt* zuletztUebergebenesProdukt = nullptr;

Zahlungseinheit::Zahlungseinheit() {}

Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher*, MuenzEingabeSensor*, MuenzAuswerfer*) {}

bool Zahlungseinheit::versucheZahlung(Produkt* produkt) {
    mockZahlungGestartet = true;
    zuletztUebergebenesProdukt = produkt;
    return true; // Immer erfolgreich im Mock
}

void Zahlungseinheit::zahlungAbbrechen() {
    // Keine Aktion im Mock – kann erweitert werden
}

void Zahlungseinheit::tick() {
    // Keine Logik im Mock – Steuerung erfolgt über globale Flags
}


