#!/bin/bash


for ((i=0; i<4; i++))
do
  start=0
  end=0
  if [ $i == 0 ]; then
    start=4
    end=9
  elif [ $i == 1 ]; then
    start=10
    end=25
  elif [ $i == 2 ]; then
    start=26
    end=48
  elif [ $i == 3 ]; then
    start=49
    end=74
  fi

  for ((j=$start; j<=$end; j++))
  do
    echo "Running test -O${i} -O${j}"
    ./optimizerTest.sh  ${i} ${j}  >> ablation.txt
  done

done
