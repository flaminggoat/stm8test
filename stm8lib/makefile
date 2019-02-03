CC = sdcc
AR = sdar
CFLAGS	= -mstm8 --std-sdcc11
LDFLAGS = -rc
B_DIR = build
RM	= rm

PROG = stm8lib.lib
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,$(B_DIR)/%.rel,$(SRCS))

all: $(B_DIR) $(PROG)

$(PROG): $(OBJS)
	$(AR) $(LDFLAGS) $(PROG) $(OBJS)

$(B_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(B_DIR)
	$(RM) $(PROG)

$(B_DIR):
	mkdir $(B_DIR)

.PHONY: all clean