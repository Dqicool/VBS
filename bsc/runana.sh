#run
    #VBSHOME='/mnt/MainShare/Projects/Qichen/VBS'
    EXE='/targets/analyse'
    DATA='/output/preAna_out/999_all/'
    OUT='/output/analyse_out/'
    rm -rf $VBSHOME/$OUT/999_all/*
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
        (`$VBSHOME/$EXE $VBSHOME$DATA${arr2[0]} $VBSHOME$DATA${arr2[1]} $VBSHOME$DATA${arr2[2]} $VBSHOME$OUT/999_all/${ADDR2[1]}.${ADDR2[2]}.root`) &
        #echo "Done......"
        #echo "-----------------------------------"
        let ii+=1
    done
    wait
    echo "alldone"
