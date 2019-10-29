#VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
EXE='/targets/preana'
DATA='/data/999_all/'
OUT='/output/preAna_out'

i=1
rm -rf $VBSHOME$OUT/999_all/*

mkdir -p $VBSHOME$OUT/999_all

for entry in `ls $VBSHOME$DATA`; do
    echo "[$i]" runing $entry
    ($VBSHOME$EXE $VBSHOME$DATA$entry $VBSHOME$OUT/999_all/$entry) &
    let i+=1
    #echo "done"
done
wait

