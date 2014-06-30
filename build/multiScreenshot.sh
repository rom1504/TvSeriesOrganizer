#!/bin/bash
if [[ $# -ne 4 ]]
then
		echo "usage : $0 <parallel tasks limit> <binary file> <data dir prefix> <screenshot dir prefix>" 
		exit 1
fi

parallelTasksLimit=$1
binaryFile=$2
dataDirPrefix=$3
screenshotDirPrefix=$4

sizes=( Smartphone Tablet )
langs=( en fr_FR it ro_RO )
disp=10
parallel=0
for siz in "${sizes[@]}"
do
	for lang in "${langs[@]}"
	do
		if [[ $parallel -eq $parallelTasksLimit ]]
		then
			echo waiting...
			wait
			parallel=0
		else
			sleep 3
		fi
		suffix=$lang"_"$siz
		ddir=$dataDirPrefix$suffix
		sdir=$screenshotDirPrefix$suffix
		rm -rf $ddir
		mkdir -p $ddir
		rm -rf $sdir
		./screenshot$siz.sh "$binaryFile --data-dir $ddir" :$disp $lang $sdir &
		((disp++))
		((parallel++))
	done
done
wait