VBSHOME='/TANK/MainShare/Projects/Qichen/VBS/'
FOL='/data/'
LNED=$FOL/all/
VBSF=$FOL/vbsf/
QQ4L=$FOL/qq4l/
GG4L=$FOL/gg4l/
HIGS=$FOL/higgs/
TRIB=$FOL/triboson/
REST=$FOL/rest/
WZ3L=$FOL/WZlvlll
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

for entry in `ls $VBSHOME$LNED | grep 361601`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$WZ3L
done

for entry in `ls $VBSHOME$LNED | grep 410472`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$HIGS
done


for entry in `ls $VBSHOME$LNED | grep 3450` ; do
    $LN $VBSHOME$LNED$entry $VBSHOME$HIGS
done

for entry in `ls $VBSHOME$LNED | grep -v 36424 | grep -v 364250 | grep -v 34570 | grep -v 344235 | grep -v 345060 | grep -v 364364 | grep -v 34634 | grep -v 361601 | grep -v 3450 | grep -v 410472`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$REST
done


