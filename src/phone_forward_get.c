/** @file
 * Implementacja operacji znajdowania przekierowania z interfejsem w pliku
 * @ref phone_forward_get.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include <stdbool.h>
#include "phone_forward_get.h"
#include "phone_numbers.h"
#include "phone_forward_struct.h"

struct PhoneNumbers const *phoneForwardGet(struct PhoneForward *phoneForward,
                                           char const *number) {
    struct PhoneForward *numberNode, *numberNodeCopy;
    char **resultStrings;
    size_t size;
    // Flaga mówiąca nam, czy już wykonaliśmy skok będący przekierowaniem
    bool jumped;
    size_t i;

    // Sprawdzenie poprawności wejścia
    if (phoneForward == NULL)
        return phoneNumbersCreateEmpty();
    i = 0;
    if (number == NULL)
        return phoneNumbersCreateEmpty();
    while (number[i] != '\0') {
        if (number[i] < FIRST_LETTER || number[i] > LAST_LETTER)
            return phoneNumbersCreateEmpty();
        i++;
    }

    // Wyznaczenie wierzchołka w drzewie
    numberNode = phoneForwardFromString(phoneForward, number);
    // Jeśli podany numer jest pustym prefiksem, to nie jest poprawnym numerem
    if (numberNode == phoneForward)
        return phoneNumbersCreateEmpty();
    // Błąd alokacji pamięci w @ref phoneForwardFromString
    if (numberNode == NULL)
        return NULL;
    numberNodeCopy = numberNode;

    // Znalezienie długości wyjściowego numeru
    size = 0;
    while (numberNode->nodeChar != '\0') {
        if (numberNode->forwardTo != NULL) {
            size += numberNode->forwardTo->depth;
            break;
        } else {
            size++;
            numberNode = numberNode->prev;
        }
    }

    // Zaalokowanie struktury będącej wynikową tablicą stringów
    resultStrings = malloc(sizeof(char *));
    if (resultStrings == NULL)
        return NULL;
    resultStrings[0] = malloc((size + 1) * sizeof(char *));
    if (resultStrings[0] == NULL) {
        free(resultStrings);
        return NULL;
    }

    // Ustawienie ostatniego znaku na koniec stringa i flagi skoku
    resultStrings[0][size] = '\0';
    jumped = false;

    // Ponowne ustawienie wierzchołka odpowiadającemu danemu słowu
    numberNode = numberNodeCopy;

    // Zapisanie słowa do wynikowej tablicy
    while (numberNode->nodeChar != '\0') {
        if (!jumped && numberNode->forwardTo != NULL) {
            jumped = true;
            numberNode = numberNode->forwardTo;
        } else {
            resultStrings[0][--size] = numberNode->nodeChar;
            numberNode = numberNode->prev;
        }
    }

    // Utworzenie struktury PhoneNumbers i jej zwrócenie
    return phoneNumbersCreate((const char *const *) resultStrings, 1);
}
