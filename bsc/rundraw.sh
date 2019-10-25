#run
    VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
    EXE='targets/draw'
    DATA='/output/analyse_out/all/'
    OUT='/output/histo_out/all/'

    rm -rf $OUT/../*
    mkdir $VBSHOME$OUT
    for entry in `ls $VBSHOME$DATA`; do
        echo $entry
        $EXE $VBSHOME$DATA$entry $VBSHOME$OUT$entry
    done

