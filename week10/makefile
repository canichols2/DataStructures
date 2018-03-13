###############################################################
# Program:
#     Week 10, Map
#     Brother Ercanbrack, CS235
# Author:
#     Cody Nichols
# Summary:
#     Use map to count occurances in BOM and D&C
# Time:
#     TBD
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week10.o
	g++ -o a.out week09.o 
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp

