/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR Outputs C++ bindings for KALibs                        *
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

#ifndef _KALIBS_KAOUTPUT_HPP
#define _KALIBS_KAOUTPUT_HPP

#include "../tools/kapin.hpp"

#ifndef DELAY
#define DELAY(t) { unsigned i = t; while (i--) _delay_ms(1); }	//!< Makro pozwalające wybrać w jakiej metody używać w celu generacji opóźnienia.
#endif

#include <util/delay.h>

/*! \file kaoutput.hpp
 *  \brief Zawiera deklaracje klasy KAOutput.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file kaoutput.cpp
 *  \brief Zawiera implementacje klasy KAOutput.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief Reprezentacja cyfrowego wyjścia.
 *
 * Pozwala na łatwą obsługę wyjść cyfrowych.
 *
 */
class KAOutput : public KAPin
{

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Port		Port wyprowadzenia.
		 *  \param [in]	Mask		Maska bitowa.
		 *
		 * Inicjuje wszystkie pola obiektu i ustala wyprowadzenie portu na wyjściowe.
		 *
		 */
		KAOutput(PORT Port, char Mask);

		/*! \brief Destruktor obiektu.
		 *
		 * Wyłącza diodę i ustawia jej pin na wejściowy.
		 *
		 */
		~KAOutput(void);

		/*! \brief Uaktywnia wyjście.
		 *
		 * Ustala stan wysoki na wyjściu.
		 *
		 */
		void On(void);

		/*! \brief Deaktywuje wyjście.
		 *
		 * Ustala stan niski na wyjściu.
		 *
		 */
		void Off(void);

		/*! \brief Przełącza wyjście.
		 *
		 * Ustala odwrotny stan na wyjściu.
		 *
		 */
		void Switch(void);

		/*! \brief		Ustala stan wyjścia.
		 *  \param [in]	State Nowy stan wyjścia.
		 *  \see			On(), Off().
		 *
		 * Zmienia dotychczasowy stan wyjścia na wybrany.
		 *
		 */
		void SetState(bool State);

		/*! \brief		Sprawdza stan wyjścia.
		 *  \return		Aktualny stan wyjścia.
		 *
		 * Pobiera aktualny stan wyjścia.
		 *
		 */
		bool GetState(void) const;

		/*! \brief		Ustala stan wyjścia.
		 *  \param [in]	Port		Port wyprowadzenia.
		 *  \param [in]	Mask		Maska bitowa.
		 *  \param [in]	State	Nowy stan wyjścia.
		 *
		 * Zmienia dotychczasowy stan wyjścia na wybrany.
		 *
		 */
		static void SetState(PORT Port, char Mask,  bool State);

		/*! \brief		Sprawdza stan wyjścia.
		 *  \param [in]	Port		Port wyprowadzenia.
		 *  \param [in]	Mask		Maska bitowa.
		 *  \return		Aktualny stan wyjścia.
		 *
		 * Pobiera aktualny stan wyjścia.
		 *
		 */
		static bool GetState(PORT Port, char Mask);

		/*! \brief Przełącza wyjście.
		 *  \param [in]	Port		Port wyprowadzenia.
		 *  \param [in]	Mask		Maska bitowa.
		 *  \param [in]	Count	Liczba zmian stanu.
		 *  \param [in]	Delay	Opóźnienie według wybranego algorytmu.
		 *  \see			Delay(t).
		 *
		 * Ustala odwrotny stan na wyjściu wybraną ilość razy. Domyślnie jednostką opóźnienia jest wielokrotność `1 ms`.
		 *
		 */
		static void SwitchState(PORT Port, char Mask, char Count = 1, char Delay = 1);

};

#endif
