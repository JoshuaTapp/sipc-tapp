#!/bin/bash
declare -r ROOT_DIR=${TRAVIS_BUILD_DIR:-$(git rev-parse --show-toplevel)}
declare -r TIPC=${ROOT_DIR}/build/src/tipc
declare -r RTLIB=${ROOT_DIR}/rtlib
declare -r SCRATCH_DIR=$(mktemp -d)

if [ -z "${TIPCLANG}" ]; then
  echo error: TIPCLANG env var must be set
  exit 1
fi

curdir="$(basename `pwd`)"
if [ "${curdir}" != "system" ]; then
  echo "Test runner must be executed in .../tipc/test/system"
  exit 1
fi

# this is the number of sample metrics to collect from each program
scoreK=30
opLevel="-O=$1"
# Self contained test cases
echo  "Optimized vs. Unoptimized Programs: using opt_level = $opLevel"
echo -e "   -1 ~ Unoptimized is better, 0 = No difference, 1 ~ Optimized is better"
echo "For other scores: ratio of optimized to unoptimized"
echo "---Score-----FileScore-------TimeScore-------MemAcessScore-------------"
for i in optests/*.tip
do
  base="$(basename $i .tip)"
  o_file="${base}_O"
  do_file="${base}_DO"

  # Check if the program is in the linkedlist list
  if [[ $base == *loop* ]]; then
    # Add command line arguments to the program when running it
    cmd_args=2
  else
    cmd_args=""
  fi

  # test optimized program
  ${TIPC} $opLevel  $i
  ${TIPCLANG} -w $i.bc ${RTLIB}/tip_rtlib.bc -o $o_file
  ${TIPC} -do $i
  ${TIPCLANG} -w $i.bc ${RTLIB}/tip_rtlib.bc -o $do_file

    # run TIPProgMetrics on the compiled program
  echo "${base}" $(./TIPProgMetrics ${o_file} ${do_file} ${scoreK} ${cmd_args} )
  rm ${o_file}
  rm ${do_file}
  rm $i.bc
done

# Cleanup
rm -rf ${SCRATCH_DIR}
