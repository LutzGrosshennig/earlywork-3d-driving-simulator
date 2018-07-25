//***************************************************************************
//*                                                                         *
//*              Hochschule Bremen WS 1994/1995                             *
//*                                                                         *
//*                 Programmier Projekt SPR-L                               *
//*                                                                         *
//* Prof : Dr. Breymann                                     Semester : I2.2 *
//*                                                                         *
//* Projektbearbeiter  : Lutz Groﬂhennig                                    *
//* Programmiersprache : Borland C++ 3.1                                    *
//*                                                                         *
//* Projektziel        : Fahrsimulator mit 3D - Grafik                      *
//*                                                                         *
//* Start   : 12.12.94            Ende : 12.1.95          Version : 1.0     *
//*                                                                         *
//* Speichermodel : LARGE     System Anforderung : min. 386 SX-16 + Copro   *
//***************************************************************************

// --- Einbinden der Standard Includedateien --------------------------------

#include <iostream.h>   // F¸r Text Ein- Ausgaben (cin/cout)
#include <graphics.h>   // F¸r Grafikfunktionen (diverse)
#include <stdlib.h>     // F¸r Programmsteuerungsaufgaben (Exit)
#include <conio.h>      // Tastaturereignisse (getch)
#include <dos.h>        // F¸r Soundeffekte (sound, nosound)

// --- Einbinden eigener Includedateien -------------------------------------

#include "HTimer.h"     // Mikrosekunden Timer Klasse
#include "Mouse.h"      // Klassendefinition f¸r Maussteuerung
#include "Objekt.h"     // Klassendefinition f¸r 3D-Objekte
#include "Data.h"       // Enth‰lt voreingestellte Daten

// --- Konstanten Definition ------------------------------------------------

#define MaxHdn 4        	// Anzahl der verf¸gbaren Hindernisse
#define MaxObj 9        	// Grˆﬂe der "Welt"
#define Grad (3.1415/180)   // Umwandlung Grad nach Rad Bogenmaﬂ
#define ESC  27         	// Abbruchtaste = Esc

// --- Prototypen der verwendeten Unterprogramme ----------------------------

void InitGFX(void);     	// Grafikmodus einschalten
void Objekt_setzen(int Nr); // Zufalls Objekt setzen
void SwapScreens(void);     // Bildschirme tauschen
void DoubleBuffering(void); // DoubleBuffering
int  RND(int Bereich);      // Zufallszahl erzeugen
char Titel(void);       	// Titelmen¸
void Bau_Welt(void);        // Welt initialisieren
void Wait_VBI(void);        // Vertical Blanking Interrupt

// --- Globale Variablen ----------------------------------------------------

int Zeichnen    = 0;        // Doublebuffering Variablen
int Sichtbar    = 1;        // Doublebuffering Variablen
int ObjektCount = 0;        // Anzahl der aktuellen Objekte

// --- Struktur & Objektinitialsierung ---

WireObj  *Welt[MaxObj]; // Welt Array definieren
Mouse    Mickey;        // Maustreiber initialisieren
HTimer   Uhr;           // Objekt Uhr der Timer Klasse
Fahrzeug *Simu;         // Struktur des Simulierten Fahrz.

// ==========================================================================
// === Hauptprogramm ========================================================
// ==========================================================================

void main(void)
{
  // --- Definitions & Deklarationsteil ---

  float Speed = 0.0;            // Fahrzeuggeschwindigkeit
  float MoveX = 0.0;            // relative Bewegung (der Maus)

  unsigned long Zeit;           // Mikrosekunden Timer

  int   i           = 0;        // Dummy Variable fÅr Schleifen
  int   Freq        = 20;       // Startfrequenz MotorgerÑusch
  long  Score       = 0;        // Punktzahl

  // --- Flags zur Programmsteuerung ---

  char  Taste    = 0;           // letzter Tastendruck
  char  SFX      = 1;           // Flag Sound an/aus
  char  DispInfo = 1;           // Flag Infos Anzeige
  char  BUMM     = 0;                   // Flag Kollision
  char  LINE     = 0;           // Linienbreite

  // ---------------------- Programmteil ------------------------

  InitGFX();                // Grafik aktiveren

  Spieler.Offset_X = getmaxx()/2;   // Koordinaten Anpassung
  Spieler.Offset_Y = getmaxy()/2;   // (Bildmitte festlegen)

  SwapScreens();            // DoubleBuffering vorbereiten

  Mickey.HideMouse();           // Mauszeiger verbergen

   // --- Hauptschleife enthÑlt die Steuerung und Weltbearbeitung ---

  while (!Titel())
   {

    Spieler.Y   = Simu->Kopfhoehe/-3;  // Hîhe Betrachter Åber der Fahrbahn

    Bau_Welt();                        // Welt aufbauen

    Taste     = 0;             // Flags zurÅck setzen
    Speed     = 0.0;
    Score     = 0;
    BUMM      = 0;
    Freq      = 20;
        Spieler.X = 0.0;


   while (Taste != ESC)         // Esc gedrÅckt ?
     {

         DoubleBuffering();     // Flimmerfreie Darstellung

         Uhr.timerOn();         // Neue Zeitmessung

         if (kbhit())               // Taste gedrÅckt ?
    {
        Taste = getch();             // Ja, dann Auswerten
        switch (Taste)
         {
            case 'i' : DispInfo = !DispInfo;   // Infos anzeigen ?
             break;

            case 's' : SFX= !SFX;        // Sound an/aus
             break;

            case '4' : Spieler.X -= 5; break;  // Justierung auf der Bahn
            case '6' : Spieler.X += 5; break;  // Justierung auf der Bahn

            case 'f' : LINE = !LINE;
             if (LINE) setlinestyle(SOLID_LINE,0,3);
             else setlinestyle(SOLID_LINE,0,1);
             break;

            default  : break;
         };
     };

    // Maus Steuerung abfragen

    MoveX      = Mickey.Mouse_RelX();

    Spieler.X += MoveX * (Speed / Simu->Lenkung);

    Score     += Speed/4;

    // Abfrage der Maustasten

    switch ( Mickey.Mouse_Buttons() )
     {
        case 1 : if (Speed < Simu->VMAX/5)
              {
                 Speed +=Simu->Gas;     // Gasgeben
                 Freq  += 1;
              };
             break;

        case 2 : if (Speed > 0.0)       // Abbremsen
              {
//               sound(17000);
                 Speed -=Simu->Bremse;
                 Freq -= 1;
//               sound(Freq);
              }
             else
              {
                 Speed =0.0;
                 Freq = 20;
              };
             break;

        default : break;
     };

    // Die ganze Welt abarbeiten

    for (i=0 ; i < ObjektCount; i++)
     {

         // Objekt Clippen gegebenfalls ganz Lîschen
         // Und neu initialisieren

         if ( i < 6)
          {
             if ( Welt[i]->ClipZ(Spieler.Z-150) )  // Leitplanke neu setzen?
        {
            Welt[i]->Verschieben(0,0,-600);   // Ja!
        };
            }
          else
            {
         if (Welt[i]->ClipZ(Spieler.Z-75))
          {
              // --- Kollision ? ----------

              if (Welt[i]->ClipX(Spieler.X))
                {
            int Wer = Welt[i]->Typ();   // Wenn ja, womit ?
            switch (Wer)
             {
                case MAUER  : Speed =  0.0;
                     BUMM  =  1;
                     Freq  =  20;
                     if (Score >= 300) Score -= 300;
                     else Score = 0;
                     break;

                case MENSCH : Speed = 0.0;
                     BUMM  = 1;
                     Freq  = 20;
                     Score = 0;
                     break;

                case LOCH   : if (Speed >= 5.0)
                      {
                          Speed -= 5.0;
                          Freq  -= 5;
                      }
                     else
                      {
                         Speed = 0.0;
                         Freq  = 20;
                      };
                     if (Score >= 100) Score -= 100;
                     else Score = 0;
                     break;

               default     : break;
             };
              };
             delete Welt[i];
              Objekt_setzen(i);
             Welt[i]->Verschieben(0,0,-250);
            };
        };

        Welt[i]->Verschieben(0,0,Speed);    // Objekte verschieben
        Welt[i]->Projektion(Spieler);   // Projektion 3D -> 2D
        Welt[i]->Malen();           // Weltobjekt zeichnen

     };

    // ********  Kollisionsabfrage  *******************

    // Kollision mit linker Leitplanke

    if (Spieler.X >= ZaunLinks)
     {
       Spieler.X = ZaunLinks;
       if (Speed > 5.0)
         {
             Speed -= 5.0;
             Freq  -= 3;
        }
       else
         {
           Speed = 0.0;
           Freq  = 20;
        }
       Spieler.X -= 2.0;
     };

    // Kollision mit linker Leitplanke

    if (Spieler.X <= ZaunRechts)
     {
       Spieler.X = ZaunRechts;
        if (Speed > 5.0)
         {
             Speed -= 5.0;
             Freq  -= 3;
         }
        else
         {
             Speed = 0.0;
             Freq  = 20;
         }
        Spieler.X += 2.0;
     };

     // Sound Steuerung +- Drehzahlschwankungen

    if ((SFX) && (Speed !=0.0)) sound(Freq+RND(1));
    else nosound();

    // Informations Anzeige

    if (DispInfo)
     {
        setcolor(3);
//      outtextxy(265,10,"Fahrsimulator");
//      outtextxy(280,20,"Lutz Gro·hennig");
//      outtextxy(260,30,"-------------------");
        outtextxy(310,10,": Bilder/s");
        outtextxy(285,10,ltoa((1000/Zeit),NULL,10));
     };

    // Auslesen des Mikrosekunden ZÑhlers
    // Division durch 1000 da nur Millisekunden relevant sind

    Zeit = Uhr.timerOff()/1000;

    // öberprÅfen ob der Aufbau weniger als 50 msek benîtigt hat,
    // wenn ja dann warten bis 50 msek vergangen sind um die Bildrate
    // auf 20 Bilder/Sekunde zu begrenzen

    if ( Zeit < 14 ) delay( 14 - Zeit );

    // Ausgabe der aktuellen Geschwindigkeit & Punktzahl

    setcolor(3);
    outtextxy(0,10,"Km/h:");
    outtextxy(60,10,itoa( ((int) (Speed*5)),NULL,10));
    outtextxy(0,20,"Score:");
    outtextxy(60,20,ltoa(Score,NULL,10));

    if ((BUMM) && (Speed == 0.0))
     {
        setcolor (3);
        outtextxy(300,100,"B O I N G !");
        outtextxy(300,110,"-----------");
     };
    if (Speed > 0.0) BUMM = 0;

     };  // Ende der while Schleife

   // Alle Weltobjekte lîschen

   for ( i=0 ; i < ObjektCount ; i++)
    {
      delete Welt[i];
    };

   if (SFX) nosound();      // Sound auschalten

 };                 // Ende der Ñu·eren while Schleife

 closegraph();          // Grafikbildschirm schlie·en

};                  // Programmende


//===========================================================================
//=== Unterprogramme ========================================================
//===========================================================================

//***************************************************************************
//* Name der Routine   : InitGFX()                      *
//* öbergabe Parameter : keine                           *
//* RÅckgabe Parameter : keine                           *
//*                                     *
//* Funktion : Initialisierung des Grafikbildschirms                *
//***************************************************************************

void InitGFX()
{

   int   gdriver = VGA;         // Nur VGA zulassen
   int   gmode = VGAMED;        // Auflîsung 640*350 16 Farben 2 Seiten

   initgraph(&gdriver,&gmode,"");   // Grafik einschalten

   if (graphresult() != grOk)       // Gab es Probleme ?
                    // Ja, Beenden
   {
      cout << "*** Grafikfehler ***" << endl;
      cout << "Dieses Programm benîtig einen VGA Grafikadapter." << endl;
      cout << "Entweder verwenden Sie einen anderen Adapter oder der ";
      cout << "benîtigte BGI-Treiber konnte nicht geladen" << endl;
      cout << "werden !!!" << endl;
        cout << "RÅckkehr zum Dos" << endl;
      exit(1);
    };
};                  // Nein, keine Probleme, weitermachen


//***************************************************************************
//* Name der Routine   : Objekt_setzen()                    *
//* öbergabe Parameter : Ziel im Weltarray als int Nr                *
//* RÅckgabe Parameter : keine                           *
//*                                     *
//* Funktion : Erzeugt ein neues 3D-Objekt                  *
//***************************************************************************

void Objekt_setzen(int Nr)
{
  int typ = random(MaxHdn);

  switch (typ)
  {                         
    case 0 : Welt[Nr] = new WireObj(Wall);
         Welt[Nr]->Verschieben( RND(100), 0, RND(100));
         break;

     case 1 : Welt[Nr] = new WireObj(Schlagloch);
         Welt[Nr]->Verschieben( RND(100), 0, RND(100));
          break;

    case 2 : Welt[Nr] = new WireObj(Person);
          Welt[Nr]->Verschieben( RND(100), 0, RND(100));
         break;
    case 3 : Welt[Nr] = new WireObj(Bridge);
         Welt[Nr]->Verschieben( 0, 0, RND(100));
         break;
    default: break;

  };
};


//***************************************************************************
//* Name der Routine   : SwapScreens()                          *
//* öbergabe Parameter : keine                           *
//* RÅckgabe Parameter : keine                           *
//*                                     *
//* Funktion : Schaltet zwischen aktiven und Sichtbare Bildschirmseite um   *
//***************************************************************************

void SwapScreens()
{
    setvisualpage(Sichtbar);
    setactivepage(Zeichnen);
};


//***************************************************************************
//* Name der Routine   : DoubleBuffering()                  *
//* öbergabe Parameter : keine                           *
//* RÅckgabe Parameter : keine                           *
//*                                     *
//* Funktion : Schaltet zwischen aktiven und Sichtbare Bildschirmseite um   *
//*        und lîscht den aktiven Bildschirm             *
//***************************************************************************

void DoubleBuffering()
{
    // --- Inhalte von Sichtbar und Zeichnen vertauschen ---

    register int d = Sichtbar;
    Sichtbar = Zeichnen;
    Zeichnen = d;

    // --- Den gerade gezeichneten Screen anzeigen und den anderen lîschen

    SwapScreens();
    Wait_VBI();

    cleardevice();
};


//***************************************************************************
//* Name der Routine   : RND()                          *
//* öbergabe Parameter : int Bereich                     *
//* RÅckgabe Parameter : Zufallszahl zwischen +Bereich & -Bereich        *
//*                                     *
//* Funktion : Erzeugt eine Zufallszahl im vorgegebenen Intervall       *
//***************************************************************************

int RND(int Bereich)
{
    return ( random(Bereich*2)-Bereich);
};


//***************************************************************************
//* Name der Routine   : Titel()                        *
//* öbergabe Parameter : keiner                          *
//* RÅckgabe Parameter : MenÅauswahl                      *
//*                                     *
//* Funktion : Erzeugt einen Titelscreen mit Auswahl MenÅ des zu         *
//*        simulierenden Fahrzeugs                      *
//***************************************************************************

char Titel()
{
    char Key   = 0;
    int  j;

    setlinestyle(SOLID_LINE,0,3);

    Welt[0] = new WireObj(C);           // Das "C" als  3D-Objekt
    Welt[0]->Verschieben(100,0,0);          // "in die Welt setzen"

    Welt[1] = new WireObj(Plus);            // ebenso das erste plus

    Welt[2] = new WireObj(Plus);        // und das zwote
    Welt[2]->Verschieben(-100,0,0);

    while ((Key != 'q') && (Key !='Q'))     // MenÅ abfragen
     {
        DoubleBuffering();          // Flimmern vermeiden

        for ( j=0; j<3; j++)             // Ganze Welt abarbeiten
         {
             Welt[j]->RotateZ(-2*Grad);
           Welt[j]->Projektion(Spieler);
           Welt[j]->Malen();
         };

        setcolor(15);                   // MenÅ ausgeben

        outtextxy(265, 40,"C++ Fahrsimulator");
        outtextxy(260, 50,"von Lutz Gro·hennig");

        outtextxy(250, 90,"WÑhlen Sie ein Fahrzeug");
        outtextxy(295,120,"1. Mofa");
        outtextxy(295,130,"2. Motorrad");
        outtextxy(295,140,"3. Pkw");
        outtextxy(295,150,"4. Porsche");
        outtextxy(295,190,"Q. Ende");

        if (kbhit())            // Tastatur abfragen
         {
        Key = getch();

        if ((Key >= '1') && (Key <= '4'))
         {
            delete Welt[0];         // Welt lîschen
             delete Welt[1];
            delete Welt[2];

            switch (Key)
             {
            case '1' : Simu = &Mofa; break;       // Fahrzeug
            case '2' : Simu = &Motorrad; break;   // Parameter
            case '3' : Simu = &Pkw; break;        // einstellen
            case '4' : Simu = &Porsche; break;
            default  : Simu = &Pkw; break;
             };
             return(0);
         };
        if ((Key == 'q') || (Key== 'Q'))
         {
            delete Welt[0];
            delete Welt[1];
            delete Welt[2];
            return(1);
         };

         };
     };

     setlinestyle(SOLID_LINE,0,1);

     return (0);
};


//***************************************************************************
//* Name der Routine   : Bau_Welt()                     *
//* öbergabe Parameter : keine                           *
//* RÅckgabe Parameter : keine                           *
//*                                     *
//* Funktion : Erzeugt die Simulations "Welt"                   *
//***************************************************************************

void Bau_Welt()
{
   // --- 6 Zaunsegmente setzen ---

    ObjektCount = 0;

   for ( int i = 0 ; i < 6 ; i++)
    {
       Welt[i] = new WireObj(Zaun);
       Welt[i]->Verschieben(0,0,i*100);
         ObjektCount++;
    };

   // --- 3 weitere Objekte setzen ---

   Welt[i] = new WireObj(Wall);
   Welt[i]->Verschieben(30,0,450);

   Welt[i+1] = new WireObj(Schlagloch);
   Welt[i+1]->Verschieben(-30,0,250);

   Welt[i+2] = new WireObj(Person);
   Welt[i+2]->Verschieben(-50,0,0);
   ObjektCount +=3;
};


//***************************************************************************
//* Name der Routine   : Wait_VBI()                     *
//* öbergabe Parameter : keine                           *
//* RÅckgabe Parameter : keine                           *
//*                                     *
//* Funktion : Rasterinpterrupt abwarten                    *
//***************************************************************************

void Wait_VBI()
{
    static const int inputStatus1 = 0x3DA;

    asm mov dx, inputStatus1;

    test_1:

    asm {
        in al, dx
        test al,0x8
        jnz test_1
        }

    test_2:

    asm {
        in al, dx
        test al,0x8
        jz test_2
         }
};

// --- END OF SOURCE --------------------------------------------------------