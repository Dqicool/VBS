#VBSHOME='/mnt/MainShare/Projects/Qichen/VBS/'
ONEEXE='/targets/stackFirst'
EXE='/targets/stack'
DATA='/output/histo_out/'

OUT='/output/stack_out/mjj_stack.root'
i=0
j=0
colarr=(kRed kGreen kBlue kYellow kMagenta kCyan kOrange kSpring kTeal kAzure kViolet kPink)
for entry in `ls $VBSHOME$DATA | grep -v 999`; do
    echo $entry with color ${colarr[j]}
    for entryy in `ls $VBSHOME$DATA$entry` ;do
        if [ $i == 0 ]
        then 
            #echo $entryy
            $VBSHOME$ONEEXE $VBSHOME/$DATA$entry/$entryy $VBSHOME$OUT ${colarr[0]}
        else
            #echo $entryy
            $VBSHOME$EXE $VBSHOME/$DATA$entry/$entryy $VBSHOME$OUT ${colarr[j]}
        fi
        let i+=1
    done
    let j+=1
done

`targets/drawstack`
