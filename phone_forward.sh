#!/bin/bash

# Wyłapywanie błędnych danych
################################################################################
# Sprawdzenie liczby argumentów
if [ "$#" -ne "3" ]; then
	echo "Proszę podać dokładnie trzy argumenty!"
	exit 1
fi

# Sprawdzenie istnienia programu
if [ ! -f $1 ]; then
	echo "Proszę podać poprawną nazwę istniejącego pliku wykonywalnego!"
	exit 1
fi

# Sprawdzenie istnienia pliku z danymi wejściowcymi
if [ ! -f $2 ]; then
	echo "Proszę podać poprawną nazwę pliku z danymi wejściowcymi!"
	exit 1
fi

# Sprawdzam, czy plik z danymi wejściowymi zawiera tylko dozwolone symbole
REGEX_OF_INPUT='^[>\d\s:;]*$'
if grep --perl-regexp -v ${REGEX_OF_INPUT} $2 > /dev/null; then
	echo "Proszę podać plik z danymi zgodyn ze sprcyfikacją!"
	exit 1
fi

# Zakończenie sprawdzania poprawności wejścia
################################################################################



# Przygotowanie programu
################################################################################
# Sensowne nazwy zmiennych
prog=$1
input=$2
y=$3

# Tworzę pliki tymczasowe
inputfile=`mktemp`
outfile=`mktemp`
touch ${inputfile}
touch ${outfile}
################################################################################



# Tworzę plik wejściowy
################################################################################
echo "NEW a" > ${inputfile}
cat ${input} >> ${inputfile}
echo "?" >> ${inputfile}
echo ${y} >> ${inputfile}
################################################################################



# Pierwsze wykonanie programu
################################################################################
# Wykonuję program z danymi wejściowymi
${prog} < ${inputfile} 1> ${outfile} 2> /dev/null

# Sprawdzam, czy wykonanie się powiodło
if [ "$?" -eq "1" ]; then
	echo "Błędny format danych wejściowcych, lub błąd z pamięcią!"
	rm ${inputfile} ${outfile}
	exit 1
fi
################################################################################



# Tworzę nowy plik wejściowy
################################################################################
echo "NEW a" > ${inputfile}
cat ${input} >> ${inputfile}

# Dopisuję nowy wiersz
echo "" >> ${inputfile}

# Dopisuję zapytania o elementy wyjścia z poprzedniego wykonania
while read number; do
	echo ${number} >> ${inputfile}
	echo "?" >> ${inputfile}
done < ${outfile}
################################################################################



# Drugie wykonanie programu
################################################################################
# Tworzę nowy plik wyjściowy
outfile2=`mktemp`
touch ${outfile2}

${prog} < ${inputfile} 1> ${outfile2} 2> /dev/null

if [ "$?" -eq "1" ]; then
	echo "Błędny format danych wejściowcych, lub błąd z pamięcią!"
	rm ${inputfile} ${outfile} ${outfile2}
	exit 1
fi
################################################################################



# Przejście po każdej linii i wypisanie spełniających warunki zadania numerów
################################################################################
size_of_output=`wc -l < ${outfile}`
for (( i = 1 ; i <= size_of_output ; i++ )); do
	real_get=`sed -n "${i}p" ${outfile2}`
	if [[ $y == ${real_get} ]]; then
		sed -n "${i}p" ${outfile}
	fi
done
################################################################################



# Zakończenie skryptu
################################################################################
rm ${inputfile}
rm ${outfile}
rm ${outfile2}
################################################################################
