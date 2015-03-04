/***********************************************************************

    Klasa Diode biblioteki AVR KuszkAPI v1.0
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

/*! \file Diode.h
 *  \brief Zawiera deklaracje klasy Diode.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Diode.cpp
 *  \brief Zawiera implementacje klasy Diode.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#ifndef _AVR_KUSZKAPI_DIODE_H
#define _AVR_KUSZKAPI_DIODE_H

#include <Arduino.h>

/*! \brief Reprezentacja diody LED.
 *
 * Pozwala na łatwą obsługę diody LED.
 *
 */
class Diode
{

	protected:

		const short PORT;	//!< Numer pinu pod który podłączono diodę.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] iPin	Określna numer portu pod który podłączono diodę.
		 *  \param [in] bState	Stan początkowy diody.
		 *
		 * Inicjuje wszystkie pola obiektu i ustala wybrany stan.
		 *
		 */
		Diode(short iPin, bool bState = LOW);

		/*! \brief Destruktor obiektu.
		 *
		 * Wyłącza diodę i ustawia jej pin na wejściowy.
		 *
		 */
		~Diode(void);

		/*! \brief Włącza diodę.
		 *
		 * Ustala napięcie na wyjściu w stan wysoki.
		 *
		 */
		void On(void);

		/*! \brief Wyłącza diodę.
		 *
		 * Ustala napięcie na wyjściu w stan niski.
		 *
		 */
		void Off(void);

		/*! \brief Ustala stan diody.
		 *  \param [in] bState Nowy stan diody.
		 *  \see On(), Off().
		 *
		 * Zmienia dotychczasowy stan wyjścia pod które podłączona jest dioda.
		 *
		 */
		void SetState(bool bState);

};

#endif
