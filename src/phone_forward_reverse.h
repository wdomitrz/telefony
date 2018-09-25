/** @file
 * Interfejs operacji znajdowania odwrotności przekierowania z implementacją w
 * pliku @ref phone_forward_reverse.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_FORWARD_REVERSE_H
#define TEL_PHONE_FORWARD_REVERSE_H

#include "phone_numbers.h"
#include "phone_forward_struct.h"

/** @brief Wyznacza przekierowania na dany numer.
 * Działa jak @ref phfwdReverse.
 * Wyznacza wszystkie przekierowania na podany numer. Wynikowy ciąg zawiera też
 * dany numer. Wynikowe numery są posortowane leksykograficznie i nie mogą się
 * powtarzać. Jeśli podany napis nie reprezentuje numeru, wynikiem jest pusty
 * ciąg. Alokuje strukturę @c PhoneNumbers, która musi być zwolniona za pomocą
 * funkcji @ref phnumDelete.
 * @param[in] phoneForward – wskaźnik na strukturę przechowującą przekierowania
 *                           numerów;
 * @param[out] phoneForward – wskaźnik na tą samą stukturę po wykonaniu na niej
 *                            opisanej w @ref phoneForwardReverse operacji
 * @param[in, out] number – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub @c NULL, gdy nie
 *         udało się zaalokować pamięci.
 */
struct PhoneNumbers const *phoneForwardReverse(struct PhoneForward *phoneForward,
                                               char const *number);

#endif //TEL_PHONE_FORWARD_REVERSE_H
