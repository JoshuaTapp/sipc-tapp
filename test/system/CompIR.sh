#!/bin/bash
declare -r ROOT_DIR=${TRAVIS_BUILD_DIR:-$(git rev-parse --show-toplevel)}
declare -r TIPC=${ROOT_DIR}/build/src/tipc
declare -r RTLIB=${ROOT_DIR}/rtlib
declare -r SYSTEM_TEST_DIR=${ROOT_DIR}/test/system
declare -r SCRATCH_DIR=$(mktemp -d)

# Check if the required command-line argument is present
if [ -z "$2" ]; then
  echo "error: script requires a .tip file as input"
  exit 1
fi

curdir="$(basename `pwd`)"
if [ "${curdir}" != "system" ]; then
  echo "Test runner must be executed in .../tipc/test/system"
  exit 1
fi
doFlag=0

if [ -z "$3" ]; then
  doFlag=1
fi

file=""
compileArgsOP=""
compileArgsUN=""
op1=""
op2=""

if [ $doFlag -eq 1 ]; then
  file="$2"
  compileArgsOP="-O=${1} --asm $file"
  compileArgsUN="--do --asm $file"
  op1=$1
  op2="DO"
else
  file="$3"
  compileArgsOP="-O=${1} --asm $file"
  compileArgsUN="-O=${2} --asm $file"
  op1=$1
  op2=$2
fi

find ${ROOT_DIR} -name '*gcda' -delete

base="$(basename ${file%.*})"

OPTIMIZED_FILE="${base}_O.ll"
UNOPTIMIZED_FILE="${base}_DO.ll"
#echo "Optimized file: $OPTIMIZED_FILE"
#echo "Unoptimized file: $UNOPTIMIZED_FILE"
${TIPC} $compileArgsOP
mv "$file.ll" "$OPTIMIZED_FILE"
${TIPC} $compileArgsUN
mv "$file.ll" "$UNOPTIMIZED_FILE"

op="UNOPTIMIZED PROGRAM: ${UNOPTIMIZED_FILE} | opt_level = ${op2}"
p="OPTIMIZED PROGRAM: ${OPTIMIZED_FILE} | opt_level = ${op1}"
colordiff -y --ignore-blank-lines --suppress-common-lines  --minimal <(echo "$p") <(echo "$op")


colordiff -y --ignore-blank-lines --suppress-common-lines  --minimal ${OPTIMIZED_FILE} ${UNOPTIMIZED_FILE}


colordiff -y --ignore-blank-lines --suppress-common-lines ${OPTIMIZED_FILE} ${UNOPTIMIZED_FILE} > ${base}_O$1_diff.txt

# Delete the files
rm ${OPTIMIZED_FILE} ${UNOPTIMIZED_FILE}



rm -r ${SCRATCH_DIR}
