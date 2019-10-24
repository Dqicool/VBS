#run
    VBSHOME='/mnt/MainShare/Projects/Qichen/VBS'
    EXE='targets/analyse'
    DATA='/output/preAna_out/all/'
    OUT='/output/analyse_out/all/'
    mkdir $VBSHOME/$OUT
    declare arr
    i=0
    j=0
    for entry in `ls $VBSHOME$DATA`; do
        IFS='.' 
        read -ra ADDR <<< "$entry"
        if [ $i != 0 ]
        then
            k=`expr j-1`
            tmp=${arr[$k]}
            if [ ${ADDR[1]} != $tmp ]
            then
                arr[j]=${ADDR[1]}
                let i+=1
                let j+=1
            else
                let i+=1
            fi
        else 
            arr[j]=${ADDR[1]}
            let i+=1
            let j+=1
        fi
    done
    IFS=$'\n' 
    for number in "${arr[@]}";do
        l=0
        declare arr2
        for entry2 in `ls $VBSHOME$DATA | grep $number`; do
            arr2[l]="$entry2"
            let l+=1
        done
        IFS='.' 
        read -ra ADDR2 <<< "${arr2[0]}"
        IFS=$'\n'
        echo "-----------------------------------"
        echo "Runing ${ADDR2[1]}......"
        echo "File1 ${arr2[0]}"
        echo "File2 ${arr2[1]}"
        echo "File3 ${arr2[2]}"
        echo "OutFile ${ADDR2[1]}.${ADDR2[2]}.root"
        `$VBSHOME/$EXE $VBSHOME$DATA${arr2[0]} $VBSHOME$DATA${arr2[1]} $VBSHOME$DATA${arr2[2]} $VBSHOME$OUT${ADDR2[1]}.${ADDR2[2]}.root`
        echo "Done......"
        echo "-----------------------------------"
    done
#cp
    VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
    OUTDIR='/output/analyse_out/'

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
    BKG='output/analyse_out/bkg/'
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






