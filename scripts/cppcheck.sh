#!/bin/sh

cppcheck . --language=c++ --enable=all -I Source --suppress=missingIncludeSystem -ibuild
