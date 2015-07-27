/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR Pins C++ bindings for KALibs                           *
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

#ifndef _KALIBS_KAPIN_HPP
#define _KALIBS_KAPIN_HPP

#define PORT_0		0b00000001			//!< Bit 0.
#define PORT_1		0b00000010			//!< Bit 1.
#define PORT_2		0b00000100			//!< Bit 2.
#define PORT_3		0b00001000			//!< Bit 3.
#define PORT_4		0b00010000			//!< Bit 4.
#define PORT_5		0b00100000			//!< Bit 5.
#define PORT_6		0b01000000			//!< Bit 6.
#define PORT_7		0b10000000			//!< Bit 7.

#define PD_0		KAPin::PORT_D, PORT_0	//!< Port D, bit 0.
#define PD_1		KAPin::PORT_D, PORT_1	//!< Port D, bit 1.
#define PD_2		KAPin::PORT_D, PORT_2	//!< Port D, bit 2.
#define PD_3		KAPin::PORT_D, PORT_3	//!< Port D, bit 3.
#define PD_4		KAPin::PORT_D, PORT_4	//!< Port D, bit 4.
#define PD_5		KAPin::PORT_D, PORT_5	//!< Port D, bit 5.
#define PD_6		KAPin::PORT_D, PORT_6	//!< Port D, bit 6.
#define PD_7		KAPin::PORT_D, PORT_7	//!< Port D, bit 7.

#define PB_0		KAPin::PORT_B, PORT_0	//!< Port B, bit 0.
#define PB_1		KAPin::PORT_B, PORT_1	//!< Port B, bit 1.
#define PB_2		KAPin::PORT_B, PORT_2	//!< Port B, bit 2.
#define PB_3		KAPin::PORT_B, PORT_3	//!< Port B, bit 3.
#define PB_4		KAPin::PORT_B, PORT_4	//!< Port B, bit 4.
#define PB_5		KAPin::PORT_B, PORT_5	//!< Port B, bit 5.
#define PB_6		KAPin::PORT_B, PORT_6	//!< Port B, bit 6.
#define PB_7		KAPin::PORT_B, PORT_7	//!< Port B, bit 7.

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
