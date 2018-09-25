/** @file
 * Interfejs operacji usuwania przekierowania z implementacją w pliku
 * @ref phone_forward_remove.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_FORWARD_REMOVE_H
#define TEL_PHONE_FORWARD_REMOVE_H

#include "phone_forward_struct.h"

/** @brief Usuwa przekierowania.
 * Działa jak @ref phfwdRemove.
 * Usuwa wszystkie przekierowania, w których parametr @p number jest prefiksem
 * parametru @p number1 użytego przy dodawaniu. Jeśli nie ma takich przekierowań
 * lub napis nie reprezentuje numeru, nic nie robi.
 *
 * @param[in] phoneForward – wskaźnik na strukturę przechowującą przekierowania
 *                           numerów;
 * @param[out] phoneForward – wskaźnik na tą samą stukturę po wykonaniu na niej
 *                            opisanej w @ref phoneForwardRemove operacji
 * @param[in, out] number – wskaźnik na napis reprezentujący prefiks numerów.
 */
void phoneForwardRemove(struct PhoneForward *phoneForward, char const *number);

#endif //TEL_PHONE_FORWARD_REMOVE_H
