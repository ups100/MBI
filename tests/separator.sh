#!/bin/bash

file=$1
number=$2
output=$3
tmp=""
i=0
counter=0
# while loop
while IFS= read -r -n1 char
do
    if [[ $char =~ ^[A-Za-z_]+$ ]]; then
      	i=$i+1
        tmp="$tmp$char"
	#echo -n "$char" >> $output
 	if (( $i == $number )); then
		echo -n $tmp >> $output
		counter=$((counter+1))
		echo -n ";" >> $output 
		i=0
		tmp=""
	fi
    fi
done 
echo $counter
