APP=main
ALLFILES=`ls *.c`
all:
	  @echo compiling $(ALLFILES).
	  @gcc $(ALLFILES) -o $(APP)
