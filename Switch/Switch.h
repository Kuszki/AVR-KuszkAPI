/***********************************************************************

    Klasa Switch biblioteki AVR KuszkAPI v1.0
    Copyright (C) 2014 Łukasz "Kuszki" Dróżdż

    Niniejszy program jest wolnym oprogramowaniem; możesz go
    rozprowadzać dalej i/lub modyfikować na warunkach Powszechnej
    Licencji Publicznej GNU, wydanej przez Fundację Wolnego
    Oprogramowania - według wersji 2-giej tej Licencji lub którejś
    z późniejszych wersji.

    Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
    użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
    gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
    ZASTOSOWAŃ. W celu uzyskania bliższych informacji - Powszechna
    Licencja Publiczna GNU.

    Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
    Powszechnej Licencji Publicznej GNU (GNU General Public License);
    jeśli nie - napisz do Free Software Foundation, Inc., 675 Mass Ave,
    Cambridge, MA 02139, USA.

***********************************************************************/

/*! \file Switch.h
 *  \brief Zawiera deklaracje klasy Switch.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Switch.cpp
 *  \brief Zawiera implementacje klasy Switch.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#ifndef _AVR_KUSZKAPI_SWITCH_H
#define _AVR_KUSZKAPI_SWITCH_H

#include <Arduino.h>

/*! \brief Przycisk "włącz/wyłącz".
 *
 * Pozwala na automatyczną obsługę przycisku cyfrowego bistabilnego i monostabilnego wraz z wyborem odpowiedniego zdarzenia i sposobem zachowania przycisku.
 *
 */
class Switch
{

	/*! \brief Sposób działania przycisku.
	 *
	 * Definiuje na jakie zbocze będzie reagował przycisk (przy jakim zboczu nastąpi zmiana jego stanu).
	 *
	 */
	public: enum MODE
	{
		ON_SWITCH,	//!< Oznacza, że zdarzenie zmiany stanu będzie powiązane ze zmianą fizyczną przycisku.
		ON_RISING,	//!< Oznacza, że zdarzenie zmiany stanu będzie powiązane z narastaniem zbocza sygnału.
		ON_FALLING	//!< Oznacza, że zdarzenie zmiany stanu będzie powiązane z opadaniem zbocza sygnału.
	};

	protected:

		typedef void (*ONCHANGE)(bool); //!< Prototyp funkcji zwrotnej wywoływanej przy zdarzeniu przycisku.

		const short INPUT;	//!< Numer pinu pod który podłączono przycisk.

		ONCHANGE fCallback;	//!< Adres funkcji zwrotnej wywoływanej przy zmianie stanu przycisku.

		bool	bLast;		//!< Ostatni zarejestrowany fizyczny stan przycisku.
		bool bOn;			//!< Aktualny stan przycisku.

		char iCount;		//!< Aktualna ilość wciśnięć przycisku.
		char iChange;		//!< Ilość zmian fizycznego stanu potrzebna do zmiany stanu logicznego.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] iPin	Określna numer portu pod który podłączono przycisk.
		 *  \param [in] fProc	Adres funkcji zwrotnej do wywołania przy zmianie stanu przycisku.
		 *  \param [in] eMode	Sposób działania przycisku.
		 *  \param [in] iType	Rodzaj połączenia przycisku (wbudowany pullup lub ręczny pullup).
		 *  \see MODE, ONCHANGE.
		 *
		 * Inicjuje wszystkie pola obiektu i ustala wybrany port jako wejściowy.
		 *
		 */
		Switch(short iPin, ONCHANGE fProc = NULL, MODE eMode = ON_SWITCH, short iType = INPUT_PULLUP);

		/*! \brief Odświerza stan przycisku.
		 *  \return Aktualny logiczny stan przycisku.
		 *  \note Użyj tej metody wraz z każdą iteracją głównej pętli programu.
		 *
		 * Sprawdza fizyczne połorzenie przycisku i odświerza jego stan.
		 *
		 */
		bool Check(void);

		/*! \brief Włącza przełącznik.
		 *  \note Po użyciu na przełączniku o stabilnym stanie zmienia logiczne położenia przycisku.
		 *
		 * Symuluje włączenie przełącznka wraz z wywołaniem funkcji zwrotnej.
		 *
		 */
		void On(void);

		/*! \brief Wyłącza przełącznik.
		 *  \note Po użyciu na przełączniku o stabilnym stanie zmienia logiczne położenia przycisku.
		 *
		 * Symuluje wyłączenie przełącznka wraz z wywołaniem funkcji zwrotnej.
		 *
		 */
		void Off(void);

		/*! \brief Ustala nowe zdarzenie zmiany stanu.
		 *  \param [in] fProc Adres funkcji zwrotnej.
		 *  \see ONCHANGE.
		 *
		 * Zmienia dotychczasowe działanie przycisku poprzez zdefiniowanie nowej funkcji zwrotnej.
		 *
		 */
		void SetAction(ONCHANGE fProc);

		/*! \brief Ustala nowy sposób działania przycisku.
		 *  \param [in] eMode Sposób działania.
		 *  \see MODE.
		 *
		 * Zmienia dotychczasowe działanie przycisku poprzez zdefiniowanie nowego sposobu działania.
		 *
		 */
		void SetMode(MODE eMode);

		/*! \brief Ustala stan przycisku.
		 *  \param [in] bState Nowy stan przycisku.
		 *  \see On(), Off().
		 *
		 * Zmienia dotychczasowy stan przycisku bez wywołania funkcji zwrotnej.
		 *
		 */
		void SetState(bool bState);

};

#endif
