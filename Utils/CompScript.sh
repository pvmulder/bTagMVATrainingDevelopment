#!/bin/bash

g++ MVAValPlotter.C -g -o main.exe -I `root-config --incdir` `root-config --libs`
#g++ Plotter.C -g -o main.exe -I `root-config --incdir` `root-config --libs`
#./main.exe "CSVt"
./main.exe
