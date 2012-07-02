#!/bin/bash

g++ MVAVarPlotter.C -g -o main.exe -I `root-config --incdir` `root-config --libs`

./main.exe
