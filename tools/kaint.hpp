/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR Ext Int C++ bindings for KALibs                        *
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

#ifndef _KALIBS_KAINT_HPP
#define _KALIBS_KAINT_HPP

#include <avr/interrupt.h>
#include <avr/io.h>

/*! \file kaint.hpp
 *  \brief Zawiera deklaracje klasy KAInt.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file kaint.cpp
 *  \brief Zawiera implementacje klasy KAInt.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief Bindy ułatwiające używanie przerwania.
 *
 * Umozliwia definiowanie działania przerwań zewnętrznych `INT0` i `INT1`.
 *
 */
class KAInt
{

	/*! \brief Wyliczenie przerwań.
	 *
	 * Pozwala ogarniczyć pule przerwań.
	 *
	 */
	public: enum INT
	{
		INT_0,		//!< Przerwanie `INT0`.
		INT_1		//!< Przerwanie `INT1`.
	};

	/*! \brief Wyliczenie trybów.
	 *
	 * Pozwala ogarniczyć pule trybów.
	 *
	 */
	public: enum MODE
	{
		ON_LOW,		//!< Przerwanie generowane przy niskim stanie sygnału.
		ON_CHANGE,	//!< Przerwanie generowane przy zmianie stanu sygnału.
		ON_FALLING,	//!< Przerwanie generowane przy opadającym zboczu.
		ON_RISING		//!< Przerwanie generowane przy narastającym zboczu.
	};

	protected:

		const INT ID;	//!< Identyfikator przerwania.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Int	ID przerwania.
		 *   \param [in]	Mode	Tryb działania przerwania.
		 *
		 * Inicjuje wszystkie wymagane pola.
		 *
		 */
		KAInt(INT Int, MODE Mode = ON_RISING);

		~KAInt(void);

		/*! \brief		Ustalenie trybu pracy przerwania.
		 *  \param [in]	Mode	Tryb pracy.
		 *
		 * Ustala tryb pracy przerwania.
		 *
		 */
		void SetMode(MODE Mode);

		/*! \brief		Pobranie trybu pracy przerwania.
		 *  \return		Tryb pracy przerwania.
		 *
		 * Pobiera tryb pracy wybranego przerwania.
		 *
		 */
		MODE GetMode(void) const;

		/*! \brief		Aktywacja przerwania.
		 *
		 * Uaktywnia przerwanie.
		 *
		 */
		void Enable(void);

		/*! \brief		Deaktywacja przerwania.
		 *
		 * Deaktywuje przerwanie.
		 *
		 */
		void Disable(void);

		/*! \brief		Sprawdzenie stanu przerwania.
		 *  \return		Stan przerwania.
		 *
		 * Zwraca `true` gdy przerwanie jest aktywne, lub `false` gdy jest nieaktywne.
		 *
		 */
		bool Active(void) const;

		/*! \brief		Ustalenie trybu pracy przerwania.
		 *  \param [in]	Int	ID przerwania.
		 *  \param [in]	Mode	Tryb pracy.
		 *
		 * Ustala tryb pracy wybranego przerwania.
		 *
		 */
		static void SetMode(INT Int, MODE Mode);

		/*! \brief		Pobranie trybu pracy przerwania.
		 *  \param [in]	Int ID przerwania.
		 *  \return		Tryb pracy przerwania.
		 *
		 * Pobiera tryb pracy wybranego przerwania.
		 *
		 */
		static MODE GetMode(INT Int);

		/*! \brief		Aktywacja przerwania.
		 *  \param [in]	Int ID przerwania.
		 *
		 * Uaktywnia wybrane przerwanie.
		 *
		 */
		static void Enable(INT Int);

		/*! \brief		Deaktywacja przerwania.
		 *  \param [in]	Int ID przerwania.
		 *
		 * Deaktywuje wybrane przerwanie.
		 *
		 */
		static void Disable(INT Int);

		/*! \brief		Sprawdzenie stanu przerwania.
		 *  \param [in]	Int ID przerwania.
		 *  \return		Stan przerwania.
		 *
		 * Zwraca `true` gdy przerwanie jest aktywne, lub `false` gdy jest nieaktywne.
		 *
		 */
		static bool Active(INT Int);

};

#endif
