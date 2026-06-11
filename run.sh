#!/bin/bash
set -e
python3 -m venv venv
source venv/bin/activate
pip install matplotlib
pip install PyQt5
make
echo -e "0\n0" > theta.txt;
./train $1;
./r_squared;
python3 bonuses/plot.py