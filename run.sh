#!/bin/bash
cmake ..
make -j12
./doseDetector forward.mac

python processing/doseRatePlot.py
python processing/activityPlot.py

python processing/doseRateTable.py
python processing/activityTable.py
