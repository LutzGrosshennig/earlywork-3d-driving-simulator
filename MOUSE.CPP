//***************************************************************************
//*                   Klassendefinition f�r Mausbedienung		    *
//*									    *
//*                Enth�lt z.Z. nur bisher ben�tigte Routinen  		    *
//*									    *
//* Autor   : Lutz Gro�hennig                              Datum : 18.12.94 *
//* Version : V 1.0	                                   Revision : 1	    *
//***************************************************************************

#include "mouse.h"				// Headerdatei einlesen

//***************************************************************************
//* Name der Methode   : Mouse()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : keine						    *
//*									    *
//* Funktion : Objekt Konstruktor			    		    *
//***************************************************************************

Mouse::Mouse(void)
{
	asm {
		mov ax,0	// gew�nschte Funktion des Maustreibers
				// in diesen Fall : Neu Initalisieren
		int 0x33	// Maustreiber aufrufen
	    };
};

//***************************************************************************
//* Name der Methode   : ShowMouse()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : keine						    *
//*									    *
//* Funktion : Mauszeiger sichtbar machen		    		    *
//***************************************************************************

void Mouse::ShowMouse(void)
{
	asm {
		mov ax,1	// gew�nschte Funktion des Maustreibers
				// in diesen Fall : Display Pointer
		int 0x33	// Maustreiber aufrufen
	    };
};


//***************************************************************************
//* Name der Methode   : HideMouse()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : keine						    *
//*									    *
//* Funktion : Mauszeiger unsichtbar machen		    		    *
//***************************************************************************

void Mouse::HideMouse(void)
{
	asm {
		mov ax,2	// gew�nschte Funktion des Maustreibers
				// in diesen Fall : Display Pointer
		int 0x33	// Maustreiber aufrufen
	    };
};


//***************************************************************************
//* Name der Methode   : Mouse_X()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : X-Position der Maus (0..639)			    *
//*									    *
//* Funktion : Auslesen der aktuellen X-Position des Mauszeigers            *
//***************************************************************************

int Mouse::Mouse_X(void)
{
	int Dummy;		// Dummy Variable um Warnings des Compilers
				// zu verhindern
	asm {
		mov ax,3	// gew�nschte Funktion des Maustreibers
		int 0x33        // hier Mausstatus einlesen
		mov Dummy,cx
	    };
	return (Dummy);
};


//***************************************************************************
//* Name der Methode   : Mouse_Y()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : Y-Position der Maus (0..479)			    *
//*									    *
//* Funktion : Auslesen der aktuellen Y-Position des Mauszeigers            *
//***************************************************************************

int Mouse::Mouse_Y(void)
{
	int Dummy;

	asm {
		mov ax,3	// gew�nschte Funktion des Maustreibers
		int 0x33	// hier Mausstatus einlesen
		mov Dummy,dx
	    };
	return (Dummy);
};


//***************************************************************************
//* Name der Methode   : Mouse_Buttons()				    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : Status der Maustasten				    *
//*									    *
//* Funktion : Status der Maustasten ermitteln			            *
//***************************************************************************

int Mouse::Mouse_Buttons(void)
{
	int Dummy;

	asm {
		mov ax,3	// gew�nschte Funktion des Maustreibers
		int 0x33        // hier Mausstatus einlesen
		mov Dummy,bx
	    };
	return (Dummy);
};


//***************************************************************************
//* Name der Methode   : Mouse_RelX()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : Relative Verschiebung des Mauszeigers		    *
//*									    *
//* Funktion : Gibt die relative Verschiebung des Mauszeigers in Mickeys    *
//*	       zur�ck ( 1 Mickey entspricht der Aufl�sung der Maus )	    *
//***************************************************************************

int Mouse::Mouse_RelX(void)
{
	int Dummy;

	asm {
		mov ax,0xB	// gew�nschte Funktion des Maustreibers
		int 0x33  	// hier delta_x einlesen
		mov Dummy,cx
	    };
	return (Dummy);
};


//***************************************************************************
//* Name der Methode   : Mouse_RelY()					    *
//* �bergabe Parameter : keine   					    *
//* R�ckgabe Parameter : Relative Verschiebung des Mauszeigers		    *
//*									    *
//* Funktion : Gibt die relative Verschiebung des Mauszeigers in Mickeys    *
//*	       zur�ck ( 1 Mickey entspricht der Aufl�sung der Maus )	    *
//***************************************************************************

int Mouse::Mouse_RelY(void)
{
	int Dummy;

	asm {
		mov ax,0xB	// gew�nschte Funktion des Maustreibers
		int 0x33        // hier delta_y einlesen
		mov Dummy,dx
	    };
	return (Dummy);
};
// --- END OF SOURCE --------------------------------------------------------