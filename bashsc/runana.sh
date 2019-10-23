VBSHOME='/mnt/MainShare/Projects/Qichen/VBS'
EXE='targets/analyse'
DATA='/data/all/'
OUT='/output/analyse_out/all/'
declare arr
i=0
j=0
for entry in `ls $VBSHOME/data/all`; do
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
    for entry2 in `ls $VBSHOME/data/all | grep $number`; do
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





