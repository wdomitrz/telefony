/** @file
 * Interfejs funkcji wczytującej jedną operację z implementacją w
 * @ref input_reader.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */


#ifndef TELEFONY_INPUT_PARSER_H
#define TELEFONY_INPUT_PARSER_H

#include <stdbool.h>
#include "operation.h"

/**
 * @brief Wczytuje wejście
 * Wczytuje kolejną operację z wejścia, jeśli taka istnieje. informację
 * Jeśli operacja jest niepoprawna, to zapisuje informację o błędnej operacji
 * @param[in] operation – operacja z polami z wartościami domyślnymi - takimi
 *                        jak po funkcji @ref operationClean;
 * @param[out] operation – operacja z ustawionymi na konkretne wartości
 *                         odpowiadające właśnie wczytanym danym;
 * @param[in] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych przed
 *                                   rozpoczęciem aktualnej operacji wczytywania;
 * @param[out] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych po
 *                                    zanończeniu aktualnej operacji wczytywania.
 * @return Wartość @c true jeśli została wczytana jakaś informacja o operacji,
 *         lub wartość @c false jeśli został osiągnięty koniec pliku przed
 *         wczytaniem jakiejkolwiek informacji o operacji (poprawnej, bądź nie).
 */
bool inputReaderReadNextOperation(struct Operation *operation,
                                  int *inputCharacterNumber);

#endif //TELEFONY_INPUT_PARSER_H
