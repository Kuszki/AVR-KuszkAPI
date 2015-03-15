/***********************************************************************

    Klasa Comport biblioteki AVR KuszkAPI v1.0
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

/*! \file Comport.h
 *  \brief Zawiera deklaracje klasy Switch.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Comport.cpp
 *  \brief Zawiera implementacje klasy Switch.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#ifndef _AVR_KUSZKAPI_COMPORT_H
#define _AVR_KUSZKAPI_COMPORT_H

#include <Arduino.h>

#define BUFF_SIZE 32

/*! \brief Obsługa połączeń przychodzących i wychodzących portu szeregowego.
 *  \note Ze względu na prostotę zrezygnowano z rozwiązania szablonowego.
 *
 * Klasa umożliwia wysyłanie i odbieranie danych za pośrednictwem interfejsu RS232.
 *
 */
class Comport
{

	public:

		/*! \brief Struktura bufora danych.
		 *
		 * Struktura ma na celu przechowywanie informacji o stanie bufora danych wejścia i wyjścia.
		 *
		 */
		struct Buffer
		{
			char pcBuff[BUFF_SIZE];	//!< Bufor na dane.

			unsigned short uHead;	//!< Koniec danych.
			unsigned short uTail;	//!< Początek danych.
		};

	protected:

		volatile static Buffer* bIN;	//!< Bufor danych wejściowych.
		volatile static Buffer* bOUT;	//!< Bufor danych wyjściowych.

		size_t sPos;

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] uRate Określa prędkość transmisji danych.
		 *
		 * Inicjuje rejestry informujące o parametrach transmisji danych..
		 *
		 */
		Comport(unsigned uRate = 9600);

		/*! \brief Destruktor obiektu.
		 *
		 * Wyłącza interfejs i zeruje stan rejestrów.
		 *
		 */
		~Comport(void);

		/*! \brief Inicjuje transmisje danych.
		 *
		 * Ustawia wybrane rejestry tak, by umożliwić transmisje danych przez port szeregowy.
		 *
		 */
		void Start(void);

		/*! \brief Zatrzymuje działanie interfejsu.
		 *
		 * Czeka na wysłanie reszty danych i kończy działanie interfejsu.
		 *
		 */
		void Stop(void);

		/*! \brief Wysyła jeden bajt danych.
		 *  \param [in] cChar Dane.
		 *
		 * Sprawdza czy bufor wejściowy nie jest przepełniony i wysyła wybrany bajt danych.
		 *
		 */
		void Send(char cChar);

		/*! \brief Wysyła ciąg znaków.
		 *  \param [in] pcData Dane.
		 *
		 * Sprawdza czy bufor wejściowy nie jest przepełniony i wysyła dane na które wskazuje parametr funkcji aż do napotkania terminatora.
		 *
		 */
		void Send(const char* pcData);

		/*! \brief Wysyła dane binarne.
		 *  \param [in] pvData	Dane.
		 *  \param [in] sBytes	Rozmiar danych.
		 *
		 * Sprawdza czy bufor wejściowy nie jest przepełniony i wysyła podaną liczbę bajtów na które wskazuje parametr funkcji.
		 *
		 */
		void Send(const void* pvData, size_t sBytes);

		/*! \brief Odbiera dane binarne.
		 *  \return Odebrane dane.
		 *  \note Gdy bufor wejściowy jest pusty metoda zwróci 0.
		 *  \see Ready().
		 *
		 * Odbiera jeden bajt danych.
		 *
		 */
		char Recv(void);

		/*! \brief Odbiera dane binarne.
		 *  \param [out]	pvData	Dane.
		 *  \param [in]	sBytes	Rozmiar danych.
		 *  \return Stan operacji:\n
		 *          false - nie pobrano wszystkich danych,\n
		 *          true - pobrano wszystkie dane.
		 *
		 * Odbiera dane aż do zapełnienia bufora podają ilościa bajtów. Gdy bufor wejścia opróżni się przed pobraniem wszystkich danych metoda zwróci wartość fałsz. Gdy uda się zapełnić bufor metoda zwróci wartość prawda.
		 *
		 */
		bool Recv(void* pvData, size_t sBytes);

		/*! \brief Sprawdzenie czy istnieją w buforze oczekujące dane.
		 *  \return Stan bufora wejścia.
		 *
		 * Jeśli w buforze wejścia oczekują dane do pobrania to funkcja zwróci wartość prawda, w przeciwnym razie zwróci fałsz.
		 *
		 */
		bool Ready(void) const;

		/*! \brief Oczekiwanie na dane.
		 *  \param [in] uTime Czas oczekiwania.
		 *  \return Stan bufora wejścia.
		 *  \todo Pomiar czasu. Tymaczasowo działa na nieskończony czas.
		 *
		 * Czeka określoną ilość milisekund na zdarzenie odbioru danych. Gdy zdarzenie w tym czasie nastąpi zwraca wartość prawda.
		 *
		 */
		bool Wait(unsigned uTime = 0) const;

};

#endif
