#!/bin/bash

value=$1

# L'option "-gt" signifie "greater than" (supérieur à en anglais), et elle est utilisée pour comparer si la valeur de la variable "value" est strictement supérieure à 10.

# L'option "-eq" est utilisée pour la comparaison d'égalité (égal à en anglais).

# L'option "-lt" est utilisée pour la comparaison de moins que (inférieur à en anglais).

# L'option "-ge" est utilisée pour la comparaison supérieur ou égal à (greater than or equal to en anglais).

# L'option "-le" est utilisée pour la comparaison inférieur ou égal à (less than or equal to en anglais).

if [ $value -gt "10" ]
then 
    echo "The test value $value is greater than 10."
elif [ $value -lt "10" ]
then
    echo -e "The test value $value is less than 10."
elif [ $value -eq "10" ]
then
    echo -e "The test value $value is equal to 10."
else
    echo -e "The test value is not a number." 
fi
