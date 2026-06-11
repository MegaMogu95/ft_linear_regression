#!/bin/bash
set -e
echo -e "0\n0" > theta.txt;
./train $1;
./r_squared;
python3 bonuses/plot.py