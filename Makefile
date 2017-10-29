# Makefile for Milestone 3
# 
# Was written by LeddarTech Inc.
# Modified by Caleb Kisby
# 

#####################################################################
# IMPORTANT
# Specify the QT5PATH variable to your QT5 lib path.
#####################################################################

include ./Definitions.mif

GPP = g++ -03 -Wall -std=c++11

CppFiles = main.cpp 

Options = $(OptionsBase) -IIncludes
Solution = ./Release/
Output = ./M3Release/
Module := $(Solution)/LeddarCDemo
QT5PATH = /usr/lib/i386-linux-gnu/

Base := main
Base := $(Base:%=$(Output)%.o)

Tout := $(Base)

$(Module) : $(Output) $(Tout)
	g++ $(CppFiles) -o Milestone3 -L$(Module) -pthread -LIncludes -LRelease -L$(QT5PATH)$(Tout) -lLeddarC -lLeddar -lLeddarTech -lQt5SerialPort -lstdc++ -Wl,-rpath=Release

$(Output)%.o : %.cpp Makefile ./Definitions.mif
	g++ $< -o$@ $(Options)

$(Output) :
	mkdir -p $(Output)

-include $(Tout:.o=.d)
