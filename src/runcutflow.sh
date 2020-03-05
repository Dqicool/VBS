#!/bin/bash
make cutflow
make stackcutflow
    VBSHOME='/mnt/SSD/VBS'
    EXE='/build/cutflow'
    DATA='/output/analyse_out/'
    OUT='/output/cutflow_out/'

    rm -rf $OUT/*
    mkdir -p $VBSHOME$OUT
    i=1
    for entry in `ls $VBSHOME$DATA`; do
        echo [$i] $entry
        ($VBSHOME$EXE $VBSHOME$DATA$entry $VBSHOME$OUT$entry) &
        let i+=1
    done
    wait
    
    build/stackcutflow




