/** @file
 * Interfejs operacji dodawania przekierowania z implementacją w pliku
 * @ref phone_forward_add.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_FORWARD_ADD_H
#define TEL_PHONE_FORWARD_ADD_H

#include <stdbool.h>
#include "phone_forward_struct.h"

/** @brief Dodaje przekierowanie.
 * Działa tak samo jak @ref phfwdAdd.
 * Dodaje przekierowanie wszystkich numerów mających prefiks @p number1, na
 * numery, w których ten prefiks zamieniono odpowiednio na prefiks @p number2.
 * Każdy numer jest swoim własnym prefiksem. Jeśli wcześniej zostało dodane
 * przekierowanie z takim samym parametrem @p number1, to jest ono zastępowane.
 * @param[in] phoneForward – wskaźnik na strukturę przechowującą przekierowania
 *                           numerów;
 * @param[out] phoneForward – wskaźnik na tą samą strukturę po wykonaniu na
 *                            niej opisanej w @ref phoneForwardAdd operacji;
 * @param[in, out] number1 – wskaźnik na napis reprezentujący prefiks numerów
 *                           przekierowywanych;
 * @param[in, out] number2 – wskaźnik na napis reprezentujący prefiks numerów,
 *                           na które jest wykonywane przekierowanie.
 * @return Wartość @c true, jeśli przekierowanie zostało dodane.
 *         Wartość @c false, jeśli wystąpił błąd, np. podany napis nie
 *         reprezentuje numeru, oba podane numery są identyczne lub nie udało
 *         się zaalokować pamięci.
 */
bool phoneForwardAdd(struct PhoneForward *phoneForward, char const *number1,
                     char const *number2);

#endif //TEL_PHONE_FORWARD_ADD_H
