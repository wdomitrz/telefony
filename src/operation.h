/** @file
 * Deklaracja klasy operacji i interfejs wykonywanych na niej metod z
 * implementacją w @ref operation.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */

#ifndef TELEFONY_INPUT_OPERATION_H
#define TELEFONY_INPUT_OPERATION_H

#include "phone_forward.h"
#include "dictionary.h"

/**
 * Kod błędu alokacji pamięci.
 */
#define MEMORY_ERROR 0

/**
 * Kod błędnej nazwy operacji.
 */
#define PARSING_ERROR 1

/**
 * Kod operacji typu przedwczesnego znaku EOF.
 */
#define EOF_ERROR 2

/**
 * Kod operacji zmiany aktualnej bazy i jej utworzenia, jeśli taka nie istnieje.
 */
#define NEW_BASE 3

/**
 * Kod operacji usunięcia aktualnej bazy.
 */
#define DEL_BASE 4

/**
 * Kod operacji dodania przekierowania.
 */
#define ADD 5

/**
 * Kod operacji wypisania przekierowania z podanego numeru.
 */
#define GET 6

/**
 * Kod operacji wypisania przekierowań na podany numer.
 */
#define REV 7

/**
 * Kod operacji usunięcia przekierowań, których podany numer jest prefiksem.
 */
#define DEL 8

/**
 * Kod błędu działania operacji
 */
#define OPERATION_ERROR 9

/**
 * Kod poprawnego wykonania operacji
 */
#define OPERATION_SUCCESS 10

/**
 * Kod nieznenej operacji DEL - @ref DEL, lub @ref DEL_BASE
 */
#define DEL_UNKNOWN 11

/**
 * Kod operacji zliczania nietrywialnych odwrotności
 */
#define NTRIV 12

/**
 * Struktura przechowująca wszystkie informacje o danej operacji.
 */
struct Operation {

    /**@{*/

    int typeOfOperation;
    /**<
     * Typ operacji.
     * Możliwe typy:
     *  - @ref MEMORY_ERROR;
     *  - @ref PARSING_ERROR;
     *  - @ref EOF_ERROR;
     *  - @ref NEW_BASE;
     *  - @ref DEL_BASE;
     *  - @ref ADD;
     *  - @ref GET;
     *  - @ref REV;
     *  - @ref DEL.
     */

    int firstSignNumber;
    /**<
     * Liczba będąca liczbą @c n oczekiwaną przy informacji o błędzie.
     */

    char *firstParameter;
    /**<
     * Pierwszy parametr operacji
     */

    char *secondParameter;
    /**<
     * Drugi parametr operacji. Jeśli operacja jest jednoargumentowa, to ma
     * wartość @c NULL.
     */

    char operationName[4];
    /**<
     * Nazwa operatora – jedna z czterach możliwych: @c NEW, @c DEL, @c ?, @c >.
     */

    /**@}*/
};

/**
 * @brief Tworzy nową strukturę.
 * Tworzy nową operacji niezawierającą żadnych informacji.
 * @return Wskaźnik na utworzoną strukturę lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct Operation *operationCreate(void);

/**
 * @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p operation. Nic nie robi, jeśli wskaźnik
 * ten ma wartość @c NULL.
 * @param[in] operation – wskaźnik na usuwaną strukturę;
 * @param[out] operation – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void operationDestroy(struct Operation *operation);

/**
 * @brief Czyści operation z danych.
 * Usuwa użyte już z @p operation ustawiając parametry na domyślne (takie jak
 * po @ref operationCreate).
 * @param[in] operation – wskaźnik na strukturę z informacjami o operacji,
 *                        których należy się pozbyć;
 * @param[out] operation – wskaźnik na strukturę z domyślnymi informacjami o
 *                         operacji.
 */
void operationClean(struct Operation *operation);

/**
 * @brief Wykonuje operacje, lub zwraca informację o błędzie.
 * Sprawdza poprawność argumentów operacji podanej w @p operation i możliwości
 * wykonania tej operacji. W przypadku jeśli jest to możliwe wykonuje ją i
 * zwraca @c true. W przeciwnym przypadku nic nie robi i zwraca @c false.
 * @param operation – wskaźnik na strukturę z informacjami o operacji;
 * @param phoneForward – wskaźnik na wskaźnik na bazę danych, która jest
 *                       aktualnie aktywna w programie;
 * @param dictionary – wskaźnik na słownik przechowujący bazy przekierowań.
 * @return Wartość @ref OPERATION_SUCCESS, jeśli wykonanie powiodło się, wartość
 *         @ref OPERATION_ERROR jeśli się nie powiodło z powodu błędu operacji,
 *         wartość @c MEMORY_ERROR jeśli wystąpił błąd alokacji pamięci, lub
 *         wartość @c PARSING_ERROR jeśli została przekazana błędna nazwa
 *         operacji.
 */
int operationExecute(struct Operation *operation,
                     struct PhoneForward **phoneForward,
                     struct Dictionary *dictionary);

#endif //TELEFONY_INPUT_OPERATION_H
