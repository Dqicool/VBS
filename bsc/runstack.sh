#!/bin/bash
make draw
make stack
SECONDS=0
    EXE='/targets/draw'
    DATA='/output/analyse_out/999_all/'
    OUT='/output/draw_out/999_all/'

    rm -rf $OUT/*
    mkdir -p $VBSHOME$OUT
    i=1
    for entry in `ls $VBSHOME$DATA`; do
        echo [$i] $entry
        ($VBSHOME$EXE $VBSHOME$DATA$entry $VBSHOME$OUT$entry) &
        let i+=1
    done
    wait

    $VBSHOME/targets/stack
ELAPSED="Elapsed: $(($SECONDS / 3600))hrs $((($SECONDS / 60) % 60))min $(($SECONDS % 60))sec"
echo $ELAPSED
