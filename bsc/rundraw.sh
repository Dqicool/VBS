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

#cp
    VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
    OUTDIR='/output/histo_out/'

    LNED=$OUTDIR/all/
    INC=$OUTDIR/inc/
    BKG=$OUTDIR/bkg/
    SIG=$OUTDIR/sig/
    LN='cp'

    mkdir $VBSHOME$INC
    mkdir $VBSHOME$BKG
    mkdir $VBSHOME$SIG

    for entry in `ls $VBSHOME$LNED | grep -v 364250 | grep -v 344235 | grep -v 364364`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$BKG$entry
    done

    for entry in `ls $VBSHOME$LNED | grep 364250`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$INC$entry
    done

    for entry in `ls $VBSHOME$LNED | grep 344235`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$SIG$entry
    done

    for entry in `ls $VBSHOME$LNED | grep 364364`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$SIG$entry
    done
#mv
    VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
    BKG='output/histo_out/bkg/'
    LNED=$BKG
    EWTRI=$BKG/EWTriBoson/
    QCDGG=$BKG/QCDggZZ/
    QCDZZ=$BKG/QCDZZjj/
    SINBO=$BKG/sinBoson/
    TTBAR=$BKG/ttbar/
    WZ=$BKG/WZlllv
    LN='mv'

    mkdir $EWTRI
    mkdir $QCDGG
    mkdir $QCDZZ
    mkdir $SINBO
    mkdir $TTBAR
    mkdir $WZ

    for entry in `ls $VBSHOME$LNED | grep 364243`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
    done

    for entry in `ls $VBSHOME$LNED | grep 364245`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
    done

    for entry in `ls $VBSHOME$LNED | grep 364247`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
    done

    for entry in `ls $VBSHOME$LNED | grep 364248`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
    done


    for entry in `ls $VBSHOME$LNED | grep 345060`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QCDGG
    done

    for entry in `ls $VBSHOME$LNED | grep 345706`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QCDGG
    done

    for entry in `ls $VBSHOME$LNED | grep 345708`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QCDGG
    done

    for entry in `ls $VBSHOME$LNED | grep 345038`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QCDZZ
    done

    for entry in `ls $VBSHOME$LNED | grep 345039`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QCDZZ
    done

    for entry in `ls $VBSHOME$LNED | grep 345040`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QCDZZ
    done

    for entry in `ls $VBSHOME$LNED | grep 344295`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
    done

    for entry in `ls $VBSHOME$LNED | grep 344296`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
    done

    for entry in `ls $VBSHOME$LNED | grep 344297`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
    done

    for entry in `ls $VBSHOME$LNED | grep 344298`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
    done

    for entry in `ls $VBSHOME$LNED | grep 346340`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
    done

    for entry in `ls $VBSHOME$LNED | grep 346341`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
    done

    for entry in `ls $VBSHOME$LNED | grep 346342`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
    done

    for entry in `ls $VBSHOME$LNED | grep 410142`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
    done

    for entry in `ls $VBSHOME$LNED | grep 410472`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
    done

    for entry in `ls $VBSHOME$LNED | grep 361601`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$WZ
    done
