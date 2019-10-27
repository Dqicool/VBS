#run
    #VBSHOME='/mnt/MainShare/Projects/Qichen/VBS'
    EXE='/targets/analyse'
    DATA='/output/preAna_out/999_all/'
    OUT='/output/analyse_out/'
    rm -rf $VBSHOME/$OUT/*
    mkdir -p $VBSHOME/$OUT/999_all
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
    ii=1
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
        #echo "-----------------------------------"
        echo "[$ii] Runing ${ADDR2[1]}......"
        #echo "File1 ${arr2[0]}"
        #echo "File2 ${arr2[1]}"
        #echo "File3 ${arr2[2]}"
        #echo "OutFile ${ADDR2[1]}.${ADDR2[2]}.root"
        `$VBSHOME/$EXE $VBSHOME$DATA${arr2[0]} $VBSHOME$DATA${arr2[1]} $VBSHOME$DATA${arr2[2]} $VBSHOME$OUT/999_all/${ADDR2[1]}.${ADDR2[2]}.root`
        #echo "Done......"
        #echo "-----------------------------------"
        let ii+=1
    done

#ln
    FOL='/output/analyse_out/'

    LNED=$FOL/999_all/

    VBSF=$FOL/111_vbsf/
    QQ4L=$FOL/000_qq4l/
    GG4L=$FOL/001_gg4l/
    HIGS=$FOL/004_higgs/
    TRIB=$FOL/003_triboson/
    REST=$FOL/005_rest/
    WZ3L=$FOL/002_WZlvlll/
    LN='ln -s'

    rm -rf $VBSHOME$VBSF
    rm -rf $VBSHOME$QQ4L
    rm -rf $VBSHOME$GG4L
    rm -rf $VBSHOME$HIGS
    rm -rf $VBSHOME$TRIB
    rm -rf $VBSHOME$REST
    rm -rf $VBSHOME$WZ3L


    mkdir $VBSHOME$VBSF
    mkdir $VBSHOME$QQ4L
    mkdir $VBSHOME$GG4L
    mkdir $VBSHOME$HIGS
    mkdir $VBSHOME$TRIB
    mkdir $VBSHOME$REST
    mkdir $VBSHOME$WZ3L

    for entry in `ls $VBSHOME$LNED | grep 36424`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$TRIB
    done

    for entry in `ls $VBSHOME$LNED | grep 364250`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QQ4L
    done

    for entry in `ls $VBSHOME$LNED | grep 34570`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$GG4L
    done

    for entry in `ls $VBSHOME$LNED | grep 344235`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$VBSF
    done

    for entry in `ls $VBSHOME$LNED | grep 345060`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$GG4L
    done

    for entry in `ls $VBSHOME$LNED | grep 364364`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$VBSF
    done

    for entry in `ls $VBSHOME$LNED | grep 361601`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$WZ3L
    done

    for entry in `ls $VBSHOME$LNED | grep 34634`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$QQ4L
    done

    for entry in `ls $VBSHOME$LNED | grep 410472`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$HIGS
    done


    for entry in `ls $VBSHOME$LNED | grep 3450 | grep 345060` ; do
        $LN $VBSHOME$LNED$entry $VBSHOME$HIGS
    done

    for entry in `ls $VBSHOME$LNED | grep -v 36424 | grep -v 364250 | grep -v 34570 | grep -v 344235 | grep -v 345060 | grep -v 364364 | grep -v 34634 | grep -v 361601 | grep -v 3450 | grep -v 410472`; do
        $LN $VBSHOME$LNED$entry $VBSHOME$REST
    done
