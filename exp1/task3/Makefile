objects = test.c
test : $(objects)
	gcc -o test $(objects)

$(objects):emalloc.h

.PHONY : clean
clean :
	rm test
