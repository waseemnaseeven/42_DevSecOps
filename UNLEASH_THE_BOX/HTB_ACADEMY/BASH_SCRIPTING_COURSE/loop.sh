#!/bin/bash

for var in 1 2 3 4
do
    echo $var
    if [ $var -eq 3 ]
    then
        echo "c'est 3"
    fi
done

for ip in "10.10.10.170 10.10.10.174 10.10.10.175"
do
	ping -c 1 $ip
done
