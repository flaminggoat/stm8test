CC = sdcc
FLASH = ../stm8flash/stm8flash
CFLAGS	= -mstm8 --std-sdcc11
LDFLAGS = -mstm8 -lstm8 --out-fmt-ihx
B_DIR = build
RM	= rm
 
PROG = main.ihx
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,$(B_DIR)/%.rel,$(SRCS))
LIBS = stm8lib/stm8lib.lib

all: $(PROG)

$(PROG): $(LIBS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(B_DIR)/$(PROG)

$(B_DIR)/%.rel: %.c
	mkdir -p $(B_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

stm8lib/stm8lib.lib: FORCE
	cd stm8lib && make all

flash:
	$(FLASH) -cstlinkv2 -pstm8s103f3 -w $(B_DIR)/$(PROG)

clean:
	$(RM) -rf $(B_DIR)

FORCE:

.PHONY: all flash clean
