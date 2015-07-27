/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  `new` and `delete` operators C++ bindings for KALibs                   *
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

#ifndef _KALIBS_KAMEMORY_HPP
#define _KALIBS_KAMEMORY_HPP

#include <stdlib.h>

#define FREE_RAM getFreeRAM()		//!< Makro wyświetlające dostępną pamięć RAM.

/*! \file		kamemory.hpp
 *  \brief	Zawiera deklaracje operatorów KLMemory.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \file		kamemory.cpp
 *  \brief	Zawiera implementacje operatorów KLMemory.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

/*! \brief		Uniwersalny operator `new`.
 *  \param [in]	Size Rozmiar pamięci.
 *  \return		Adres zaalokowanej pamięci.
 *
 * Alokuje wybraną ilość pamięci i zwraca wskaźnik na tą pamięć.
 *
 */
void* operator new (size_t Size);

/*! \brief		Uniwersalny operator `new[]`.
 *  \param [in]	Size Rozmiar pamięci.
 *  \return		Adres zaalokowanej pamięci.
 *
 * Alokuje wybraną ilość pamięci i zwraca wskaźnik na tą pamięć.
 *
 */
void* operator new[] (size_t Size);

/*! \brief		Uniwersalny operator `delete`.
 *  \param [in]	Pointer Pamięć do zwolnienia.
 *
 * Zwalnia wybraną pamięć.
 *
 */
void operator delete (void* Pointer);

/*! \brief		Uniwersalny operator `delete[]`.
 *  \param [in]	Pointer Pamięć do zwolnienia.
 *
 * Zwalnia wybraną pamięć.
 *
 */
void operator delete[] (void* Pointer);

/*! \brief		Pobranie iloście wolnej pamięci.
 *  \return		Wolna pamięć w bajtach.
 *
 * Oblicza i zwraca wolną ilość pamięci RAM.
 *
 */
size_t getFreeRAM(void);

#endif
