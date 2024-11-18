#*************************************************************************************#
#                                       MINITALK                                      #
#*************************************************************************************#

# Paths and Compiler Options
PRINTF = ft_printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Targets
all: client server

client: client.o ft_atoi.o $(PRINTF)
	@$(CC) $(CFLAGS) -o client client.o ft_atoi.o $(PRINTF)

server: server.o $(PRINTF)
	@$(CC) $(CFLAGS) -o server server.o $(PRINTF)

client.o: client.c ft_atoi.c
	@$(CC) $(CFLAGS) -c client.c

ft_atoi.o: ft_atoi.c
	@$(CC) $(CFLAGS) -c ft_atoi.c

server.o: server.c
	@$(CC) $(CFLAGS) -c server.c

# Compile the printf library if it doesn’t exist or is out-of-date
$(PRINTF):
	@make -C $(dir $(PRINTF))

# Clean and Rebuild
clean:
	@rm -f client.o server.o ft_atoi.o
	@make -C $(dir $(PRINTF)) clean

fclean: clean
	@rm -f client server 
	@make -C $(dir $(PRINTF)) fclean

re: fclean all

.PHONY: all clean fclean re



