#!/bin/bash
cmake ..
make -j12
./doseDetector run.mac

#python processing/plot.py