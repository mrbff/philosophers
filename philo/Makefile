# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 20:40:06 by mabaffo           #+#    #+#              #
#    Updated: 2023/02/11 19:24:08 by mabaffo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo

SRCS_DIR		:=	./srcs/

FILES		:=	main.c \
				check_n_create.c \
				ft_millisec.c \
				ft_patoli.c \
				monitor.c \

SRCS			:=	$(addprefix $(SRCS_DIR), $(FILES))

OBJS			:=	$(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CC				:=	gcc

FLAGS			:=	-Wall -Wextra -Werror -pthread -g

CLR_RMV			:=	\033[0m
RED				:=	\033[1;31m
GREEN			:=	\033[1;32m
YELLOW			:=	\033[1;33m
BLUE			:=	\033[1;34m
CYAN			:=	\033[1;36m

RM				:=	rm -f

$(NAME):	$(OBJS)
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
			@echo "$(GREEN)$(NAME) created 🍝 ${CLR_RMV}"

all:			$(NAME)

clean:
				@ ${RM} *.o */*.o */*/*.o
				@ echo "$(RED)Deleting $(CYAN)objs $(CLR_RMV)🚮"

fclean:			clean
				rm -f $(NAME)
				@ echo "$(RED)Deleting $(CYAN)binaries $(CLR_RMV)🚮"

re:				fclean all

.PHONY:			all clean fclean re
.SILENT:
