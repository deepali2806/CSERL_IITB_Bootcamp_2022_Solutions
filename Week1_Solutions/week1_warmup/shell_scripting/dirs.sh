#!/bin/bash


mkdir root;

for i in 1 2 3 4 5
do
	 directory_name=root/dir${i}
	 mkdir $directory_name
	 
	for j in 1 2 3 4
	 do
	 	filename=${directory_name}/file${j}
	 	touch $filename
	 	
	 	for ((k=0; k<${j}; k++))
	 	do
	 		echo ${j} >> $filename
	 	done
	 	
	 done
done


#rm -r root


