//***************************************************************************
//*              Klassendefinition fÅr Dreidimensionale Grafik		    *
//*									    *
//*                EnthÑlt z.Z. nur bisher benîtigte Routinen  		    *
//*									    *
//* Autor   : Lutz Gro·hennig                              Datum : 08.01.95 *
//* Version : V 2.3	                                   Revision : 2	    *
//***************************************************************************

#include <graphics.h>			// Standart BGI Grafik
#include <math.h>			// benîtigte Mathematikfunktionen
#include "Objekt.h"			// Headerdatei


//***************************************************************************
//* Name der Methode   : WireObj()					    *
//* öbergabe Parameter : Strukurdaten  					    *
//* RÅckgabe Parameter : keine						    *
//*									    *
//* Funktion : Objekt Konstruktor			    		    *
//***************************************************************************

WireObj::WireObj(const Bauteil& p)
{
	deltax = deltay = deltaz = 0;
	Alpha = Beta = Gamma = 0;

	// --- Struktur kopieren

	Part = new Bauteil;
	Part->Ecken = p.Ecken;
	Part->Farbe = p.Farbe;
	Part->Typ   = p.Typ;
	Part->Verb  = p.Verb;		// von Pkt. -> nach Pkt. info

	// --- Kopierschleifen

	for (register int i=0; i<MaxEcken; i++) Part->Data[i]=p.Data[i];
	for (i=0; i<MaxVerb; i++) Part->Line[i]=p.Line[i];

};


//***************************************************************************
//* Name der Methode   : ~WireObj()					    *
//* öbergabe Parameter : keine   					    *
//* RÅckgabe Parameter : keine						    *
//*									    *
//* Funktion : Objekt Destruktor			    		    *
//***************************************************************************

WireObj::~WireObj()
{
	delete Part;
};


//***************************************************************************
//* Name der Methode   : Projektion()					    *
//* öbergabe Parameter : Abstand Auge-> Bildschirm   			    *
//* RÅckgabe Parameter : keine						    *
//*									    *
//* Funktion : Simple Zentralprojektion			    		    *
//***************************************************************************

void WireObj::Projektion(int Abstand)
{

   int dx = getmaxx() >> 1;  		// Bildmitte = Bildmaxx / 2
   int dy = getmaxy() >> 1;  		// &           Bildmaxy / 2

   // fÅr jeden Punkt

   for (register int i=0; i<Part->Ecken; i++)
    {

      // doppelte addition vermeiden

      float SpeedUp1 = Part->Data[i].rz+deltaz;

      // Projektion 3D->2D

      Part->Data[i].bx = ((Part->Data[i].rx+deltax)/SpeedUp1*Abstand)+dx;
      Part->Data[i].by = ((Part->Data[i].ry+deltay)/SpeedUp1*Abstand)+dy;
    };

};


//***************************************************************************
//* Name der Methode   : Projektion()					    *
//* öbergabe Parameter : Struktur des Spielers				    *
//* RÅckgabe Parameter : keine						    *
//*									    *
//* Funktion : Zentralprojektion mit variablen Betrachterstandpunkt	    *
//***************************************************************************

void WireObj::Projektion(const Betrachter& Ich)
{
   // Alle punkte bearbeiten

   for (register int i=0; i<Part->Ecken; i++)
    {

      // Doppelte Berechnungen einsparen

      register float SpeedUp = Part->Data[i].rz - Ich.Z;
      register float Speedy  = Part->Data[i].rz;

      // Division durch Null vermeiden

      if (SpeedUp == 0.0) SpeedUp = 0.0001;

      // Projektion 3D->2D

      Part->Data[i].bx=((Ich.X*Speedy)-(Ich.Z*Part->Data[i].rx))/SpeedUp+Ich.Offset_X;
      Part->Data[i].by=((Ich.Y*Speedy)-(Ich.Z*Part->Data[i].ry))/SpeedUp+Ich.Offset_Y;

    };
};


//***************************************************************************
//* Name der Methode   : Malen()					    *
//* öbergabe Parameter : keine   					    *
//* RÅckgabe Parameter : keine						    *
//*									    *
//* Funktion : zuvor Projeziertes Objekt auf Bildschirm ausgeben	    *
//***************************************************************************

void WireObj::Malen(void)
{
  setcolor(Part->Farbe);	  // Objektfarbe = Zeichenfarbe

  for ( register int i=0; i<Part->Verb; i++)
   {
     moveto(Part->Data[Part->Line[i].p1].bx,Part->Data[Part->Line[i].p1].by);
     lineto(Part->Data[Part->Line[i].p2].bx,Part->Data[Part->Line[i].p2].by);
   };
};


//***************************************************************************
//* Name der Methode   : Verschieben()					    *
//* öbergabe Parameter : delta_X, delta_Y, delta_Z			    *
//* RÅckgabe Parameter : keine						    *
//*									    *
//* Funktion : verschiebt das Objekt im Raum				    *
//***************************************************************************

void WireObj::Verschieben(int x,int y,int z)
{
	deltax += x;		// Verschiebung merken
	deltay += y;
	deltaz += z;

	// FÅr alle Punkte

	for (register int i=0; i < Part->Ecken; i++)
	 {
	    Part->Data[i].rx += x;		// Rotationsvariablen
	    Part->Data[i].ry += y;		// mit verschieben
	    Part->Data[i].rz += z;
	 };

};


//***************************************************************************
//* Name der Methode   : ClipX()					    *
//* öbergabe Parameter : Pos_X   					    *
//* RÅckgabe Parameter : BOOLEAN 					    *
//*									    *
//* Funktion : PrÅft ob ein Punkt mit dem Objekt kollidiert	    	    *
//***************************************************************************

int WireObj::ClipX(int Pos_x)
{
	int BOOL = 0;
	float MAX=0.0,MIN=0.0;

	for ( register int i=0; i<Part->Ecken; i++)
	 {
	    if (Part->Data[i].rx > MAX) MAX = Part->Data[i].rx;
	    if (Part->Data[i].rx < MIN) MIN = Part->Data[i].rx;
	 };

	 if (( Pos_x < MAX) && (Pos_x > MIN)) BOOL = 1;	// HIT

	return(BOOL);
};


//***************************************************************************
//* Name der Methode   : ClipY()					    *
//* öbergabe Parameter : Pos_Y   					    *
//* RÅckgabe Parameter : BOOLEAN 					    *
//*									    *
//* Funktion : PrÅft ob ein Punkt mit dem Objekt kollidiert	    	    *
//***************************************************************************

int WireObj::ClipY(int Pos_y)
{
	int BOOL = 0;
	float MAX=0.0,MIN=0.0;

	for ( register int i=0; i<Part->Ecken; i++)
	 {
	    if (Part->Data[i].ry > MAX) MAX = Part->Data[i].ry;
	    if (Part->Data[i].ry < MIN) MIN = Part->Data[i].ry;
	 };

	 if (( Pos_y < MAX) && (Pos_y > MIN)) BOOL = 1;	// HIT

	return(BOOL);
};


//***************************************************************************
//* Name der Methode   : ClipZ()					    *
//* öbergabe Parameter : Max_z   					    *
//* RÅckgabe Parameter : BOOLEAN 					    *
//*									    *
//* Funktion : PrÅfen ob der Punkt vor dem Objekt liegt		    	    *
//***************************************************************************

int WireObj::ClipZ(int Max_z)
{
	int AllesWeg=1;

	for ( register int i=0; i<Part->Ecken; i++)
	 {
	   if (Part->Data[i].rz <= Max_z) AllesWeg=0;
	 };
	return(AllesWeg);
};


//***************************************************************************
//* Name der Methode   : RotateX()					    *
//* öbergabe Parameter : delta_alpha (Bogenma·)				    *
//* RÅckgabe Parameter : keine 						    *
//*									    *
//* Funktion : dreht ein Objekt um die X-Achse			    	    *
//***************************************************************************

void WireObj::RotateX(float delta_alpha)
{
   Alpha += delta_alpha;

   float CosAlpha = cos(Alpha);
   float SinAlpha = sin(Alpha);

   for ( register int i=0; i<Part->Ecken; i++)
    {

      // Diese folgenden AusdrÅcke werden in zwei Multiplikationen benîtig
      // daher werden die Multiplikatoren mit der integrierten Addition
      // in eine Dummy Variable geschrieben das erhîht die Verarbeitungs-
      // geschwindigkeit der Routine.

      float SpeedUp1 = Part->Data[i].y+deltay;
      float SpeedUp2 = Part->Data[i].z+deltaz;

      // X' = X

      Part->Data[i].rx = Part->Data[i].x+deltax;

      // Y' = Y*cos(Alpha) - Z*sin(Alpha)

      Part->Data[i].ry = (SpeedUp1 * CosAlpha) - (SpeedUp2 * SinAlpha);

      // Z' = Y*sin(Alpha) - Z*cos(Alpha)

      Part->Data[i].rz = (SpeedUp1 * SinAlpha) - (SpeedUp2 * CosAlpha);

    };
};


//***************************************************************************
//* Name der Methode   : RotateY()					    *
//* öbergabe Parameter : delta_beta (Bogenma·)				    *
//* RÅckgabe Parameter : keine 						    *
//*									    *
//* Funktion : dreht ein Objekt um die Y-Achse			    	    *
//***************************************************************************

void WireObj::RotateY(float delta_beta)
{

   Beta += delta_beta;				// Rotationswinkel + énderung

   float CosBeta = cos(Beta);			// Einmalige Berechung der
   float SinBeta = sin(Beta);			// Sinus, Cosinus Werte

   for ( register int i=0; i<Part->Ecken; i++)
    {

      // Diese folgenden AusdrÅcke werden in zwei Multiplikationen benîtig
      // daher werden die Multiplikatoren mit der integrierten Addition
      // in eine Dummy Variable geschrieben das erhîht die Verarbeitungs-
      // geschwindigkeit der Routine.

      float SpeedUp1 = Part->Data[i].y+deltay;
      float SpeedUp2 = Part->Data[i].z+deltaz;

      // Y' = Y

      Part->Data[i].ry = SpeedUp1;

      // X' = X*cos(Beta) + Z*sin(Beta)

      Part->Data[i].rx = ((Part->Data[i].x+deltax)*CosBeta)+(SpeedUp2*SinBeta);

      // Z' = -Y*sin(Beta) + Z*cos(Beta)

      Part->Data[i].rz = -(SpeedUp1*SinBeta)+(SpeedUp2*CosBeta);

    };
};


//***************************************************************************
//* Name der Methode   : RotateZ()					    *
//* öbergabe Parameter : delta_gamma (Bogenma·)				    *
//* RÅckgabe Parameter : keine 						    *
//*									    *
//* Funktion : dreht ein Objekt um die Z-Achse			    	    *
//***************************************************************************

void WireObj::RotateZ(float delta_gamma)
{

   Gamma += delta_gamma;		// Rotationswinkel + énderung

   float CosGamma = cos(Gamma);		// Einmalige Berechung der Sinus
   float SinGamma = sin(Gamma);		// bzw. Cosinus Werte

   for ( register int i=0; i<Part->Ecken; i++)
    {

      // Diese folgenden AusdrÅcke werden in zwei Multiplikationen benîtig
      // daher werden die Multiplikatoren mit der integrierten Addition
      // in eine Dummy Variable geschrieben das erhîht die Verarbeitungs-
      // geschwindigkeit der Routine.

      float SpeedUp1 = Part->Data[i].x+deltax;
      float SpeedUp2 = Part->Data[i].y+deltay;

      // Die Z-Position bleibt unverÑndert

      Part->Data[i].rz= Part->Data[i].z+deltaz;

     // x' = x*cos(gamma) - y*sin(gamma)

      Part->Data[i].rx= (SpeedUp1*CosGamma)+(SpeedUp2*SinGamma);

     // y' = x*sin(gamma) + y*cos(gamma)

      Part->Data[i].ry=-(SpeedUp1*SinGamma)+(SpeedUp2*CosGamma);

   };

};


//***************************************************************************
//* Name der Methode   : Typ()						    *
//* öbergabe Parameter : keine						    *
//* RÅckgabe Parameter : Typ Nr 					    *
//*									    *
//* Funktion : Gibt die ID des Objektes zurÅck			    	    *
//***************************************************************************

int WireObj::Typ(void)
{
	return (Part->Typ);
};

// --- END OF SOURCE --------------------------------------------------------