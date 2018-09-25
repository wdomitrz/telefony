/** @file
 * Interfejs operacji znajdowania przekierowania z implementacją w pliku
 * @ref phone_forward_get.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_FORWARD_GET_H
#define TEL_PHONE_FORWARD_GET_H

#include "phone_numbers.h"
#include "phone_forward_struct.h"

/** @brief Wyznacza przekierowanie numeru.
 * Działa jak @ref phfwdGet.
 * Wyznacza przekierowanie podanego numeru. Szuka najdłuższego pasującego
 * prefiksu. Wynikiem jest co najwyżej jeden numer. Jeśli dany numer nie został
 * przekierowany, to wynikiem jest ten numer. Jeśli podany napis nie
 * reprezentuje numeru, wynikiem jest pusty ciąg. Alokuje strukturę
 * @ref PhoneNumbers, która musi być zwolniona za pomocą funkcji
 * @ref phnumDelete.
 * @param[in] phoneForward – wskaźnik na strukturę przechowującą przekierowania
 *                            numerów;
 * @param[out] phoneForward – wskaźnik na tą samą strukturę po wykonaniu na
 *                            niej opisanej w @ref phoneForwardGet operacji;
 * @param[in, out] number – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub @c NULL, gdy
 *         nie udało się zaalokować pamięci.
 */
struct PhoneNumbers const *phoneForwardGet(struct PhoneForward *phoneForward,
                                           char const *number);

#endif //TEL_PHONE_FORWARD_GET_H
