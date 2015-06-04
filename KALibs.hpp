/***********************************************************************
 *
 * KALibs - Lightweight C++ AVR libs
 * Copyright (C) Łukasz "Kuszki" Dróżdż  2015
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

/*! \file		KALibs.hpp
 *  \brief	Pomocnicze deklaracje.
 *
 * Dołącza cały projekt przy pomocy jednego pliku.
 *
 */

/*! \page		links Linki
 *
 *  \section	source Kod źródłowy
 *
 * - [Projekt w serwisie GitHub](https://github.com/Kuszki/KALibs)
 *
 *  \section	license Licencja
 *
 * - [GNU GPL v2 angielski](http://www.gnu.org/licenses/gpl-2.0.html)
 * - [GNU GPL v2 polski](http://gnu.org.pl/text/licencja-gnu.html)
 *
 *  \section	author Autor
 *
 * - [Profil GitHub](https://github.com/Kuszki)
 * - [e-mail](l.drozdz@o2.pl)
 *
 */

#ifndef KALIBS_GLOBAL_HPP
#define KALIBS_GLOBAL_HPP

#include "memory/kamemory.hpp"
#include "memory/kaflash.hpp"

#include "interface/kauart.hpp"

#include "tools/kapin.hpp"
#include "tools/katimer.hpp"

#include "outputs/kaoutput.hpp"
#include "outputs/kawave.hpp"

#include "inputs/kaswitch.hpp"
#include "inputs/kaconverter.hpp"

#endif // KALIBS_GLOBAL_HPP
