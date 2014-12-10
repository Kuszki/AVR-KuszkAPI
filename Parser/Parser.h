/***********************************************************************

    Klasa Parser biblioteki AVR KuszkAPI v1.0
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

/*! \file Parser.h
 *  \brief Zawiera deklaracje klasy Switch.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Parser.cpp
 *  \brief Zawiera implementacje klasy Switch.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#include <Arduino.h>

class Parser
{

	protected:

		typedef void (*ONCOMPLETE)(void*); //!< Prototyp funkcji zwrotnej wywoływanej przy zdarzeniu odebrania pełnego pakietu danych.

		const size_t sSize;		//!< Rozmiar ramki danych.

		ONCOMPLETE fCallback;	//!< Adres funkcji zwrotnej wywoływanej przy zmianie stanu przycisku.

		size_t sPos;			//!< Aktualna liczba wczytanych bajtów.

		char* ptData;			//!< Wskaźnik na odczytywane dane.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] sBytes	Określna rozmiar ramki danych.
		 *  \param [in] fProc	Adres funkcji zwrotnej do wywołania po wczytaniu pełnej ramki danych.
		 *
		 * Inicjuje wszystkie pola obiektu i alokuje bufor na ramkę danych.
		 *
		 */ Parser(size_t sBytes, ONCOMPLETE fProc);

		/*! \brief Destruktor obiektu.
		 *
		 * Zwalnia pamięć użytą na ramkę danych.
		 *
		 */ ~Parser(void);

		/*! \brief Usiłuje wczytać kolejną porcję danych.
		 *  \param [in] sPort Wskaźnik na obiekt strumienia z którego mają zostać pobrane dane.
		 *  \return Powodzenie operacji.
		 *  \note Podczaj jednego wywołania tylko jeden pełny pakiet danych może zostać odebrany.
		 *
		 * Sprawdza czy dostępne są dane do odczytu i zapisuje je do bufora ramki. Jeśli odczyt zapełnił cały bufor ramki metoda zwróci wartość 'true'. W przeciwnym wypadku zwracaną wartością będzie 'false'. Po odebraniu danych automatycznie wywołana zostanie zadana funkcja zwrotna.
		 *
		 */ bool Check(Stream* sPort);

		/*! \brief Ustala nową funkcję zwrotną.
		 *  \param [in] fProc Funkcja zwrotna.
		 *  \see ONCOMPLETE.
		 *
		 * Zmienia dotychczasowe zachowanie po odebraniu pełnej ramki danych.
		 *
		 */ void SetAction(ONCOMPLETE fProc);

};
