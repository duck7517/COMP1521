EXERCISES	  += chicken
CLEAN_FILES	+= chicken
CLEAN_FILES	+= chicken.o
CLEAN_FILES	+= chicken_main.o
CLEAN_FILES	+= chicken_hash.o
CLEAN_FILES	+= chicken_6_bit.o

chicken:	chicken.o chicken_main.o chicken_hash.o chicken_6_bit.o

chicken.o:	chicken.c chicken.h
chicken_main.o: chicken_main.c chicken.h
chicken_hash.o:	chicken_hash.c chicken.h
chicken_6_bit.o:	chicken_6_bit.c chicken.h


#
# To add another `.c' file to your assignment:
#
#  - add the corresponding `.o' file to the `chicken:' line, and
#  - add a CLEAN_FILES line for the corresponding `.o' file.
#
# For example, to add `egg_on_face.c', you might add::
#
#     CLEAN_FILES	+= egg_on_face.o
#
# and change the `chicken:' line to have::
#
#     chicken:	chicken.o chicken_args.o egglet_hash.o egg_on_face.o
#
# You should (but do not need to) list any header files that your new
# `.c' file includes, so that, if those files are changed. your file is
# recompiled.
#
# For example, if `egg_on_face.c' only includes `egg.h', you might add::
#
#     egg_on_face.o:	egg_on_face.c egg.h
#
