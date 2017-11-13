# Makefile for Linux version of Leddar SDK.
# Copyrigth 2015 LeddarTech Inc.

#********************************************************
# IMPORTANT
# Specify the QT5PATH variable to your QT5 lib path.
#********************************************************

include ./Definitions.mif

Options = $(OptionsBase) -I./Includes
Solution = Release/
Output = Output/
Module := $(Solution)LeddarCDemo
QT5PATH = /usr/lib/x86_64-linux-gnu

Base := Main
Base := $(Base:%=$(Output)%.o)

Tout := $(Base)

$(Module) : $(Output) $(Tout)
	gcc Main.c -o Main -L$(Module) -pthread -LIncludes -LRelease -L$(QT5PATH)$(Tout) -lLeddarC -lLeddar -lLeddarTech -lQt5SerialPort -lstdc++ -Wl,-rpath=Release

$(Output)%.o : %.c Makefile ./Definitions.mif
	$(Compiler) $< -o$@ $(Options)

$(Output) :
	mkdir -p $(Output)

-include $(Tout:.o=.d)

clean:
	\rm *.o *~ Main
