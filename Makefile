# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgelu <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/15 17:56:01 by tgelu             #+#    #+#              #
#    Updated: 2018/09/05 14:21:32 by tgelu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

CPP_FLAGS = -Iinclude

NAME = lem-in

SRC_PATH = ./srcs
LIB_PATH = ./lib
INC_PATH = ./includes
OBJ_PATH = ./obj

SRC_NAME = main.c \
		   parser.c \
		   parser_room.c \
		   parser_tubes.c \
		   ants.c \
		   room_utils.c \
		   get_next_line.c \
		   utils.c \
		   print.c 

INC_NAME = lem_in.h
LIB_NAME = libftprintf.a
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC= $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH)/, $(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_PATH) -I$(LIB_PATH)

clean:
	@make -C $(LIB_PATH) clean 
	@rm -rf $(OBJ) $(OBJLIB) $(OBJ_PATH)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -rf $(NAME)

re: fclean all
