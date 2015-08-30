#!/bin/bash

watchpath=$1
cppfile=$2
exeinput=$3
exename=${cppfile//'.cpp'/''}

echo "watching : $cppfile"
echo "executing : $exename"
echo ""

runsim() {
    echo ""
    echo "************"
    echo "*RUN  START*"
    echo "************"
    cat $exeinput | $exename
    echo "************"
    echo "*RUN    END*"
    echo "************"
}

# sha1sum returns the hash of its input (via SHA1 160 bit checksum)
sha=0
updatesha() {
    sha=`ls -lR --time-style=full-iso "$watchpath" | sha1sum`
}
updatesha
previoussha=$sha

compare() {
    updatesha
    if [ "$sha" != "$previoussha" ]; then
        echo "change detected!"
        build
        previoussha=$sha
    fi
}

build() {
    echo ""
    echo "**************"
    echo "*COMPILING...*"
    c++ -lm -lcrypt -O2 -std=c++11 -pipe $cppfile -o $exename 
    echo "*........DONE*"
    echo "**************"
}
 

runfuncs() {
    #compare
    build
    runsim
    echo "resuming watch 0|=<"
}

trap runfuncs SIGINT
trap exit SIGQUIT

echo -e  "--> Press Ctrl+C to force build, Ctrl+\\ to exit."
echo -en "--> watching \"$watchpath\"."

while true; do
    #compare
    sleep 10
done

