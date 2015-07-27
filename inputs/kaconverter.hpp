/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR ADC C++ bindings for KALibs                            *
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

#ifndef _KALIBS_KACONVERTER_HPP
#define _KALIBS_KACONVERTER_HPP

#include <avr/io.h>

class KAConverter
{

	/*! \brief Wyliczenie przetworników.
	 *
	 * Pozwala ogarniczyć pule przetworników ADC.
	 *
	 */
	public: enum PORT
	{
		ADC_0,	//!< Przetwornik 0.
		ADC_1,	//!< Przetwornik 1.
		ADC_2, 	//!< Przetwornik 2.
		ADC_3,	//!< Przetwornik 3.
		ADC_4,	//!< Przetwornik 4.
		ADC_5,	//!< Przetwornik 5.
		ADC_6,	//!< Przetwornik 6.
		ADC_7,	//!< Przetwornik 7.
	};

	protected:

		const PORT ID;		//!< Port wejściowy.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Port		ID portu.
		 *
		 * Inicjuje wszystkie wymagane pola.
		 *
		 */
		KAConverter(PORT Port);

		/*! \brief		Pobranie zmierzonej wartości w kwantach.
		 *  \return		Zmierzone napięcie w kwantach (0-1023).
		 *
		 * Wybiera przetwornik i odczytuje jego napięcie.
		 *
		 */
		unsigned GetValue(void) const;

		/*! \brief		Pobranie zmierzonej wartości w woltach.
		 *  \return		Zmierzone napięcie w woltach (0-5 V).
		 *
		 * Wybiera przetwornik i odczytuje jego napięcie.
		 *
		 */
		double GetVoltage(void) const;

		/*! \brief		Pobranie zmierzonej wartości w kwantach.
		 *  \param [in]	Port		ID portu.
		 *  \return		Zmierzone napięcie w kwantach (0-1023).
		 *
		 * Wybiera przetwornik i odczytuje jego napięcie.
		 *
		 */
		static unsigned GetValue(PORT Port);

		/*! \brief		Pobranie zmierzonej wartości w woltach.
		 *  \param [in]	Port		ID portu.
		 *  \return		Zmierzone napięcie w woltach (0-5 V).
		 *
		 * Wybiera przetwornik i odczytuje jego napięcie.
		 *
		 */
		static double GetVoltage(PORT Port);

};

#endif
