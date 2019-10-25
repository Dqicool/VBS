VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
EXE='targets/preana'
DATA='/data/all/'
OUT='/output/preAna_out'

i=1
rm -rf $VBSHOME$OUT/all

mkdir -p $VBSHOME$OUT/all

for entry in `ls $VBSHOME$DATA`; do
    echo "[$i]" runing $entry
    $VBSHOME$EXE $VBSHOME$DATA$entry $VBSHOME$OUT/all/$entry
    let i+=1
    #echo "done"
done
