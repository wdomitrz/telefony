/** @file
 * Implemetacja metod wykonywanych na klasie operacji z interfejsem w
 * @ref operation.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operation.h"
#include "phone_forward.h"
#include "dictionary.h"

struct Operation *operationCreate() {
    struct Operation *newOperation;

    // Zaalokowanie miejsca na strukturę
    newOperation = malloc(sizeof(struct Operation));
    if (newOperation == NULL)
        return NULL;

    // Ustawienie wartości parametrów
    newOperation->typeOfOperation = MEMORY_ERROR;
    newOperation->firstSignNumber = 0;
    newOperation->firstParameter = NULL;
    newOperation->secondParameter = NULL;
    strcpy(newOperation->operationName, "");

    // Zwrócenie nowej struktury
    return newOperation;
}

void operationClean(struct Operation *operation) {

    // Zwolnienie parametrów
    free(operation->firstParameter);
    free(operation->secondParameter);

    // Ustawienie domyślnych wartości parametrów
    operation->typeOfOperation = MEMORY_ERROR;
    operation->firstSignNumber = 0;
    operation->firstParameter = NULL;
    operation->secondParameter = NULL;
    strcpy(operation->operationName, "");
}

void operationDestroy(struct Operation *operation) {

    // Sprawdzenie poprawności wejścia
    if (operation == NULL)
        return;

    // Zwolnienie parametrów
    free(operation->firstParameter);
    free(operation->secondParameter);
    strcpy(operation->operationName, "");

    // Zwolnienie struktury
    free(operation);
}

int operationExecute(struct Operation *operation,
                     struct PhoneForward **phoneForward,
                     struct Dictionary *dictionary) {
    struct PhoneForward *helper;
    struct PhoneNumbers const *output;
    size_t i, len;
    char const *number;

    /*
     * Poprawność danych - numerów i identyfikatorów jest już sprawdzona w
     * czasie parsowania wejścia.
     */

    // Znalezienie operacji do wykonania
    switch (operation->typeOfOperation) {

        case NEW_BASE:

            /*
             * Zmiana aktywnej bazy numerów telefonicznych
             */
            helper = dictionaryGet(dictionary, operation->firstParameter);
            if (helper == NULL)
                return MEMORY_ERROR;

            *phoneForward = helper;
            break;
        case DEL_BASE:

            /*
             * Usunięcie przekierowania
             */
            if (!dictionaryRemove(dictionary, operation->firstParameter,
                                  phoneForward))
                return OPERATION_ERROR;

            break;
        case ADD:

            /*
             * Sprawdzenie istnienia aktualnej bazy
             */
            if (*phoneForward == NULL) {
                return OPERATION_ERROR;
            }

            /*
             * Dodanie przekierowania
             */
            if (!phfwdAdd(*phoneForward, operation->firstParameter,
                          operation->secondParameter))
                return OPERATION_ERROR;

            break;
        case GET:

            /*
             * Sprawdzenie istnienia aktualnej bazy
             */
            if (*phoneForward == NULL) {
                return OPERATION_ERROR;
            }

            /*
             * Znalezienie przekierowania
             */
            output = phfwdGet(*phoneForward, operation->firstParameter);

            // Sprawdzenie, czy wynik jest zaalokowany
            if (output == NULL)
                return MEMORY_ERROR;

            // Sprawdzenie, czy wynik jest niepusty
            if (phnumGet(output, 0) == NULL)
                return OPERATION_ERROR;

            // Wypisanie szukanych numerów
            i = 0;
            while ((number = phnumGet(output, i)) != NULL) {
                printf("%s\n", number);
                i++;
            }
            phnumDelete(output);

            break;
        case REV:

            /*
             * Sprawdzenie istnienia aktualnej bazy
             */
            if (*phoneForward == NULL) {
                return OPERATION_ERROR;
            }

            /*
             * Znajduje odwrotności przekierowania
             */
            output = phfwdReverse(*phoneForward, operation->firstParameter);

            // Sprawdzenie, czy wynik jest zaalokowany
            if (output == NULL)
                return MEMORY_ERROR;

            // Sprawdzenie, czy wynik jest niepusty
            if (phnumGet(output, 0) == NULL)
                return OPERATION_ERROR;

            // Wypisanie szukanych numerów
            i = 0;
            while ((number = phnumGet(output, i)) != NULL) {
                printf("%s\n", number);
                i++;
            }
            phnumDelete(output);

            break;
        case DEL:

            /*
             * Sprawdzenie istnienia aktualnej bazy
             */
            if (*phoneForward == NULL) {
                return OPERATION_ERROR;
            }

            // Usunięcie przekierowań
            phfwdRemove(*phoneForward, operation->firstParameter);

            break;
        case NTRIV:

            /*
             * Sprawdzenie istnienia aktualnej bazy
             */
            if (*phoneForward == NULL) {
                return OPERATION_ERROR;
            }

            // Ustawienie parametru len
            len = strlen(operation->firstParameter);
            if (len > 12)
                len -= 12;
            else
                len = 0;

            // Wykonanie operacji i wypisanie wyniku
            printf("%zu\n", phfwdNonTrivialCount(
                    *phoneForward, operation->firstParameter, len));

            break;
        default:

            /*
             * Wejście tu możliwe jest tylko w przypadku jakiegoś błędu
             * parsowania na przykład MEMORY_ERROR w czasie parsowania,
             * EOF_ERROR, lub PARSING_ERROR
             */
            return operation->typeOfOperation;
    }

    return OPERATION_SUCCESS;
}