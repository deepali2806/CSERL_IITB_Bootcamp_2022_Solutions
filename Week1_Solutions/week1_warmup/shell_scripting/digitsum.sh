#!/bin/bash

inputNumber=$1
sum=0
for ((i = 0; i<${#inputNumber}; i++))
	do
		char=${inputNumber:$i:1};
		sum=$(($sum + $char))
	done;    
echo "Sum of digits from a given number is $sum"
	  
#Can also use read -n 1 char < inputString to read a character from a string
