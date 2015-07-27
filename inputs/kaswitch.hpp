/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Lightweight AVR Switch Input C++ bindings for KALibs                   *
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

#ifndef _KALIBS_KASWITCH_HPP
#define _KALIBS_KASWITCH_HPP

/*! \file kaswitch.hpp
 *  \brief Zawiera deklaracje klasy KASwitch.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file kaswitch.cpp
 *  \brief Zawiera implementacje klasy KASwitch.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#include "../tools/kapin.hpp"

/*! \brief Przycisk "włącz/wyłącz".
 *
 * Pozwala na automatyczną obsługę przycisku cyfrowego bistabilnego i monostabilnego wraz z wyborem odpowiedniego zdarzenia i sposobem zachowania przycisku.
 *
 */
class KASwitch : public KAPin
{

	/*! \brief Sposób detekcji zdarzenia.
	 *
	 * Definiuje na jakie zbocze będzie reagował przycisk (przy jakim zboczu nastąpi zmiana jego stanu).
	 *
	 */
	public: enum EVENT
	{
		ON_SWITCH,	//!< Oznacza, że zdarzenie zmiany stanu będzie powiązane ze zmianą fizyczną przycisku.
		ON_RISING,	//!< Oznacza, że zdarzenie zmiany stanu będzie powiązane z narastaniem zbocza sygnału.
		ON_FALLING	//!< Oznacza, że zdarzenie zmiany stanu będzie powiązane z opadaniem zbocza sygnału.
	};

	/*! \brief Sposób podłączenia przycisku.
	 *
	 * Definiuje czy przycisk będzie podłączony bezpośrednio do masy (z wejściem podciągniętym do zasilania), czy będzie on zwykłym wejściem.
	 *
	 */
	public: enum MODE
	{
		NORMAL,		//!< Zwyczajne połączenie do zasilania.
		PULLUP		//!< Połączenie do masy z podciągniętym do zasilania wejściem.
	};

	protected:

		typedef void (*ONCHANGE)(bool); //!< Prototyp funkcji zwrotnej wywoływanej przy zdarzeniu przycisku.

		ONCHANGE Callback;	//!< Adres funkcji zwrotnej wywoływanej przy zmianie stanu przycisku.

		bool	Last;		//!< Ostatni zarejestrowany fizyczny stan przycisku.
		bool Active;		//!< Aktualny stan przycisku.

		char Count;		//!< Aktualna ilość wciśnięć przycisku.
		char Change;		//!< Ilość zmian fizycznego stanu potrzebna do zmiany stanu logicznego.

	public:

		/*! \brief		Konstruktor obiektu.
		 *  \param [in]	Port		ID portu.
		 *  \param [in]	Mask		Maska bitowa.
		 *  \param [in]	Proc		Adres funkcji zwrotnej do wywołania przy zmianie stanu przycisku.
		 *  \param [in]	Event	Sposób działania przycisku.
		 *  \param [in]	Mode		Rodzaj połączenia przycisku (wbudowany pullup lub ręczny pullup).
		 *  \see			EVENT, ONCHANGE.
		 *
		 * Inicjuje wszystkie pola obiektu i ustala wybrany port jako wejściowy.
		 *
		 */
		KASwitch(PORT Port,
			    char Mask,
			    ONCHANGE Proc = nullptr,
			    EVENT Event = ON_SWITCH,
			    MODE Mode = PULLUP);

		/*! \brief		Odświerza stan przycisku.
		 *  \return		Aktualny logiczny stan przycisku.
		 *  \note			Użyj tej metody wraz z każdą iteracją głównej pętli programu.
		 *
		 * Sprawdza fizyczne połorzenie przycisku i odświerza jego stan.
		 *
		 */
		bool Check(void);

		/*! \brief		Włącza przełącznik.
		 *  \param [in]	Call Wywołanie funkcji zwrotnej.
		 *  \note			Po użyciu na przełączniku o stabilnym stanie zmienia logiczne położenia przycisku.
		 *
		 * Symuluje włączenie przełącznka wraz z wywołaniem funkcji zwrotnej.
		 *
		 */
		void On(bool Call = true);

		/*! \brief		Wyłącza przełącznik.
		 *  \param [in]	Call Wywołanie funkcji zwrotnej.
		 *  \note			Po użyciu na przełączniku o stabilnym stanie zmienia logiczne położenia przycisku.
		 *
		 * Symuluje wyłączenie przełącznka wraz z wywołaniem funkcji zwrotnej.
		 *
		 */
		void Off(bool Call = true);

		/*! \brief		Ustala nowe zdarzenie zmiany stanu.
		 *  \param [in]	Proc Adres funkcji zwrotnej.
		 *  \see			ONCHANGE.
		 *
		 * Zmienia dotychczasowe działanie przycisku poprzez zdefiniowanie nowej funkcji zwrotnej.
		 *
		 */
		void SetAction(ONCHANGE Proc);

		/*! \brief		Ustala nowy sposób działania przycisku.
		 *  \param [in]	Event Sposób działania.
		 *  \see			MODE.
		 *
		 * Zmienia dotychczasowe działanie przycisku poprzez zdefiniowanie nowego sposobu działania.
		 *
		 */
		void SetMode(EVENT Event);

		/*! \brief		Ustala stan przycisku.
		 *  \param [in]	State Nowy stan przycisku.
		 *  \see			On(), Off().
		 *
		 * Zmienia dotychczasowy stan przycisku bez wywołania funkcji zwrotnej.
		 *
		 */
		void SetState(bool State);

};

#endif
