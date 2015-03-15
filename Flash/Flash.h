/***********************************************************************

    Klasa Flash biblioteki AVR KuszkAPI v1.0
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

/*! \file Flash.h
 *  \brief Zawiera deklaracje klasy Flash.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Flash.cpp
 *  \brief Zawiera implementacje klasy Flash.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#ifndef _AVR_KUSZKAPI_FLASH_H
#define _AVR_KUSZKAPI_FLASH_H

#include <Arduino.h>

/*! \brief Model pamięci FLASH mikrokontrolera.
 *
 * Pozwala na łatwy dostęp do pamięci FLASH.
 *
 */
class Flash
{

	protected:

		unsigned uAdress;	//!< Adres aktualnej komórki.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] uStart Określna początkowy adres pamięci flash.
		 *
		 * Zapamiętuje adres pamięci w którym za rozpocząć się wczytywanie lub zapis danych.
		 *
		 */
		Flash(unsigned uStart = 0);

		/*! \brief Odczytuje z pamięci bajt danych.
		 *  \return Odczytane dane.
		 *
		 * Odczytuje z kolejnej komórki dane.
		 *
		 */
		char Read(void);

		/*! \brief Odczytuje z pamięci wybraną ilość danych.
		 *  \param [out] pvData	Wskaźnik na pamięć do wpidania danych.
		 *  \param [in] sSize	Ilość danych do odczytania.
		 *
		 * Odczytuje z kolejnej komórki dane.
		 *
		 */
		void Read(void* pvData, size_t sSize);

		/*! \brief Zapisuje do pamięci bajt danych.
		 *  \param [in] cChar Dane do zapisania.
		 *
		 * Wpisuje do kolejnej komórki pamięci wybrane dane.
		 *
		 */
		void Write(char cChar);

		/*! \brief Zapisuje do pamięci wybraną ilość danych.
		 *  \param [in] pvData	Wskaźnik na pamięć do zapisu.
		 *  \param [in] sSize	Ilość danych do zapisania.
		 *
		 * Zapisuje do pamięci dane.
		 *
		 */
		void Write(const void* pvData, size_t sSize);

		/*! \brief Ustala adres pamięci.
		 *  \param [in] uStart Nowy adres komórki.
		 *
		 * Zmienia dotychczasowy adres kolejnej komórki.
		 *
		 */
		void SetAdress(unsigned uStart);

		/*! \brief Zwraca adres pamięci.
		 *  \return uStart Adres aktualnej komórki.
		 *
		 * Zwraca adres kolejnej komórki pamięci.
		 *
		 */
		unsigned GetAdress(void) const;

		/*! \brief Odczytuje z pamięci bajt danych.
		 *  \param [in] uStart Adres pamięci.
		 *  \return Odczytane dane.
		 *
		 * Odczytuje z wybranej komórki dane.
		 *
		 */
		static char Read(unsigned uStart);

		/*! \brief Zapisuje do pamięci bajt danych.
		 *  \param [in] uStart	Adres pamięci.
		 *  \param [in] cChar	Dane do zapisania.
		 *
		 * Wpisuje do wybrnej komórki pamięci wybrane dane.
		 *
		 */
		static void Write(unsigned uStart, char cChar);

};

#endif
