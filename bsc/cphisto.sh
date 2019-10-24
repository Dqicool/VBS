VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
OUTDIR='/output/preAna_out/'
# LNED='/data/all/'
# INC='/data/inc/'
# BKG='/data/bkg/'
# SIG='/data/sig/'
# LN='cp'
LNED=$OUTDIR/all_no_fidw/
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

