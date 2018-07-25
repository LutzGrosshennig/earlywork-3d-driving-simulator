//***************************************************************************
//*                    Headerdatei zur Maus Klasse		            *
//*									    *
//*                Enth„lt z.Z. nur bisher ben”tigte Routinen  		    *
//*									    *
//* Autor   : Lutz Groáhennig                              Datum : 09.01.95 *
//* Version : V 1.0	                                   Revision : 1	    *
//***************************************************************************

class Mouse
{
    public:
		Mouse();		// Konstruktor zur Initialisierung
					// des Maustreibers

		void ShowMouse();	// Mauspointer sichtbar machen
		void HideMouse();	// Mauspointer verbergen
		int  Mouse_X();		// X-Position des Pointers
		int  Mouse_Y();		// Y-Position des Pointers
		int  Mouse_Buttons();	// Status der Maustasten
		int  Mouse_RelX();	// relative Maus„nderung der X_Pos
		int  Mouse_RelY();	// relative Maus„nderung der Y_Pos

};

// --- END OF SOURCE -------------------------------------------------------