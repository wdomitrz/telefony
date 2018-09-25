/** @file
 * Główny plik programu będącego rozwiązaniem drugiej części zadania telegony.
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "phone_forward.h"
#include "dictionary.h"
#include "input_reader.h"
#include "operation.h"

/**
 * Główna funkcja programu
 * @return Wartość @c 0 jeśli program zakończył się bez błędów i @c 1 jeśli
 *         zakończył się z błędem.
 */
int main() {
    struct Dictionary *dictionary;
    struct PhoneForward *phoneForward;
    struct Operation *nextOperation;
    int inputCharacterNumber;
    int programmeOutput;
    int operationOptput;

    // Ustawienie ostatniego wczytanego znaku na znak zerowy
    inputCharacterNumber = 0;

    // Ustawienie wyjścia programu na 0 - nie został jeszcze wykryty błąd
    programmeOutput = 0;

    // Ustawienie informacji o braku ustawionej bazy przekierowań
    phoneForward = NULL;

    // Przygotowanie operacji
    nextOperation = operationCreate();
    if (nextOperation == NULL) {
        // błąd alokacji pamięci
        fprintf(stderr, "ERROR memory error");
        return 1;
    }

    // Stworzenie nowego, pustego słownika
    dictionary = dictionaryCreate();
    if (dictionary == NULL) {
        // błąd alokacji pamięci
        fprintf(stderr, "ERROR memory error");
        operationDestroy(nextOperation);
        return 1;
    }

    while (inputReaderReadNextOperation(nextOperation, &inputCharacterNumber)) {

        /*
         * Próba wykonania operacji.
         * W przypadku niepowodzenia zwrócenie informacji o błędzie i
         * zakończenie programu
         */
        if ((operationOptput =
                     operationExecute(nextOperation, &phoneForward, dictionary))
            != OPERATION_SUCCESS) {

            switch (operationOptput) {

                // Napodkany przedwcześnie EOF
                case EOF_ERROR:
                    fprintf(stderr, "ERROR EOF\n");
                    break;

                // Błąd wykonania operacji
                case OPERATION_ERROR:
                    fprintf(stderr, "ERROR %s %d\n", nextOperation->operationName,
                            nextOperation->firstSignNumber);
                    break;

                // Błąd parsowania operacji wejścia
                case PARSING_ERROR:
                    fprintf(stderr, "ERROR %d\n", nextOperation->firstSignNumber);
                    break;

                // Błąd pamięci
                case MEMORY_ERROR:
                    fprintf(stderr, "ERROR memory error\n");
                    break;

                // Nieznany błąd
                default:
                    // Informacja o nieznanym błędzie
                    fprintf(stderr, "ERROR unknown error\n");
                    break;
            }

            // Jeśli wystąpił jakikolwiek błąd, to kończymy wykonanie programu
            programmeOutput = 1;
            break;
        }

        // Wyczyszczenie nextOperation z użytych już danych
        operationClean(nextOperation);
    }

    /*
     * Zwolnienie zaalokowanej pamięci i zakończenie wykonania programu
     */
    operationDestroy(nextOperation);
    dictionaryDestroy(dictionary);
    return programmeOutput;
}