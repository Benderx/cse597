#!/bin/bash
make

if [ $? -eq 0 ]
then
	echo "make ran successfully"
	./run
	python ./graph_times.py
else
	echo "did not run due to makefile errors"
fi