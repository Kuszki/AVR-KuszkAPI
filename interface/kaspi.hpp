/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR SPI C++ bindings for KALibs                            *
 *  Copyright (C) 2015  Łukasz "Kuszki" Dróżdż            l.drozdz@o2.pl   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the  Free Software Foundation, either  version 3 of the  License, or   *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This  program  is  distributed  in the hope  that it will be useful,   *
 *  but WITHOUT ANY  WARRANTY;  without  even  the  implied  warranty of   *
 *  MERCHANTABILITY  or  FITNESS  FOR  A  PARTICULAR  PURPOSE.  See  the   *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have  received a copy  of the  GNU General Public License   *
 *  along with this program. If not, see http://www.gnu.org/licenses/.     *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _KALIBS_KASPI_HPP
#define _KALIBS_KASPI_HPP

#include "../tools/kapin.hpp"

#include <stdlib.h>

#include <avr/interrupt.h>

/*! \file		kaspi.hpp
 *  \brief	Zawiera deklaracje klasy KASpi.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file		kaspi.cpp
 *  \brief	Zawiera implementacje klasy KASpi.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief 	Obsługa połączeń przychodzących i wychodzących portu szeregowego SPI.
 *  \note 	Ze względu na prostotę zrezygnowano z rozwiązania szablonowego.
 *
 * Klasa umożliwia wysyłanie i odbieranie danych za pośrednictwem interfejsu SPI.
 *
 */
class KASpi
{

	/*! \brief 	Wyliczenie roli urządzenia.
	 *
	 * Decyduje jaką rolę będzie miało wybrane urządzenie.
	 *
	 */
	public: enum MODE
	{
		MASTER,	//!< Oznacza rolę `master` urządzenia.
		SLAVE	//!< Oznacza rolę `slave` urządzenia.
	};

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Mode Określa rolę urządzenia.
		 *
		 * Inicjuje rejestry informujące o parametrach transmisji danych..
		 *
		 */
		KASpi(MODE Mode = MASTER);

		/*! \brief		Destruktor obiektu.
		 *
		 * Wyłącza interfejs i zeruje stan rejestrów.
		 *
		 */
		~KASpi(void);

		/*! \brief		Wybór urządzenia odbiorczego.
		 *  \param [in]	Port	Port do którego podłączono sygnał CS.
		 *  \param [in]	Mask	Maska wyprowadzenia.
		 *  \note			Do użytku tylko przy pracy jako `master`.
		 *
		 * Ustawia wybrany pin na stan niski w celu aktywacji sygnału CS.
		 *
		 */
		void Select(KAPin::PORT Port, char Mask);

		/*! \brief		Zwolnienie urządzenia odbiorczego.
		 *  \param [in]	Port	Port do którego podłączono sygnał CS.
		 *  \param [in]	Mask	Maska wyprowadzenia.
		 *  \note			Do użytku tylko przy pracy jako `master`.
		 *
		 * Ustawia wybrany pin na stan wysoki w celu zwolnienia sygnału CS.
		 *
		 */
		void Unselect(KAPin::PORT Port, char Mask);

		/*! \brief		Wysłanie porcji danych.
		 *  \param [in]	Dane do wysłania.
		 *  \warning		Do użytku tylko przy pracy jako `master`. Aby wysłać dane jako `slave` należy zrobić to podczas przerwania sygnalizującego odbiór danych `SPI_vect`.
		 *
		 * Wysyła jeden bajt danych.
		 *
		 */
		void Send(char Char);

		/*! \brief		Wysyła ciąg znaków.
		 *  \param [in]	String Dane.
		 *
		 * Wysyła dane na które wskazuje parametr funkcji aż do napotkania terminatora.
		 *
		 */
		void Send(const char* String);

		/*! \brief		Wysyła dane binarne.
		 *  \param [in]	Data		Dane.
		 *  \param [in]	Size		Rozmiar danych.
		 *
		 * Wysyła podaną liczbę bajtów na które wskazuje parametr funkcji.
		 *
		 */
		void Send(const void* Data, size_t Size);

		/*! \brief		Odebranie porcji danych.
		 *  \param [in]	Dane do wysłania.
		 *  \warning		Do użytku tylko przy pracy jako `master`. Aby odebrać dane jako `slave` należy zrobić to podczas przerwania sygnalizującego odbiór danych `SPI_vect`.
		 *
		 * Wysyła pusty bajt w celu wymuszenia odbioru danych z urządzenia `slave`.
		 *
		 */
		char Recv(void);

		/*! \brief		Odbiera dane binarne.
		 *  \param [out]	Data		Dane.
		 *  \param [in]	Size		Rozmiar danych.
		 *  \return		Stan operacji:\n
		 *          		false - nie pobrano wszystkich danych,\n
		 *          		true - pobrano wszystkie dane.
		 *
		 * Odbiera dane aż do zapełnienia bufora podają ilościa bajtów. Gdy bufor wejścia opróżni się przed pobraniem wszystkich danych metoda zwróci wartość fałsz. Gdy uda się zapełnić bufor metoda zwróci wartość prawda.
		 *
		 */
		void Recv(void* Data, size_t Size);

		KASpi& operator << (char Char);
		KASpi& operator << (const char* String);

		KASpi& operator >> (char& Char);

};

#endif
