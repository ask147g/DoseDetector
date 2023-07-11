#!/bin/bash
cmake ..
make -j12
./doseDetector forward.mac

python processing/nuclides.py