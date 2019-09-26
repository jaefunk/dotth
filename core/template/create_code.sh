#!/bin/bash

read -p "file name? " filename

year=$(date +'%Y')
small=${filename,,}
big=${filename^^}

value=`cat hpp_template.txt`
value=${value//thisyear/$year} 
value=${value//filenamesmall/$small}
value=${value//filenamebig/$big} 
echo "$value" > $filename.hpp

value=`cat cpp_template.txt`
value=${value//thisyear/$year} 
value=${value//filenamesmall/$small}
value=${value//filenamebig/$big} 
echo "$value" > $filename.cpp