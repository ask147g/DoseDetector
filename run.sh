#!/bin/bash
cmake ..
make -j12
./doseDetector run.mac

python processing/doseRate.py
python processing/activity.py