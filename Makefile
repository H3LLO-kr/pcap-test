NAME	= pcap-test
CC		= gcc
CFLAGS	= -lpcap
RM		= rm -rf
SRCS	= pcap-test.c \
		  _print.c
OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	$(RM) $(NAME)
	$(RM) $(OBJS)


.PHONY: all clean

