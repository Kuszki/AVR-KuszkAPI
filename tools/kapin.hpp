/***********************************************************************
 *
 * Lightweight AVR Pins C++ bindings for KALibs
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

#ifndef _KALIBS_KAPIN_HPP
#define _KALIBS_KAPIN_HPP

#define PIN_0		KAPin::PORT_D, 1		//!< Pin 0.
#define PIN_1		KAPin::PORT_D, 2		//!< Pin 1.
#define PIN_2		KAPin::PORT_D, 4		//!< Pin 2.
#define PIN_3		KAPin::PORT_D, 8		//!< Pin 3.
#define PIN_4		KAPin::PORT_D, 16		//!< Pin 4.
#define PIN_5		KAPin::PORT_D, 32		//!< Pin 5.
#define PIN_6		KAPin::PORT_D, 64		//!< Pin 6.
#define PIN_7		KAPin::PORT_D, 128		//!< Pin 7.

#define PIN_8		KAPin::PORT_B, 1		//!< Pin 8.
#define PIN_9		KAPin::PORT_B, 2		//!< Pin 9.
#define PIN_10		KAPin::PORT_B, 4		//!< Pin 10.
#define PIN_11		KAPin::PORT_B, 8		//!< Pin 11.
#define PIN_12		KAPin::PORT_B, 16		//!< Pin 12.
#define PIN_13		KAPin::PORT_B, 32		//!< Pin 13.

#include <avr/io.h>

/*! \file kapin.hpp
 *  \brief Zawiera deklaracje klasy KAPin.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file kapin.cpp
 *  \brief Zawiera implementacje klasy KAPin.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief Reprezentacja pinu.
 *
 * Pozwala na łatwą obsługę wyjść i wyjść cyfrowych.
 *
 */
class KAPin
{

	/*! \brief Wyliczenie portów.
	 *
	 * Pozwala ogarniczyć pule portów.
	 *
	 */
	public: enum PORT
	{
		PORT_B,	//!< Port B.
		PORT_D	//!< Port A.
	};

	protected:

		const char MASK;	//!< Maska dla wyprowadzenia.

		const PORT ID;		//!< Port wejścia/wyjścia.

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Port		ID portu.
		 *  \param [in]	Mask		Maska bitowa.
		 *
		 * Inicjuje wszystkie wymagane pola.
		 *
		 */
		KAPin(PORT Port,
			 char Mask);

	public:

		/*! \brief		Pobranie wejścia.
		 *  \return		Referencja do wybranego wejścia.
		 *
		 * Zwraca referencje do rejestru opisującego wybrane wejścia.
		 *
		 */
		static volatile unsigned char& GetPin(PORT Port);

		/*! \brief		Pobranie portu.
		 *  \return		Referencja do wybranego portu.
		 *
		 * Zwraca referencje do rejestru opisującego wybrany port.
		 *
		 */
		static volatile unsigned char& GetPort(PORT Port);

		/*! \brief		Pobranie flag portu.
		 *  \return		Referencja do flag wybranego portu.
		 *
		 * Zwraca referencje do rejestru opisującego flagi wybranego port.
		 *
		 */
		static volatile unsigned char& GetFlag(PORT Port);

		/*! \brief		Ustalenie portu jako wyjście.
		 *  \param [in]	Port		ID portu.
		 *  \param [in]	Mask		Maska bitowa.
		 *
		 * Ustawia wybrane za pomocą maski wyprowadzenia na wyjściowe.
		 *
		 */
		static void SetOutputMode(PORT Port,
							 char Mask);

		/*! \brief		Ustalenie portu jako wejście.
		 *  \param [in]	Port		ID portu.
		 *  \param [in]	Mask		Maska bitowa.
		 *
		 * Ustawia wybrane za pomocą maski wyprowadzenia na wejściowe.
		 *
		 */
		static void SetInputMode(PORT Port,
							char Mask);

		/*! \brief		Ustalenie portu jako wejście z pullupem.
		 *  \param [in]	Port		ID portu.
		 *  \param [in]	Mask		Maska bitowa.
		 *
		 * Ustawia wybrane za pomocą maski wyprowadzenia na wejściowe z podciąganiem do 5 V.
		 *
		 */
		static void SetPullupMode(PORT Port,
							 char Mask);

};

#endif
