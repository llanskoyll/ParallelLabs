#!/bin/bash

./build.sh lab1

echo
echo Task1
for i in $(seq 1 5)
do
    echo
    echo Num of process: $i
    ./lab1/task_run.sh $i task1
done

echo Task2
for i in $(seq 1 5)
do
    echo
    echo Num of process: $i
    ./lab1/task_run.sh $i task2
done