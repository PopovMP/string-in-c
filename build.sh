#! /usr/bin/bash

set -ueo pipefail

CC='/usr/bin/gcc'
WARN='-Wall -Wextra -Wpedantic'
STD='-std=c2x'
OPT='-O2'

$CC $WARN $STD $OPT -c -o string.o string.c
$CC $WARN $STD $OPT -o test string.o string.test.c

