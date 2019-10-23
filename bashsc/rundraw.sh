VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
EXE='targets/draw'
DATA='/output/analyse_out/all/'
OUT='/output/histo_out/all/'

for entry in `ls $VBSHOME$DATA`; do
    $EXE $VBSHOME$DATA$entry $VBSHOME$OUT$entry
done
