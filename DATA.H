#define ZaunLinks 100       // Linke  Begrenzung
#define ZaunRechts -100     // Rechte Begrenzung

// --- Bauteile Initialisierung ---------------------------------------------

struct Bauteil Zaun =
{
    ZAUN,               // Typ
    2,                  // Farbe
    8,                  // Ecken
    5,                  // Verbindungen

    {                   // Koordinaten
     {ZaunLinks ,-30, 50, ZaunLinks,-30, 50, 0,0},  // Leitplanke Links
     {ZaunLinks ,-30,-50, ZaunLinks,-30,-50, 0,0},
     {ZaunLinks ,  0,-50, ZaunLinks,  0,-50, 0,0},

     {ZaunRechts,-30, 50, ZaunRechts,-30, 50, 0,0},  // Leitplanke Rechts
     {ZaunRechts,-30,-50, ZaunRechts,-30,-50, 0,0},
     {ZaunRechts,  0,-50, ZaunRechts,  0,-50, 0,0},

     {     0,  0, 50,  0,  0, 50,  0,0},  // Mittelstreifen
     {     0,  0,  1,  0,  0,  1,  0,0}


    },
    {                                       // Verbindungen
     { 0,1 },
     { 1,2 },
     { 3,4 },
     { 4,5 },
     { 6,7 }
    }
};

struct Bauteil Wall =
{
    MAUER,              // Typ
    12,                 // Farbe
    4,                  // Ecken
    4,                  // Verbindungen

    {
     {-20,-30, 10, -20,-30,-10, 0,0},       // Koordinaten
     {-20,  0, 10, -20,  0,-10, 0,0},
     { 40,  0,-35,  40,  0,-35, 0,0},
     { 40,-30,-35,  40,-30,-35, 0,0}
    },
    {                   // Verbindungsdaten
     { 0,1 },
     { 1,2 },
     { 2,3 },
     { 3,0 }
    }
};

struct Bauteil Schlagloch =
{
    LOCH,               // Typ
    1,                  // Farbe
    4,                  // Ecken
    4,                  // Verbindungen

    {
     {-30, 0, 15, -30, 0, 15, 0,0},
     {  0, 0,-10,   0, 0,-10, 0,0},
     { 30, 0, 15,  30, 0, 15, 0,0},
     {  0, 0, 20,   0, 0, 20, 0,0}
    },
    {
     { 0,1 },
     { 1,2 },
     { 2,3 },
     { 3,0 }
    }
};

struct Bauteil Bridge =
{
    BRUECKE,            // Typ
    9,                  // Farbe
    4,                  // Ecken
    3,                  // Verbindungen

    {
     {ZaunLinks+60,  0, 15, ZaunLinks+60,  0, 15, 0,0},
     {ZaunLinks   ,-60, 15, ZaunLinks   ,-60, 15, 0,0},

     {ZaunRechts   ,-60, 15, ZaunRechts   ,-60, 15, 0,0},
     {ZaunRechts-60,  0, 15, ZaunRechts-60,  0, 15, 0,0},

    },
    {
     { 0,1 },
     { 1,2 },
     { 2,3 },
    }
};

struct Bauteil Person =
{
    MENSCH,             // Typ
    4,                  // Farbe
    10,                 // Ecken
    9,                  // Verbindungen

    {
     {  5,-40, 0,   5,-40, 0, 0,0},     // Kopf
     {-10,-50, 0, -10,-50, 0, 0,0},
     {  5,-60, 0,   5,-60, 0, 0,0},
     { 10,-50, 0,  10,-50, 0, 0,0},

     {  5,-20, 0,   5,-20, 0, 0,0},     // Rumpf + Beine
     {-20,  0, 0, -20,  0, 0, 0,0},
     { 20,  0, 0,  20,  0, 0, 0,0},

     {-20,-40,10, -20,-40,10, 0,0},     // Arme
     {  5,-30, 0,   5,-30, 0, 0,0},
     { 20,-40,10,  20,-40,10, 0,0}
    },
    {
     { 0,1 },   // Kopfverbindungen
     { 1,2 },
     { 2,3 },
     { 3,0 },

     { 0,4 },   // Rumpf + Beinverbindungen
     { 4,5 },
     { 4,6 },

     { 7,8 },   // Armverbindungen
     { 8,9 }
    }
};

// --- Verschiedene Fahrzeuge sollen anw‰hlbar sein -------------------------

struct Fahrzeug Mofa =
{
    0.2,        // Beschleunigung in G
    0.6,        // Bremskraft  in G
    25.0,       // VMAX in Km/h
    3.3,        // Kurvenradius in Meter
    155.0       // Hˆhe Betrachter ¸Åber Fahrbahn in Zentimeter
};

struct Fahrzeug Motorrad =
{
    0.5,        // Beschleunigung in G
    0.9,        // Bremskraft  in G
    145.0,      // VMAX in Km/h
    4.5,        // Kurvenradius in Meter
    150.0       // Hˆhe Betrachter ¸ber Fahrbahn in Zentimeter
};

Fahrzeug Pkw =
{
    0.6,        // Beschleunigung in G
    1.0,        // Bremskraft  in G
    175.0,      // VMAX in Km/h
    16.0,       // Kurvenradius in Meter
    120.0       // Hˆhe Betrachter ¸ber Fahrbahn in Zentimeter
};
struct Fahrzeug Porsche =
{
    0.9,        // Beschleunigung in G
    1.1,        // Bremskraft  in G
    230.0,      // VMAX in Km/h
    20.5,       // Kurvenradius in Meter
    105.0       // Hîhe Betrachter Åber Fahrbahn in Zentimeter
};

// --- Betrachter Intialisierung --------------------------------------------

struct Betrachter Spieler =
{
    0.0, 0.0, 550.0,        // X, Y, Z Position
    0.0, 0.0, 0.0,          // alpha, beta, gamma
    0,0                     // Bildzentierwerte
};


// --- Bauteile f¸r Titelbild -----------------------------------------------

struct Bauteil C =
{
    0,                  // Typ
    1,                  // Farbe
    6,                  // Ecken
    5,                  // Verbindungen

    {
     {-40,-40, 0, -40,-40, 0, 0,0},         // Koordinaten
     { 20,-40, 0,  20,-40, 0, 0,0},
     { 30,-30, 0,  30,-30, 0, 0,0},
     { 30, 30, 0,  30, 30, 0, 0,0},
     { 20, 40, 0,  20, 40, 0, 0,0},
     {-40, 40, 0, -40, 40, 0, 0,0}
    },
    {                   // Verbindungsdaten
     { 0,1 },
     { 1,2 },
     { 2,3 },
     { 3,4 },
     { 4,5 }
    }
};
struct Bauteil Plus =
{
    0,                  // Typ
    12,                 // Farbe
    4,                  // Ecken
    2,                  // Verbindungen

    {
     {-30, 0, 0, -30,  0, 0, 0,0},          // Koordinaten
     { 30, 0, 0, -30,  0, 0, 0,0},
     { 0, 30, 0,   0, 30, 0, 0,0},
     { 0,-30, 0,   0,-30, 0, 0,0}
    },
    {                   // Verbindungsdaten
     { 0,1 },
     { 2,3 },
    }
};

// --- END OF SOURCE --------------------------------------------------------
