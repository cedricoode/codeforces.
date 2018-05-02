#! /bin/bash


source=main.cpp

if [[ -n $2 ]] 
then
    source=$2
fi


g++ $source

xsel --clipboard --output | ./a.out
