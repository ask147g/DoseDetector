#!/bin/bash
cmake ..
make -j12
./doseDetector neutron.mac

python processing/doseRate.py
python processing/activity.py

python processing/tableDoseRate.py
python processing/tableActivity.py