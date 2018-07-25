//***************************************************************************
//*                    Headerdatei zur 3D-Grafik Klasse                     *
//*                                                                         *
//*                Enth‰lt z.Zt. nur bisher benˆtigte Routinen              *
//*                                                                         *
//* Autor   : Lutz Groﬂhennig                              Datum : 08.01.95 *
//* Version : V 2.3                                        Revision : 2     *
//***************************************************************************

#include "Defs.h"   // Struktur Definitionen

class WireObj
{
    public :
            // Konstruktor mit ¸bergabe des zu initialierendes
            // 3D-Objektes
            WireObj(const Bauteil& p);

            // Allgemeiner Destruktor
            virtual ~WireObj();

            // Simple perspektivische Projektion
            // ‹bergeben wird nur die Entfernung des Betrachters
            void Projektion(int Abstand);

            // Projektion mit einem Betrachter Punkt
            // strukturdefinition fÅ¸r den Betrachter siehe DEFS.H
            void Projektion(const Betrachter& Ich);

            // Das Objekt auf den Bildschirm ausgeben
            // vorherige Projektion nˆtig
            void Malen(void);

            // Das Objekt im Raum verschieben
            void Verschieben(int x, int y, int z);

            // Bereichs und Kollisionsbfragen
            int  ClipX(int Pos_x);
            int  ClipY(int Pos_y);
            int  ClipZ(int Max_z);

            // Das Objekt um eine Achse drehen
            void RotateX(float deltaalpha);
            void RotateY(float deltabeta);
            void RotateZ(float deltagamma);

			// R¸Åckgabe des Objekttypes
            int  Typ();

    private :

			// Verschiebung
            int   deltax, deltay, deltaz;
			
			// Rotationswinkel
            float Alpha, Beta, Gamma;
			
			// Zeiger auf Objektdaten
            struct Bauteil *Part;
};

// --- END OF SOURCE -------------------------------------------------------
