NAME	= pcap-test
CC		= gcc
CFLAGS	= -lpcap
RM		= rm -rf
SRCS	= pcap-test.c \
		  _print.c
OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)

%.o : %.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	$(RM) $(NAME)
	$(RM) $(OBJS)


.PHONY: all clean

