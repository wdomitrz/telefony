/** @file
 * Implementacja funkcji obliczania liczby nietrywialnych numerów z interfejsem
 * w pliku @ref phone_forward_non_trivial_count.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 08.06.2018
 */

#include <stdlib.h>
#include <stdbool.h>
#include "phone_forward_struct.h"
#include "phone_forward_list.h"
#include "phone_forward_non_trivial_count.h"

/**
 * @brief Potęguje.
 * Oblicza @p b tą potęgę @p modulo @c 2 do potęgi liczba bitów reprezentacji
 * typu @c size_t.
 * @param a – liczba do podniesienia do potęgi,
 * @param b – liczba będąca potęgą.
 * @return Wartość a do potęgi b modulo @c 2 do potęgi liczba bitów
 *         reprezentacji typu @c size_t.
 */
size_t nthPowerOf(size_t a, size_t b) {
    size_t helper;
    if (b == 0)
        return 1;
    helper = nthPowerOf(a, b / 2);
    if (b % 2 == 0)
        return helper * helper;
    return helper * helper * a;
}

/**
 * @brief Funkcja oblicza liczbę nietrywialnych numerów.
 * Pomocnicza do @ref phoneForwardNonTrivialCount.
 * Funkcja oblicza liczbę nietrywialnych numerów długości len zawierających
 * tylko cyfry, które są oznaczone jako istniejące w @p doesCharacterExist.
 * Obliczenia wykonuje modulo @c 2 do potęgi liczba bitów reprezentacji typu
 * @c size_t.
 * @param[in] phoneForward  – wskaźnik na strukturę przechowującą przekierowania
 *                            numerów, który nie może mieć wartości @c NULL;
 * @param[out] phoneForward – wskaźnik na tą samą strukturę;
 * @param doesCharacterExist – wskaźnik na tablicę @c bool-i, która musi być
 *                             rozmiaru @ref SIZE_OF_ALPHABET, zawierającą
 *                             informację o istnieniu pocsczególnych cyfr;
 * @param count – liczba dozwolonch w tablicy @p doesCharacterExist;
 * @param length – długość zliczanych numerów telefonów na początku musząca być
 *                 różną od @c 0;
 * @param result – wskaźnik na zmienną do której ma zostać zapisany wynik do
 *                 zwrócenia, który na początku ma mieć wartość @c 0 i jest
 *                 akumulatorem.
 * @return Szukana liczba modulo @c 2 do potęgi liczba bitów reprezentacji typu
 *         @c size_t.
 */
size_t phoneForwardNonTrivialCountProcessedParams(
        struct PhoneForward *phoneForward, bool *doesCharacterExist,
        size_t count, size_t length, size_t *result) {
    size_t i;

    // Sprawdzanie, czy numery poniżej są nietrywialne
    if (!phoneForwardListIsEmpty(phoneForward->revert)) {
        *result += nthPowerOf(count, length);
        return *result;
    }

    // Jeśli skończyła się dozwolona liczba numerów
    if (length == 0) {
        return *result;
    }

    // Wejście do kolejnych synów
    for (i = 0; i < SIZE_OF_ALPHABET; i++) {
        if (doesCharacterExist[i] && phoneForward->nextLetter[i] != NULL) {
            phoneForwardNonTrivialCountProcessedParams(
                    phoneForward->nextLetter[i], doesCharacterExist, count,
                    length - 1, result);
        }
    }
    return *result;
}

size_t phoneForwardNonTrivialCount(struct PhoneForward *phoneForward,
                                   char const *set, size_t length) {
    size_t i;
    size_t count;
    size_t result;
    bool doesCharacterExist[SIZE_OF_ALPHABET];

    /*
     * Jeśli wskaźnik PhoneForward ma wartość NULL, set ma wartość NULL, set
     * jest pusty, lub parametr length jest równy zeru, wynikiem jest zero.
     */
    if (phoneForward == NULL || set == NULL || set[0] == '\0' || length == 0)
        return 0;

    // Przygotowanie wartości
    count = 0;
    for (i = 0; i < SIZE_OF_ALPHABET; i++) {
        doesCharacterExist[i] = false;
    }

    // Zapisanie które cyfry numeru są w set i ich zliczenie
    for (i = 0; set[i] != '\0'; i++) {

        if (FIRST_LETTER <= set[i] && set[i] <= LAST_LETTER &&
            !doesCharacterExist[set[i] - FIRST_LETTER]) {
            // Dodanie informacji o wcześniej nienapotkanej cyfry
            doesCharacterExist[set[i] - FIRST_LETTER] = true;
            count++;
        }
    }

    // Jeśli set nie zawiera żadnej cyfry wynikiem jest zero
    if (count == 0)
        return 0;

    // Przygotowanie wyniku
    result = 0;

    // Zwrócenie szukanej wartości
    return phoneForwardNonTrivialCountProcessedParams(
            phoneForward, doesCharacterExist, count, length, &result);
}
