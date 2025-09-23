#!/bin/sh

search_dir="$1"
filename="$2"

find "$search_dir" -name "$filename" -exec perl -0777 -ne '
    print "$ARGV\n" if /#pragma\s+omp\s+parallel\s+for.*?\n(?:\s*\/\/[^\n]*\n|\s*#pragma[^\n]*\n)*\s*for\s*\([^)]*\)\s*\{\s*(?:\/\/[^\n]*\n|\s*)*\}/s
' {} +