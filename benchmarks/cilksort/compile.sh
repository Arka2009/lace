#!/bin/bash

gcc cilksort-lace.c -o lacecilksort.out -llace -llace14 -lpthread
