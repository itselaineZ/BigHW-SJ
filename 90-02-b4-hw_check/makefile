CFLAGS   = -c -Wall -Werror
COMPILE  = gcc
RM       = rm -f
OBJ      = 90-02-b4-hw_check
SOURCE   = 90-02-b4-hw_check.o ../common/common_mybase_tool.o

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ)

$(SOURCE): %.o: %.c
	$(COMPILE) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.bak $(SOURCE) $(OBJ)
	touch *.*
