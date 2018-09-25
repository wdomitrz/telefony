/** @file
 * Implementacja operacji znajdowania odwrotności przekierowania z interfejsem w
 * pliku @ref phone_forward_reverse.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include <stdbool.h>
#include "phone_forward_reverse.h"
#include "string_list.h"
#include "phone_numbers.h"
#include "phone_forward_struct.h"
#include "phone_forward_list.h"

/**
 * @brief Funkcja pomicnicza @ref phoneForwardReverse
 * Zapisuje numery szukane w @ref phoneForwardReverse reprezentowane przez słowa
 * do danej listy słów.
 * @param phoneForward – wskaźnik na strukturę przechowującą przekierowania
 *                       numerów;
 * @param[in] mainList – wskaźnik listę do której zostaną dopisane słowa
 *                       reprezentujące szukane numery telefonów;
 * @param[out] mainList – wskaźnik listę do której zostały dopisane słowa
 *                        reprezentujące szukane numery telefonów;
 * @param begin – wskaźnik na wierzchołek drzewa reprezentujący napis pusty;
 * @param end – wkaźnik na wierzchołek drzewa z reprezentujący numer, z którego
 *              szukane są numery telefonów.
 * @return Wartość @c true, jeśli operacja się powiodła
 *         Wartość @c false, jeśli operacja się nie powiodła (np. nie udało się
 *         zaalokować pamięci).
 */
bool phoneForwardReverseToList(struct PhoneForward *phoneForward,
                               struct StringList *mainList,
                               struct PhoneForward *begin,
                               struct PhoneForward *end) {
    struct PhoneForwardList *currentElem;
    char const *currentNumber;

    // Jeśli doszliśmy do pustego słowa, to dodajemy oryginalny numer do listy.
    if (phoneForward->nodeChar == '\0') {
        // Utworzenie słowa reprezentującego orginalny numer
        currentNumber = phoneForwardToString(begin, begin, begin, end);
        if (currentNumber == NULL)
            return false;

        // Dodanie tego słowa do listy
        if (!stringListAdd(mainList, currentNumber)) {
            free((void *) currentNumber);
            return false;
        }
        return true;
    }

    /* Przeiterowanie się po możliwych odwrotnościach przekierowań z danego
     * numeru.
     */
    currentElem = phoneForward->revert->next;
    while (currentElem != NULL) {
        /* Utworzenie słowa reprezentującego numer z którego przekierowywujemy,
         * jeśli przekierowaniem jest za numeru reprezentowanego przez aktualny
         * wierzchołek, na numer reprezentowany przez aktualny element listy.
         */
        currentNumber = phoneForwardToString(begin, currentElem->val,
                                             phoneForward, end);
        if (currentNumber == NULL)
            return false;

        // Dodanie tego słowa do listy
        if (!stringListAdd(mainList, currentNumber)) {
            free((void *) currentNumber);
            return false;
        }
        currentElem = currentElem->next;
    }

    // Wywołanie tej samej procedury dla przekierowań w poprzednim wierzchołku
    return phoneForwardReverseToList(phoneForward->prev, mainList, begin, end);
}

struct PhoneNumbers const *phoneForwardReverse(struct PhoneForward *phoneForward,
                                               char const *number) {
    struct StringList *stringList;
    struct PhoneForward *numberNode;
    char const *const *outList;
    size_t size, i;

    // Sprawdzenie poprawności wejścia
    if (phoneForward == NULL)
        return NULL;
    i = 0;

    // Sprawdzenie czy dany numer może reprezentować numer
    if (number == NULL)
        return phoneNumbersCreateEmpty();
    while (number[i] != '\0') {
        if (number[i] < FIRST_LETTER || number[i] > LAST_LETTER)
            return phoneNumbersCreateEmpty();
        i++;
    }

    // Znalezienie wierzchołka reprezentującego dany numer
    numberNode = phoneForwardFromString(phoneForward, number);
    if (numberNode == NULL)
        return NULL;

    // Sprawdzenie, czy dany numer nie jest pusty
    if (numberNode == phoneForward)
        return phoneNumbersCreateEmpty();

    // Utworzenie listy na wynikowe słowa
    stringList = stringListCreate();
    if (stringList == NULL)
        return NULL;

    //
    if (!phoneForwardReverseToList(numberNode, stringList, phoneForward,
                                   numberNode)) {
        stringListDestroy(stringList);
        return NULL;
    }

    // Zapisanie liczby wynikowych słów
    size = stringListSize(stringList);

    // Zamienienie listy słów na tablicę
    outList = stringListToStringsAndDestroy(stringList);
    if (outList == NULL) {
        stringListDestroy(stringList);
        return NULL;
    }

    // Utworzenie struktury PhoneNumbers i jej zwrócenie
    return phoneNumbersCreate(outList, size);
}