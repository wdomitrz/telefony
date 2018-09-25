/** @file
 * Interfejs podstawowych operacji i deklaracja struktury @c PhoneForward z
 * implementacją w pliku @ref phone_forward_struct.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_FORWARD_BASIC_H
#define TEL_PHONE_FORWARD_BASIC_H

/**
 * Pierwsza (alfabetycznie) dozwolona listera w słowie
 */
#define FIRST_LETTER '0'

/**
 * Ostatnia (alfabetycznie) dozwolona listera w słowie
 */
#define LAST_LETTER ';'

/**
 * Liczba różnych dozwolonych liter w słowie
 */
#define SIZE_OF_ALPHABET (LAST_LETTER - FIRST_LETTER + 1)

struct PhoneForwardList;

/**
 * @brief Struktura przechowująca przekierowania numerów telefonów.
 * Przekierowania numerów telefonów reprezentuję jako drzewo TRIE numerów
 * telefonów, w którym trzymam potrzebne informacje o numerach
 */
struct PhoneForward {
    /**@{*/

    int depth;
    /**<
     * Głębokość w drzewie (równa długości słowa). W korzeniu jest to 0.
     */

    char nodeChar;
    /**<
     * Ostatni znak numeru telefonu kończącego się w tym miejscu.
     * W korzniu jest to @c '\0'.
     */

    struct PhoneForward *prev;
    /**<
     * Wskaźnik na ojca w drzewie.
     * W korzeniu jest to @c NULL.
     */

    struct PhoneForward *nextLetter[SIZE_OF_ALPHABET];
    /**<
     * Wskaźniki na synów w drzewie - po jednym na każdy możliwy znak.
     */

    struct PhoneForward *forwardTo;
    /**<
     * Wskaźnik na wierzchołek do którego idzie bezpośrednie przekierowanie z
     * danego wierzchołka.
     * Wartość @c NULL, jeśli z danego wierzchołka nie ma bezpośredniego
     * przekierowania.
     */

    struct PhoneForwardList *revert;
    /**<
     * Wskaźnik na listę przechowywującą możliwe przekierowania z tego
     * wierzchołka.
     */

    /**@}*/
};

/** @brief Tworzy nową strukturę.
 * Działa jak @ref phfwdNew.
 * Tworzy nową strukturę niezawierającą żadnych przekierowań.
 * @return Wskaźnik na utworzoną strukturę lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct PhoneForward *phoneForwardCreate(void);

/** @brief Usuwa strukturę.
 * Działa jak @ref phfwdDelete.
 * Usuwa strukturę wskazywaną przez @p phoneForward. Nic nie robi, jeśli
 * wskaźnik ten ma wartość NULL.
 * @param[in] phoneForward – wskaźnik na usuwaną strukturę.
 * @param[out] phoneForward – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void phoneForwardDestroy(struct PhoneForward *phoneForward);

/**
 * @brief Zamienia słowo na wierchołek
 * Zamienia słowo @p number będące numerem telefonu na wierchołke będący jego
 * reprezentacją w drzewie @p phoneForward.
 * @param phoneForward – wskaźnik na drzewo w którym szukamy reprezentacji
 *                       danego słowa;
 * @param number – wskaźnik na słowo.
 * @return Wartość @c NULL jeśli dane słowo nie reprezentuje numeru, lub
 *         wskaźnik na wierzchołek w drzewie reprezentujący dany numer.
 */
struct PhoneForward *phoneForwardFromString(struct PhoneForward *phoneForward,
                                            char const *number);

/**
 * @brief Zamienia wierchołki na słowo
 * Tworzy słowo będące połączeniem dwóch słów - pierwsza jego część to
 * napis reprezentujący numer od wierchołka begin1 (wyłącznie) do wierchołka
 * end1 (włącznie), a druga to napis reprezentujący numer of wierchołka begin2
 * (wyłącznie) do wierchołka end2 (włącznie).
 * @param begin1 – wskaźnik na pierwszy wierchołek w drzewie;
 * @param end1 – wskaźnik na drugi wierzhołek w drzewie, będący synem @p begin1;
 * @param begin2 – wskaźnik na trzeci wierzchołek w drzewie;
 * @param end2 – wskaźnik na czwarty wierchołek w drzewie będący synem @p begin2.
 * @return Szukane słowo, lub @c NULL, gdy nie udało się zaalokować pamięci.
 */
char *phoneForwardToString(struct PhoneForward *begin1,
                           struct PhoneForward *end1,
                           struct PhoneForward *begin2,
                           struct PhoneForward *end2);

#endif //TEL_PHONE_FORWARD_BASIC_H
