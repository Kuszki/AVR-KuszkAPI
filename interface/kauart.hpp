/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR UART C++ bindings for KALibs                           *
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

#ifndef _KALIBS_KACOMPORT_HPP
#define _KALIBS_KACOMPORT_HPP

#include <stdlib.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define BUFF_SIZE 64	//!< Rozmiar bufora wejścia/wyjścia.

/*! \file		kauart.hpp
 *  \brief	Zawiera deklaracje klasy KAUart.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file		kauart.cpp
 *  \brief	Zawiera implementacje klasy KAUart.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief Obsługa połączeń przychodzących i wychodzących portu szeregowego.
 *  \note Ze względu na prostotę zrezygnowano z rozwiązania szablonowego.
 *
 * Klasa umożliwia wysyłanie i odbieranie danych za pośrednictwem interfejsu UART.
 *
 */
class KAUart
{
	/*! \brief Wyliczenie przepustowości łącza.
	 *
	 * Umożliwia użycie standardowych wartości prędkości transmisji UART.
	 *
	 */
	public: enum BAUD : unsigned long
	{
		B_1200	= 1200,	//!< Transmisja 1200 bps.
		B_2400	= 2400,	//!< Transmisja 2400 bps.
		B_4800	= 4800,	//!< Transmisja 4800 bps.
		B_9600	= 9600,	//!< Transmisja 9600 bps.
		B_19200	= 19200,	//!< Transmisja 19200 bps.
		B_38400	= 38400,	//!< Transmisja 38400 bps.
		B_57600	= 57600,	//!< Transmisja 57600 bps.
		B_115200	= 115200	//!< Transmisja 115200 bps.
	};

	public:

		/*! \brief		Struktura bufora danych.
		 *
		 * Struktura ma na celu przechowywanie informacji o stanie bufora danych wejścia i wyjścia.
		 *
		 */
		struct Buffer
		{
			unsigned short Head;	//!< Koniec danych.
			unsigned short Tail;	//!< Początek danych.

			char Data[BUFF_SIZE];	//!< Bufor na dane.
		};

	protected:

		volatile static Buffer* IN;	//!< Bufor danych wejściowych.
		volatile static Buffer* OUT;	//!< Bufor danych wyjściowych.

		volatile unsigned Current;	//!< Aktualna pozycja przy odbieraniu pakietu.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Biterate Określa prędkość transmisji danych.
		 *
		 * Inicjuje rejestry informujące o parametrach transmisji danych..
		 *
		 */
		KAUart(BAUD Biterate = B_9600);

		/*! \brief		Destruktor obiektu.
		 *
		 * Wyłącza interfejs i zeruje stan rejestrów.
		 *
		 */
		~KAUart(void);

		/*! \brief		Inicjuje transmisje danych.
		 *
		 * Ustawia wybrane rejestry tak, by umożliwić transmisje danych przez port szeregowy.
		 *
		 */
		void Start(void);

		/*! \brief		Zatrzymuje działanie interfejsu.
		 *
		 * Czeka na wysłanie reszty danych i kończy działanie interfejsu.
		 *
		 */
		void Stop(void);

		/*! \brief		Wysyła jeden bajt danych.
		 *  \param [in]	Char Dane.
		 *
		 * Sprawdza czy bufor wejściowy nie jest przepełniony i wysyła wybrany bajt danych.
		 *
		 */
		void Send(char Char);

		/*! \brief		Wysyła ciąg znaków.
		 *  \param [in]	String Dane.
		 *
		 * Sprawdza czy bufor wejściowy nie jest przepełniony i wysyła dane na które wskazuje parametr funkcji aż do napotkania terminatora.
		 *
		 */
		void Send(const char* String);

		/*! \brief		Wysyła dane binarne.
		 *  \param [in]	Data		Dane.
		 *  \param [in]	Size		Rozmiar danych.
		 *
		 * Sprawdza czy bufor wejściowy nie jest przepełniony i wysyła podaną liczbę bajtów na które wskazuje parametr funkcji.
		 *
		 */
		void Send(const void* Data, size_t Size);

		/*! \brief		Wysyła znak z pamięci programu.
		 *  \param [in]	Adress	Adress danych w pamięci programu.
		 *
		 * Wysyła dane na które wskazuje parametr funkcji aż do napotkania terminatora.
		 *
		 */
		void SendPgmChar(unsigned Adress);

		/*! \brief		Wysyła ciąg znaków z pamięci programu.
		 *  \param [in]	Adress	Adress danych w pamięci programu.
		 *
		 * Wysyła dane na które wskazuje parametr funkcji aż do napotkania terminatora.
		 *
		 */
		void SendPgmString(unsigned Adress);

		/*! \brief		Wysyła ciąg znaków z pamięci programu.
		 *  \param [in]	Adress	Adress danych w pamięci programu.
		 *  \param [in]	Size		Rozmiar danych.
		 *
		 * Wysyła dane na które wskazuje parametr funkcji aż do napotkania terminatora.
		 *
		 */
		void SendPgmData(unsigned Adress, size_t Size);

		/*! \brief		Odbiera dane binarne.
		 *  \return		Odebrane dane.
		 *  \note			Gdy bufor wejściowy jest pusty metoda zwróci 0.
		 *  \see			Ready().
		 *
		 * Odbiera jeden bajt danych.
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
		bool Recv(void* Data, size_t Size);

		/*! \brief		Sprawdzenie czy istnieją w buforze oczekujące dane.
		 *  \return		Stan bufora wejścia.
		 *
		 * Jeśli w buforze wejścia oczekują dane do pobrania to funkcja zwróci wartość prawda, w przeciwnym razie zwróci fałsz.
		 *
		 */
		bool Ready(void) const;

		/*! \brief		Oczekiwanie na dane.
		 *  \param [in]	Time Czas oczekiwania.
		 *  \return		Stan bufora wejścia.
		 *  \todo			Pomiar czasu. Tymaczasowo działa na nieskończony czas.
		 *
		 * Czeka określoną ilość milisekund na zdarzenie odbioru danych. Gdy zdarzenie w tym czasie nastąpi zwraca wartość prawda.
		 *
		 */
		bool Wait(unsigned Time = 0) const;

		KAUart& operator << (unsigned Unsigned);
		KAUart& operator << (double Number);
		KAUart& operator << (int Integer);
		KAUart& operator << (bool Bool);

		KAUart& operator << (char Char);
		KAUart& operator << (const char* String);

		KAUart& operator << (const void* Adress);

		KAUart& operator >> (char& Char);

};

#endif
