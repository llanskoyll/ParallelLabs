#!/bin/sh

mpirun --allow-run-as-root -np $1 ./lab1/build/$2
