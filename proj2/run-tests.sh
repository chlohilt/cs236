#!/bin/bash

# script for project 3 pass-off tests

program="project3"

buckets="20 40 60 80 100"

numbers_20="21 22 24"
numbers_40="41 42"
numbers_60="61 62"
numbers_80="81 82"
numbers_100="101 102 104 105"

testdir="project3-passoff"
diffopts=" -a -i -E -Z -b -w -B "  # ignore whitespace

g++ -Wall -Werror -std=c++17 -g *.cpp -o $program

for bucket in $buckets ; do

    echo Bucket $bucket
    eval numbers=\$numbers_$bucket

    for number in $numbers ; do

	echo "Running input" $number

	inputfile=$testdir/$bucket/input$number.txt
	answerfile=$testdir/$bucket/answer$number.txt
	outputfile=actual$number.txt

	./$program $inputfile > $outputfile

	diff $diffopts $answerfile $outputfile || echo "diff failed on test" $number

	rm $outputfile

    done
done

rm $program

