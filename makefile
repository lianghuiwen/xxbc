DIR_INC = include
DIR_SRC = src
DIR_LIB = bin
DIR_BIN = bin

CC = g++
ARCR = ar cr
FLAG = -g -Wall
SOFG = -g -Wall -shared -fPIC
INCS = $(foreach dir,$(DIR_INC),-I$(dir))
SRCS = $(foreach dir,$(DIR_SRC),$(wildcard $(dir)/*.cc))
OBJS = $(patsubst %.cc,%.o,$(SRCS))
LIBS = $(foreach dir,$(DIR_LIB),-L$(dir))
TARG = $(DIR_BIN)/libxxbc.a

.PHONY: clean

$(TARG): $(OBJS)
	$(ARCR) $@ $(OBJS) 

%.o: %.cc
	$(CC) $(FLAG) -c $^ $(INCS) -o $@ 

clean:
	-rm -f $(OBJS) $(TARG)

