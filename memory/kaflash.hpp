/***********************************************************************
 *
 * Lightweight avr/eeprom C++ bindings for KALibs
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

#ifndef KAFLASH_HPP
#define KAFLASH_HPP

#include <avr/eeprom.h>

#include <stdlib.h>

/*! \file		kaflash.hpp
 *  \brief	Zawiera deklaracje klasy KAFlash.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file		kaflash.cpp
 *  \brief	Zawiera implementacje klasy KAFlash.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief		Model pamięci FLASH mikrokontrolera.
 *
 * Pozwala na łatwy dostęp do pamięci FLASH.
 *
 */
class KAFlash
{

	protected:

		unsigned Adress;	//!< Adres aktualnej komórki.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Start Określna początkowy adres pamięci flash.
		 *
		 * Zapamiętuje adres pamięci w którym za rozpocząć się wczytywanie lub zapis danych.
		 *
		 */
		KAFlash(unsigned Start = 0);

		/*! \brief		Odczytuje z pamięci bajt danych.
		 *  \return		Odczytane dane.
		 *
		 * Odczytuje z kolejnej komórki dane.
		 *
		 */
		char Read(void);

		/*! \brief		Odczytuje z pamięci wybraną ilość danych.
		 *  \param [out]	Data		Wskaźnik na pamięć do wpidania danych.
		 *  \param [in]	Size		Ilość danych do odczytania.
		 *
		 * Odczytuje z kolejnej komórki dane.
		 *
		 */
		void Read(void* Data, size_t Size);

		/*! \brief Zapisuje do pamięci bajt danych.
		 *  \param [in] Char Dane do zapisania.
		 *
		 * Wpisuje do kolejnej komórki pamięci wybrane dane.
		 *
		 */
		void Write(char Char);

		/*! \brief Zapisuje do pamięci wybraną ilość danych.
		 *  \param [in] Data	Wskaźnik na pamięć do zapisu.
		 *  \param [in] Size	Ilość danych do zapisania.
		 *
		 * Zapisuje do pamięci dane.
		 *
		 */
		void Write(const void* Data, size_t Size);

		/*! \brief		Ustala adres pamięci.
		 *  \param [in]	Start Nowy adres komórki.
		 *
		 * Zmienia dotychczasowy adres kolejnej komórki.
		 *
		 */
		void SetAdress(unsigned Start);

		/*! \brief		Zwraca adres pamięci.
		 *  \return		Start Adres aktualnej komórki.
		 *
		 * Zwraca adres kolejnej komórki pamięci.
		 *
		 */
		unsigned GetAdress(void) const;

		/*! \brief		Odczytuje z pamięci bajt danych.
		 *  \param [in]	Start Adres pamięci.
		 *  \return		Odczytane dane.
		 *
		 * Odczytuje z wybranej komórki dane.
		 *
		 */
		static char Read(unsigned Start);

		/*! \brief		Zapisuje do pamięci bajt danych.
		 *  \param [in]	Start	Adres pamięci.
		 *  \param [in]	Char		Dane do zapisania.
		 *
		 * Wpisuje do wybrnej komórki pamięci wybrane dane.
		 *
		 */
		static void Write(unsigned Start, char Char);

};

#endif
