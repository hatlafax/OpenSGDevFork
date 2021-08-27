export pyexe=d:/cpp_xxx_/Utils/Python39/python.exe
export fcdDir=d:/cpp_xxx_/Comp/builder/support/opensg/Tools/fcd2code
export opensgDir=d:/cpp_xxx_/Comp/intern/opensg

for i in $(find . -name *.fcd -type f -print); do j=$(dirname "$i"); $pyexe $fcdDir/fcd2code.py -d $i -b -p $j -r $opensgDir -t $fcdDir; done