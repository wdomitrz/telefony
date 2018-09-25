/** @file
 * Interfejs funkcji obliczania liczby nietrywialnych numerów z implementacją w
 * pliku @ref phone_forward_non_trivial_count.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 08.06.2018
 */

#ifndef TELEFONY_PHONE_FORWARD_NON_TRIVIAL_COUNT_H
#define TELEFONY_PHONE_FORWARD_NON_TRIVIAL_COUNT_H

#include <stdlib.h>
#include "phone_forward_struct.h"

/** @brief Funkcja oblicza liczbę nietrywialnych numerów.
 * Działa jak @ref phfwdNonTrivialCount.
 * Funkcja oblicza liczbę nietrywialnych numerów długości len zawierających
 * tylko cyfry, które znajdują się w napisie set. Obliczenia wykonuje modulo
 * @c 2 do potęgi liczba bitów reprezentacji typu @c size_t. Napis @p set może
 * zawierać dowolne znaki.
 * @param[in] phoneForward  – wskaźnik na strukturę przechowującą przekierowania
 *                            numerów;
 * @param[out] phoneForward – wskaźnik na tą samą strukturę;
 * @param set – wskaźnik na napis;
 * @param length – długość zliczanych numerów telefonów.
 * @return Wartość @c 0, jeśli wskaźnik @p pf ma wartość @c NULL, @p set ma
 *         wartość @c NULL @p set jest pusty, @p set nie zawiera żadnej cyfry
 *         lub parametr @p len jest równy zeru.
 *         W przeciwnym przypadku szukaną liczbę modulo @c 2 do potęgi liczba
 *         bitów reprezentacji typu @c size_t.
 */
size_t phoneForwardNonTrivialCount(struct PhoneForward *phoneForward,
                                   char const *set, size_t length);

#endif //TELEFONY_PHONE_FORWARD_NON_TRIVIAL_COUNT_H
