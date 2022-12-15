#!/bin/bash
declare -r ROOT_DIR=${TRAVIS_BUILD_DIR:-$(git rev-parse --show-toplevel)}
declare -r TIPC=${ROOT_DIR}/build/src/tipc
declare -r RTLIB=${ROOT_DIR}/rtlib
declare -r SYSTEM_TEST_DIR=${ROOT_DIR}/test/system
declare -r SCRATCH_DIR=$(mktemp -d)

# $1 = file1 opt level, $2 = file2 opt level,
# $3 = file to test, $4 = args to pass to TIPProgMetrics

# Check if the required command-line argument is present
if [ -z "$1" ]; then
  echo "error: script requires a opLevel1 as input"
  exit 1
fi
if [ -z "$2" ]; then
  echo "error: script requires a opLevel2 as input"
  exit 1
fi
if [ -z "$3" ]; then
  echo "error: script requires a .tip file as input"
  exit 1
fi

curdir="$(basename `pwd`)"
if [ "${curdir}" != "system" ]; then
  echo "Test runner must be executed in .../tipc/test/system"
  exit 1
fi
doFlag=0

# if opLevel2 is -1, then run with optimizations disabled
if [ "$3" == -1 ]; then
  doFlag=1
fi

file=""
compileArgsOP=""
compileArgsUN=""
op1=""
op2=""


scoreK=10

if [ $doFlag -eq 1 ]; then
  file="$2"
  compileArgsOP="-O=${1}  $file"
  compileArgsUN="--do     $file"
  op1=$1
  op2="DO"
else
  file="$3"
  compileArgsOP="-O=${1}  $file"
  compileArgsUN="-O=${2}  $file"
  op1=$1
  op2=$2
fi

find ${ROOT_DIR} -name '*gcda' -delete

  base="$(basename ${file%.*})"
  file1="${base}_${op1}"
  file2="${base}_${op2}"

    # Check if the program is in the linkedlist list
  if [[ $base == *loop* ]]; then
    # Add command line arguments to the program when running it
    cmd_args=2
  elif [[ $base == *ref* ]]; then
    cmd_args="3 3 1"
  elif [[ $base == *tail*  ]]; then
    cmd_args=10
  else
    cmd_args=""
  fi

  # test optimized program
  ${TIPC}  $compileArgsOP
  ${TIPCLANG} -w $file.bc ${RTLIB}/tip_rtlib.bc -o $file1
  ${TIPC}  $compileArgsUN
  ${TIPCLANG} -w $file.bc ${RTLIB}/tip_rtlib.bc -o $file2
echo "Program: ${base} | opt_level = ${op1} | opt_level = ${op2}"
echo "$(printf "%-20s" "${file}")" $(./TIPProgMetrics ${file1} ${file2} ${scoreK} ${cmd_args})

# Delete the files
rm ${file1} ${file2}
rm ${file}.bc


rm -r ${SCRATCH_DIR}
