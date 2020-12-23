CFLAGS   = -c -Wall -Werror
COMPILE  = gcc
RM       = rm -f
OBJ      = 90-02-b4-qq_rec_parsed
SOURCE   = 90-02-b4-qq_rec_parsed.o ../common/common_mybase_tool.o

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ)

$(SOURCE): %.o: %.c
	$(COMPILE) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.bak $(SOURCE) $(OBJ)
	touch *.*
