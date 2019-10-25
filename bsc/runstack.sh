VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
ONEEXE='targets/stackFirst'
EXE='targets/stack'
DATABKG='/output/histo_out/bkg/'
DATASIG='/output/histo_out/sig/'
OUT='/output/stack_out/mjj_stack.root'
i=0
j=0
colarr=(kRed kGreen kBlue kYellow kMagenta kCyan kOrange kSpring kTeal kAzure kViolet kPink)
for entry in `ls $VBSHOME$DATABKG`; do
    echo bkg $entry with color ${colarr[j]}
    for entryy in `ls $VBSHOME$DATABKG$entry` ;do
        if [ $i == 0 ]
        then 
            #echo $entryy
            $ONEEXE $VBSHOME$DATABKG$entry/$entryy $VBSHOME$OUT ${colarr[0]}
        else
            #echo $entryy
            $EXE $VBSHOME$DATABKG$entry/$entryy $VBSHOME$OUT ${colarr[j]}
        fi
        let i+=1
    done
    let j+=1
done
for entry in `ls $VBSHOME$DATASIG`; do
    echo sig with color ${colarr[j]}
    #echo $entry
    $EXE $VBSHOME$DATASIG$entry $VBSHOME$OUT ${colarr[j]}
done
