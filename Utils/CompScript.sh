#!/bin/bash

g++ MVAValPlotter.C -g -o main.exe -I `root-config --incdir` `root-config --libs`

./main.exe
