/***********************************************************************
 *
 * Lightweight AVR PWM KAWaveform C++ bindings for KALibs
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

#ifndef _AVR_KUSZKAPI_WAVE_H
#define _AVR_KUSZKAPI_WAVE_H

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/*! \file		kawave.hpp
 *  \brief	Zawiera deklaracje klasy KAKAWave.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file		kawave.cpp
 *  \brief	Zawiera implementacje klasy KAKAWave.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief		Obsługa generowania impulsów z modulacją wypełnienia.
 *  \note			Klasa działa także z innymi płytkami, nie tylko z Arduino.
 *  \warning		Częstotliwość jest nastawiana wspólnie dla wszystkich generatorów.
 *
 * Klasa umożliwia automatyczne utworzenie generatora sygnału prostokątnego o podanym wypełnieniu i częstotliwości.
 *
 */
class KAWave
{

	/*! \brief		Enumeracja dostępnych generatorów.
	 *
	 * Określa numer generatora z którego chcemy skorzystać.
	 *
	 */
	public: enum WAVE
	{
		W_1	=	11,	//!< Pierwszy generator - pin 11.
		W_2	=	3	//!< Drugi generator - pin 3.
	};

	/*! \brief Enumeracja dostępnych częstotliwości.
	 *
	 * Określa częstotliwość przebiegu z której korzystamy.
	 *
	 */
	public: enum FREQ
	{
		OFF,			//!< Zerowa częstotliwość - brak generacji.
		F_62500,		//!< Częstotliwość 62500 Hz.
		F_31400,		//!< Częstotliwość 31373 Hz.
		F_7800,		//!< Częstotliwość 7812,5 Hz.
		F_4000,		//!< Częstotliwość 3921,6 Hz.
		F_2000,		//!< Częstotliwość 1953,1 Hz.
		F_1000,		//!< Częstotliwość 980,39 Hz.
		F_500,		//!< Częstotliwość 490,20 Hz.
		F_250,		//!< Częstotliwość 245,10 Hz.
		F_120,		//!< Częstotliwość 122,55 Hz.
		F_60,		//!< Częstotliwość 61,035 Hz.
		F_30			//!< Częstotliwość 30,637 Hz.
	};

	protected:

		static unsigned char Scale;	//!< Aktualnie używany prescaler wybrany na podstwie trybu pracy i częstotliwości.
		static unsigned char Mode;	//!< Określa tryb pracy generatorów na podstawie wybranej częstotliwości.

		const WAVE ID;				//!< Stały indeks używanego generatora.

		unsigned char Count;		//!< Liczba impulsów do zliczenia.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Number Określna numer użytego generatora.
		 *  \warning		Nie dokonuję się sprawdzania czy wybrany generator jest w użyciu. Należy zatem pamiętać by nie dublować generatorów.
		 *
		 * Inicjuje wszystkie pola obiektu na zero.
		 *
		 */
		KAWave(WAVE Number);

		/*! \brief		Destruktor obiektu.
		 *
		 * Zatrzymuje bierzący generator, nie zeruje jednak jego stanu.
		 *
		 */
		~KAWave(void);

		/*! \brief		Aktywuje generator.
		 *  \return		Powodzenie operacji.
		 *
		 * Sprawdza poprawność danych i aktywuje generator. Gdy operacja powiedzie się zwraca wartość true, w przeciwnym wypadku zwraca false.
		 *
		 */
		bool Start(void);

		/*! \brief		Wyłącza generator.
		 *
		 * Wyłącza aktywny generator bez resetowania ustawień. Aby wznowić działanie generatora bez potrzeby obliczania parametrów i ustalania flag użyj metody Resume().
		 *
		 */
		void Stop(void);

		/*! \brief		Wznawia generator.
		 *
		 * Przywraca pracę wybranego generatora bez potrzeby obliczania na nowo jego parametrów.
		 *
		 */
		void Resume(void);

		/*! \brief		Aktywuje nowe ustawienia.
		 *  \return		Powodzenie operacji.
		 *  \see			SetFreq(), SetWidth().
		 *
		 * Wprowadza w życie nowe ustawienia generatora.
		 *
		 */
		bool Refresh(void);

		/*! \brief		Sprawdza czy generator jest aktywny.
		 *  \return		Stan generatora.
		 *
		 * Sprawdza czy dany generator jest aktywny. Zwraca true gdy czasomierz działa, lub false gdy jest wyłączony.
		 *
		 */
		bool Active(void) const;

		/*! \brief		Ustawia generator.
		 *  \param [in]	Width Wypełnienie przebiegu (od 0 do 255).
		 *
		 * Ustala wypełnienie generowanego przebiegu. Nie zmienia jednak aktualnej pracy generatora - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		void SetWidth(unsigned char Width);

		/*! \brief		Ustawia generator.
		 *  \param [in]	Freq Częstotliwość przebiegu w hercach (Hz).
		 *  \see			FREQ.
		 *
		 * Ustala odpowiednie parametry generatorów potrzebne do aktywowania ich na podstawie podanej częstotliwości. Nie zmienia jednak aktualnej pracy generatora - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		static void SetFreq(FREQ Freq);

};

#endif
