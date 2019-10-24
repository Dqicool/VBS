VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
EXE='targets/preana'
DATA='/data/bkg/ttbar/'
OUT='/output/preAna_out/all_no_fidw/'
mkdir $VBSHOME$OUT
for entry in `ls $VBSHOME$DATA | grep 410472`; do
    echo runing $entry
    $EXE $VBSHOME$DATA$entry $VBSHOME$OUT$entry
    echo "done"
done
