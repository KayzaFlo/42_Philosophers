# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 13:26:56 by fgeslin           #+#    #+#              #
#    Updated: 2023/04/24 13:36:30 by fgeslin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####	CONFIG		############################################################
NAME		:= philosophers
CC			:= gcc
AR			:= ar -rcs
RM			:= rm -f
CFLAGS		= -Wall -Wextra -Werror

#####	SOURCES		############################################################
SRC			=	src/philosophers.c \
				src/parsing.c \
				src/thread_setup.c \
				src/thread_routine.c \
				src/utils_time.c \
				src/utils_print.c \
				src/utils_str.c
OBJ			=	$(SRC:.c=.o)

#####	Makefile  objs		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m

.c.o:
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

# ------ #

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}$(NAME) ${WHITE}..."
	@ $(CC) -o $(NAME) $(OBJ) -lm
	@ echo "$(CYAN)$(NAME) $(GREEN)created$(WHITE) ✔️"

# ------ #

debug: $(OBJ)
	@ echo "$(GREEN)Debug Compil ${WHITE}of ${CYAN}$(NAME) ${WHITE}..."
	@ $(CC) -fsanitize=thread -o $(NAME) $(OBJ) -lm
	@ echo "$(CYAN)$(NAME) $(GREEN)created$(WHITE) ✔️"

# ------ #

clean:
	@ ${RM} $(OBJ) $(OBJ_BONUS)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE)objs ✔️"

fclean: clean
	@ ${RM} $(NAME)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE)binary ✔️"

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus
