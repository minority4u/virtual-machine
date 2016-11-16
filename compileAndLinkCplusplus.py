# small script for easy c++ compiling
# compiles c++ files in the current dir directory
# this script compile and links all *.cpp files to the given targetName
# finally this scrit runs the targetFile

from glob import * 
import os

# dir = actually directory of this python script
# if you want to compile different projects change dir or copy script
dir = os.path.abspath(".")
targetName = "VM"
dateinamen = ""

# lists all *.cpp files in the given directory
for file in glob("*.cpp"):
   dateinamen += file + " "

dateinamen = "g++ -c " + dateinamen  
# print dateinamen
# executes the compile-string in a new shell
os.system(dateinamen)
dateinamen = ""

# lists all *.o files in the given directory
for file in glob("*.o"):
   dateinamen += file + " "

dateinamen = "g++ -o "+ targetName+ " " + dateinamen
# print dateinamen
# execute the linker-string in a new shell
os.system(dateinamen)
os.system(dir + "/" + targetName)
