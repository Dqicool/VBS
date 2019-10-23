VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
BKG='output/analyse_out/bkg/'
LNED=$BKG
EWTRI=$BKG/EWTriBoson/
QCDGG=$BKG/QCDggZZ/
QCDZZ=$BKG/QCDZZjj/
SINBO=$BKG/sinBoson/
TTBAR=$BKG/ttbar/
WZ=$BKG/WZlllv
LN='mv'

for entry in `ls $VBSHOME$LNED | grep 364243`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
done

for entry in `ls $VBSHOME$LNED | grep 364245`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
done

for entry in `ls $VBSHOME$LNED | grep 364247`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
done

for entry in `ls $VBSHOME$LNED | grep 364248`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$EWTRI
done


for entry in `ls $VBSHOME$LNED | grep 345060`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$QCDGG
done

for entry in `ls $VBSHOME$LNED | grep 345706`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$QCDGG
done

for entry in `ls $VBSHOME$LNED | grep 345708`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$QCDGG
done

for entry in `ls $VBSHOME$LNED | grep 345038`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$QCDZZ
done

for entry in `ls $VBSHOME$LNED | grep 345039`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$QCDZZ
done

for entry in `ls $VBSHOME$LNED | grep 345040`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$QCDZZ
done

for entry in `ls $VBSHOME$LNED | grep 344295`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
done

for entry in `ls $VBSHOME$LNED | grep 344296`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
done

for entry in `ls $VBSHOME$LNED | grep 344297`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
done

for entry in `ls $VBSHOME$LNED | grep 344298`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$SINBO
done

for entry in `ls $VBSHOME$LNED | grep 346340`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
done

for entry in `ls $VBSHOME$LNED | grep 346341`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
done

for entry in `ls $VBSHOME$LNED | grep 346342`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
done

for entry in `ls $VBSHOME$LNED | grep 410142`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
done

for entry in `ls $VBSHOME$LNED | grep 410472`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$TTBAR
done

for entry in `ls $VBSHOME$LNED | grep 361601`; do
    $LN $VBSHOME$LNED$entry $VBSHOME$WZ
done
