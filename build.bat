@echo off
title Cranky's Lab Build System
del rom\build.log
python build\build.py >> rom/build.log
python build\dump_pointer_tables_vanilla.py >> rom/build.log