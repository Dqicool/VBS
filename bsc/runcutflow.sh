#!/bin/bash
make cutflow
make stackcutflow

    EXE='/targets/cutflow'
    DATA='/output/analyse_out/999_all/'
    OUT='/output/cutflow_out/999_all/'

    rm -rf $OUT/*
    mkdir -p $VBSHOME$OUT
    i=1
    for entry in `ls $VBSHOME$DATA`; do
        echo [$i] $entry
        ($VBSHOME$EXE $VBSHOME$DATA$entry $VBSHOME$OUT$entry) &
        let i+=1
    done
    wait




