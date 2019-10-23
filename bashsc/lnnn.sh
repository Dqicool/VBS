VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
# LNED='data/all/'
# INC='data/inc/'
# BKG='data/bkg/'
# SIG='data/sig/'
# LN='cp'
LNED='output/analyse_out/all/'
INC='output/analyse_out/inc/'
BKG='output/analyse_out/bkg/'
SIG='output/analyse_out/sig/'
LN='cp'


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

