# *****************************************************************
#
# Starter Makefile
#
# Contains rules for:
#
# -    (executable target)
# - .o (object file)
# - .PHONY (all, clean and test)
#
#
# Uses the following variables (built-in and user-defined):
#
# CC = C compiler (gcc)
# CFLAGS = compiler options (e.g. -g)
# LINKER_FLAGS = specify libraries to link in
# $@ = target
# $^ = all dependencies
# $< = first dependency only (not used in this solution)
#
# Generic "rule" terminology:
#
# target:dependency
# [TAB] <CMD1>
# [TAB] <CMD2>
#
# GCC options used in this Makefile:
#
# -c = "compile only"
# -o = "output filename"
# -g = "debug mode"
#
# Note1: if you use a filename other than "makefile", use the
# 	 -f option to enable make to use it:
# 	 e.g.  make -f my_make_file.mak
#
# Note2: .PHONY tells make that the rule's target is not 
#        actually a file (to be created or searched for).
#
# Note3: When make runs without any rules specified on the
#        command line, it will make (by default) the FIRST
#        rule found in the makefile. Hence, it is common
#        to have a rule named "all" listed first (as below).
# 
# ***************************************************************


# -----------------------
# ------ includes -------
# -----------------------



# --------------------------------
# ------ user-defined vars -------
# --------------------------------
CC := gcc
CFLAGS := -g
LINKER_FLAGS := -lm



# -----------------------
# ------ make all -------
# -----------------------
.PHONY : all
all : app

# The "all" rule commonly specifies all executable targets to
# be built. Note, the user has full control over what the "all"
# rule builds. In this solution, we only have one target.
# However, in the final Beagle makefile, you'll see more
# targets listed. 





# -----------------------------------
# ------ executable rule  -----------
# -----------------------------------
#app.o : app.o
	#$(CC) $(CFLAGS) $(LINKER_FLAGS) app.o -o app
	#@echo; echo $@ successfully created; echo


# ---------------------------------------------------
# ------ intermeditate object files rule (.o) -------
# ---------------------------------------------------
app.o : main.c filters.c sensor.c
	$(CC) $(CLFLAGS) $(LINKER_FLAGS) main.c filters.c sensor.c -o app.o




# ----------------------
# ----- clean all ------
# ----------------------
.PHONY : clean
clean :
	rm -rf app
	rm -rf app.o

# The "clean" rule should remove all files created by
# the makefile (e.g. the executables and intermediate
# files).

	


# -------------------------------------
# ----- basic debug for Makefile ------
#
# -----     example only         ------
# -------------------------------------
.PHONY : test
test:
	@echo CC = $(CC)

# We use test to print out the user-defined variables to
# make sure they are set properly - this helps with 
# debugging makefile errors.


	

