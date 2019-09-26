
#!/usr/local/bin/bash
echo $BASH_VERSION


read -p "file name? " filename
echo $filename
year=$(date +'%Y')
echo $year
small=${filename,}
echo $small
big=${filename^}

value=`cat hpp_template.txt`
value=${value//thisyear/$year} 
value=${value//filenamesmall/$small}
value=${value//filenamebig/$big} 
echo "$value" > $filename.hpp

year2=$(date +'%Y')
small2=${filename,,[a,z]}
big2=${filename^^[a,z]}

value2=`cat cpp_template.txt`
value2=${value2//thisyear/$year2}
value2=${value2//filenamesmall/$small2}
value2=${value2//filenamebig/$big2}
echo "$value2" > $filename.cpp
