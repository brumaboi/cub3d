# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/16 13:45:58 by marvin            #+#    #+#              #
#    Updated: 2025/02/16 13:45:58 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f
AR				=	ar rcs

MLX42_DIR		=	MLX42
MLX42			=	$(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

INC				= 	inc/
SRC_DIR			= 	src/
OBJ_DIR			= 	obj/
	   
SRC 			= $(SRC_DIR)main.c
				  
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(MLX42) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX42) -I $(INC)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(MLX42):
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		clear; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) > /dev/null 2>&1
	@make -C $(MLX42_DIR)/build -j4 > /dev/null 2>&1


clean :
	@$(RM) -f $(OBJ)
	@$(RM) -rf $(OBJ_DIR)

fclean : clean
	@$(RM) $(NAME)
	@$(RM) -rf $(MLX42_DIR)

re : clean fclean all
