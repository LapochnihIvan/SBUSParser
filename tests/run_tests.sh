#!/bin/bash

if [[ $# > 2 ]]; then
    echo "Invalid count of options" >&2
    
    exit 1
fi

for flag in "$@"
do
    case $flag in
        "-rebuild")
            is_need_rebuild=true
            ;;
        "-memcheck")
            is_need_memcheck=true
            ;;
        *)
            echo "\"$flag\" is inavid option" >&2
    
            exit 1
            ;;
    esac
done

cd "$( dirname "$0" )"

if [[ ! -d build ]]; then
    mkdir build
elif [[ $is_need_rebuild ]]; then
    rm -rf build/*
fi

cd build
cmake .. 1>/dev/null
cmake --build . -- -j$(nproc) 1>/dev/null

if [[ $is_need_memcheck ]]; then
    ctest -T memcheck
else
    ctest
fi

exit
