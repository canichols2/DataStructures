###############################################################
# Program:
#     Week 13, Geneology
#     Brother Ercanbrack, CS235
# Author:
#     Cody Nichols
# Summary:
#     <put a description here>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o spellCheck.o
	g++ -o a.out week13.o spellCheck.o -g
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
week13.o:  week13.cpp 
	g++ -c week13.cpp -g
