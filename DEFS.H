//**************************************************************************
//* Definition Datei zur 3D - Grafik Klasse, sowie fÅ¸r den Fahrsimulator   *
//**************************************************************************

#define MaxEcken 12
#define MaxVerb 10

enum ObjType {MAUER, LOCH, MENSCH, ZAUN, BRUECKE};

struct Fahrzeug
{
    float   Gas;            // Faktor f¸r konstante Beschleunigung
    float   Bremse;         // Bremsenwirkung
    float   VMAX;           // Hîchstgeschwindigkeit
    float   Lenkung;        // Lenkwirkung
    float   Kopfhoehe;      // Hîhe des Kopfes Åber d. Fahrbahn
};

struct Element
{
    float x,y,z;
    float rx, ry, rz;
    float bx, by;
};

struct VonNach      // Verbindungsdaten
{                   // Von Punkt P1 nach P2
    char p1, p2;
};

struct Bauteil
{
    int Typ;                       // Identifier
    int Farbe;                     // Zeichenfarbe
    int Ecken;                     // Anzahl Punkte
    int Verb;                      // Anzahl Verbindung.
    struct Element Data[MaxEcken]; // Punktdaten
    struct VonNach Line[MaxVerb];  // Punktverbindungen
};

struct Betrachter
{
    float X, Y, Z;                 // Koordinaten
    float Alpha, Beta, Gamma;      // Blickrichtung
    int   Offset_X, Offset_Y;      // Bildzentierung
};

// --- END OF SOURCE -------------------------------------------------------