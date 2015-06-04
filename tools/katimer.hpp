/***********************************************************************
 *
 * Lightweight AVR Timers C++ bindings for KALibs
 * Copyright (C) 2015  Łukasz "Kuszki" Dróżdż
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **********************************************************************/

#ifndef KATIMER_HPP
#define KATIMER_HPP

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/*! \file		katimer.hpp
 *  \brief	Zawiera deklaracje klasy KATimer.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file		katimer.cpp
 *  \brief	Zawiera implementacje klasy KATimer.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief		Obsługa przerwań licznika czasu.
 *  \note			Przerwanie wybranego timera należy zaimplementować ręcznie.
 *  \note			Klasa działa także z innymi płytkami, nie tylko z Arduino.
 *  \bug			Po aktywacji licznika metodą Start() zdarza się, że pierwsze wyzwolenie nastąpi w nieokreślonym czasie. Takie działanie ma miejsce gdy ręcznie załączymy zliczanie w trakcie programu. Timer aktywowany na początku programu działa zwykle poprawnie. Bug dotyczy tylko pierwszego wyzwolenia. Zdarzenie odnotowano tylko dla licznika T2 - dla pozostałych liczników nie przeprowadzono testów.
 *
 * Klasa umożliwia automatyczne utworzenie przerwania wywoływanego z określoną częstotliowścią lub określonym czasem.
 *
 * Aby obsłużyć główne zdarzenie zdefiniuj w programie przerwanie TIMERX_COMPA_vect, gdzie X to numer licznika (0, 1 lub 2). W celu obsłurzenie przerwania pomocniczego adefiniuj przerwanie TIMERX_COMPB_vect.
 *
 */
class Timer
{

	/*! \brief		Enumeracja dostępnych liczników.
	 *
	 * Określa numer licznika z którego chcemy skorzystać.
	 *
	 */
	public: enum TIMER
	{
		T1,	//!< Pierwszy licznik - zakres od 0 do 255; przerwanie TIMER0_COMPA_vect i TIMER0_COMPB_vect.
		T2	//!< Drugi licznik - zakres od 0 do 65535; przerwanie TIMER1_COMPA_vect i TIMER1_COMPB_vect.
	};

	/*! \brief		Enumeracja dostępnych prescalerów.
	 *
	 * Określa prescaler z którego korzystamy.
	 *
	 */
	public: enum SCALER
	{
		OFF,		//!< Zerowy prescaler - brak zliczania.
		P1,		//!< Prescaler 1/1.
		P8,		//!< Prescaler 1/8.
		P64,		//!< Prescaler 1/64.
		P256,	//!< Prescaler 1/265.
		P1024	//!< Prescaler 1/1024.
	};

	protected:

		const TIMER ID;		//!< Stały indeks używanego licznika.

		unsigned char Scale;	//!< Aktualnie używany prescaler.

		unsigned Count;		//!< Liczba impulsów do zliczenia.
		unsigned Prev;		//!< Impulsy do pierwszego zdarzenia.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Number Określna numer użytego licznika.
		 *  \warning		Nie dokonuję się sprawdzania czy wybrany licznik jest w użyciu. Należy zatem pamiętać by nie dublować liczników.
		 *
		 * Inicjuje wszystkie pola obiektu na zero.
		 *
		 */
		Timer(TIMER Number);

		/*! \brief		Destruktor obiektu.
		 *
		 * Zatrzymuje bierzący licznik, nie zeruje jednak jego stanu.
		 *
		 */
		~Timer(void);

		/*! \brief		Aktywuje licznik.
		 *  \return		Powodzenie operacji.
		 *
		 * Sprawdza poprawność danych i aktywuje licznik. Gdy operacja powiedzie się zwraca wartość true, w przeciwnym wypadku zwraca false.
		 *
		 */
		bool Start(void);

		/*! \brief		Wyłącza licznik.
		 *
		 * Wyłącza aktywny licznik bez resetowania jego pozycji. Aby wznowić działanie licznika bez potrzeby obliczania parametrów i ustalania flag użyj metody Resume().
		 *
		 */
		void Stop(void);

		/*! \brief		Zeruje licznik i restartuje pomiar.
		 *
		 * Powoduje, że cykl zliczania zaczyna się od nowa.
		 *
		 */
		void Reset(void);

		/*! \brief		Wznawia licznik.
		 *
		 * Przywraca pracę wybranego licznika bez potrzeby obliczania na nowo jego parametrów.
		 *
		 */
		void Resume(void);

		/*! \brief		Aktywuje nowe ustawienia.
		 *  \return		Powodzenie operacji.
		 *  \see			SetFreq(), SetTime(), SetPrefs().
		 *
		 * Wprowadza w życie nowe ustawienia licznika.
		 *
		 */
		bool Refresh(void);

		/*! \brief		Sprawdza czy licznik jest aktywny.
		 *  \return		Stan licznika.
		 *
		 * Sprawdza czy dany licznik jest aktywny. Zwraca true gdy czasomierz działa, lub false gdy jest wyłączony.
		 *
		 */
		bool Active(void) const;

		/*! \brief		Ustawia licznik.
		 *  \param [in]	FreqA	Częstotliwość wyzwalania w hercach (Hz).
		 *  \param [in]	FreqB	Częstotliwość wyzwalania pomocniczego zdarzenia w hercach (Hz).
		 *  \note			Jeśli chcesz nastawić częstotliwość poniżej 1Hz możesz użyć funkcji SetTime().
		 *
		 * Ustala odpowiednie parametry licznika potrzebne do aktywowania go na podstawie podanej częstotliwości wyzwalania zdarzenia. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		void SetFreq(unsigned long FreqA, unsigned long FreqB = 0);

		/*! \brief		Ustawia licznik.
		 *  \param [in]	TimeA	Okres wyzwalania zdarzenia w mikrosekundach (us).
		 *  \param [in]	TimeB	Okres wyzwalania pomocniczego zdarzenia w mikrosekundach (us) - musi być większy od okresu pierwszego wydarzenia.
		 *
		 * Ustala odpowiednie parametry licznika potrzebne do aktywowania go na podstawie podanego czasu. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		void SetTime(unsigned long TimeA, unsigned long TimeB = 0);

		/*! \brief		Ustawia licznik.
		 *  \param [in]	Scale	Wybrany prescaler.
		 *  \param [in]	CapA	Wybrana pojemność zdarzenia.
		 *  \param [in]	CapB	Pojemność pierwszego zdarzenia.
		 *  \warning		Istotne jest by parametry były zgodne ze specyfikacją licznika. Nie będą one bowiem sprawdzane pod kątem poprawności szerokości licznika.
		 *  \see			SCALER.
		 *
		 * Ustala ręcznie odpowiednie parametry licznika potrzebne do aktywowania go. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start().
		 *
		 */
		void SetPrefs(SCALER Scale, unsigned CapA, unsigned CapB = 0);

};

#endif
