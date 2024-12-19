#!/bin/sh

echo "Write by ourselves if so..."
export MALLOC_DEBUG=1
LD_PRELOAD=./libt_malloc.so tests/srcs/test
$@