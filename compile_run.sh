# !/bin/bash

cpp_file=$1
exe_name=${cpp_file//'prob'/'exec'}
exe_name=${exe_name//'.cpp'/''}

rm $exe_name

echo "**************"
echo "*COMPILING...*"
echo "**************"
c++ -lm -lcrypt -O2 -std=c++11 -pipe $cpp_file -o $exe_name 

echo "************"
echo "*RUNNING...*"
echo "************"
exe_input=$2
cat $exe_input | ./$exe_name

#diff diff.txt wk_01/out_100.txt
echo "*************"
echo "*FINISHED!!!*"
echo "*************"
