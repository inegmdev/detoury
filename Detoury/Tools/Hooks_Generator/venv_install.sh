#!/bin/bash
source ./venv/bin/activate
which python
# Upgrade pip
python -m pip install -U pip
# Upgrade setuptools
python -m pip install -U setuptools
# Install all the needed packages fromm requirements file
pip install -r requirements.txt