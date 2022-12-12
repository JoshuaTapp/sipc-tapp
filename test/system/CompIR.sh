#!/bin/bash
declare -r ROOT_DIR=${TRAVIS_BUILD_DIR:-$(git rev-parse --show-toplevel)}
declare -r TIPC=${ROOT_DIR}/build/src/tipc
declare -r RTLIB=${ROOT_DIR}/rtlib
declare -r SYSTEM_TEST_DIR=${ROOT_DIR}/test/system
declare -r SCRATCH_DIR=$(mktemp -d)

# Check if the required command-line argument is present
if [ -z "$1" ]; then
  echo "error: script requires a .tip file as input"
  exit 1
fi

curdir="$(basename `pwd`)"
if [ "${curdir}" != "system" ]; then
  echo "Test runner must be executed in .../tipc/test/system"
  exit 1
fi

find ${ROOT_DIR} -name '*gcda' -delete
base="$(basename $2 .tip)"

OPTIMIZED_FILE="${base}_O.ll"
UNOPTIMIZED_FILE="${base}_DO.ll"
#echo "Optimized file: $OPTIMIZED_FILE"
#echo "Unoptimized file: $UNOPTIMIZED_FILE"
${TIPC} -O=$1 --asm  $2
mv "$2.ll" "$OPTIMIZED_FILE"
${TIPC} --do --asm $2
mv "$2.ll" "$UNOPTIMIZED_FILE"


# Show the diff between the two files

colordiff -y -b ${OPTIMIZED_FILE} ${UNOPTIMIZED_FILE} > ${base}_O$1_diff.txt

# Delete the files
rm ${OPTIMIZED_FILE} ${UNOPTIMIZED_FILE}



rm -r ${SCRATCH_DIR}
