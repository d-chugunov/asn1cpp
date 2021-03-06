#!/bin/bash


shell="../../../asn1cpp"
asn_files_path="../../tests"
skeletons_folder="../../../../skeletons"

check()
{
    local testdir="module"
    rm -f -r $testdir
    if [ ! -d $testdir ]; then
	    mkdir $testdir		|| exit $?
    fi
    cd $testdir			|| exit $?

    for fileext in $(find $asn_files_path -name \*.asn*); do
	files=$(basename $fileext)
	ind=`expr index $files '~'`
	if [ $ind -eq 0 ];
	then
	  flags=`echo $files | awk '{split($0,a,".asn");print a[2]}'`
	  files=`echo $files | awk '{split($0,a,".asn");print a[1]}'`
	
	  "$shell" $flags $1 -flink-skeletons -S $skeletons_folder "$fileext" 2>/dev/null
	fi
    done

    #remove all symlinks
    find . -maxdepth 1 -type l -exec rm -f {} \;


# Create a Makefile for the project.
cat > Makefile <<EOM
# This file is autogenerated by ../$0

COMMON_FLAGS= -I. -I$skeletons_folder -I..
CXXFLAGS = \${COMMON_FLAGS} ${CXXFLAGS} $2 -g -O0 -std=c++11 -Wall -Wextra -Wwrite-strings -Wmaybe-uninitialized

CXX ?= ${CXX}

all: check-executable
check-executable: compiled-module ../../*.cpp
	@rm -f *.core
	\$(CXX) \$(CXXFLAGS) -o check-executable ../../*.cpp *.cpp $skeletons_folder/*.cpp

compiled-module: $shell *.cpp *.hpp $skeletons_folder/*.cpp $skeletons_folder/*.hpp
	@touch compiled-module

check-succeeded: check-executable
	@rm -f check-succeeded
	./check-executable
	@touch check-succeeded

check: check-succeeded

clean:
	@rm -f *.o check-executable
EOM

    # Perform building and checking
    make check || exit $?

}

do_check() {
  if [ ! -d $1 ]; then
    mkdir $1		|| exit $?
  fi
  cd $1
  check "$2" "$3"
  cd ../..
}

do_check secure-ptrs "" -DDEBUG
do_check secure-ptrs-no-switch -fno-switch -DDEBUG
do_check insecure-ptrs -finsecure-pointers "-DINSECURE_POINTERS -DDEBUG"
do_check insecure-ptrs-no-switch "-finsecure-pointers -fno-switch" "-DINSECURE_POINTERS -DDEBUG"
do_check secure-ptrs-ptr-choice-getters "-fptr-choice-getters" "-DDEBUG -DPTR_CHOICE_GETTERS"

exit 0
