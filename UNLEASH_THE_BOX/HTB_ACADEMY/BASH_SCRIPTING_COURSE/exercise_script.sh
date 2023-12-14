#!/bin/bash
# Count number of characters in a variable:
#     echo $variable | wc -c

# Variable to encode
var="nef892na9s1p9asn2aJs71nIsm"

for counter in {1..40}
do
    var=$(echo $var | base64)
    # count number of characters until the 35th encoded value
    if [ $counter -eq 35 ]
    then
        char_count=$(echo $var | wc -c)
        echo "The number of characters in the 35th encoded value of var is: $char_count"
        exit
    fi
done