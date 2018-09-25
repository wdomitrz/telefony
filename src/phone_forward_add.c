/** @file
 * Implementacja operacji dodawania przekierowania z interfejsem w pliku
 * @ref phone_forward_add.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdbool.h>
#include <stdlib.h>
#include "phone_forward_add.h"
#include "phone_forward_struct.h"
#include "phone_forward_list.h"

bool phoneForwardAdd(struct PhoneForward *phoneForward, char const *number1,
                     char const *number2) {
    struct PhoneForward *number1Node, *number2Node;

    // Sprawdzenie poprawności wejścia
    if (phoneForward == NULL)
        return false;

    // Znalezienie wierzchołków odpowiadających danym słowom
    number1Node = phoneForwardFromString(phoneForward, number1);
    number2Node = phoneForwardFromString(phoneForward, number2);

    // Sprawdzenie poprawności numerów
    if (number1Node == NULL || number2Node == NULL || number1Node == number2Node
        || number1Node == phoneForward || number2Node == phoneForward)
        return false;

    // Usunięcie starego przekierowania jeśli istniało
    if (number1Node->forwardTo != NULL)
        phoneForwardListRemove(number1Node->forwardTo->revert, number1Node);

    // Dodanie informacji o odwrotności przekierowania
    if (!phoneForwardListAdd(number2Node->revert, number1Node))
        return false;

    // Dodanie informacji o przekierowaniu
    number1Node->forwardTo = number2Node;

    return true;
}