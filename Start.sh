#!/bin/bash

if [ -d $1 ] && [ -d $2 ]; then
    build/bin/main -w $1 -c $2
else
    echo Enter paths e.g ./Start.sh path-to-folder path-for-copy-file
fi

exit 0