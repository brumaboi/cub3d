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
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -f
AR				=	ar rcs

MLX42_DIR		=	MLX42
MLX42			=	$(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT_PATH		= 	libft
LIBFT			= 	libft.a

INC				= 	inc/
SRC_DIR			= 	src/
OBJ_DIR			= 	obj/
	   
SRC 			= $(SRC_DIR)main.c \
				  $(SRC_DIR)check_input.c \
				  $(SRC_DIR)raycasting.c \
				  $(SRC_DIR)raycast_utils.c \
				  $(SRC_DIR)map/1_check_map.c \
				  $(SRC_DIR)map/2_parser.c \
				  $(SRC_DIR)map/3_config.c \
				  $(SRC_DIR)map/4_validation/1_validate_map.c \
				  $(SRC_DIR)map/4_validation/2_map_elements.c \
				  $(SRC_DIR)map/4_validation/3_surroundings.c \
				  $(SRC_DIR)map/4_validation/4_player_mobility.c \
				  $(SRC_DIR)game/1_init_game.c \
				  $(SRC_DIR)game/2_init_player.c
				  
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(MLX42) $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)/$(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_PATH)/$(LIBFT) $(MLX42) -I $(INC)

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

$(LIBFT_PATH)/$(LIBFT) : 
	@make -C $(LIBFT_PATH) > /dev/null 2>&1

clean :
	@$(RM) -f $(OBJ)
	@$(RM) -rf $(OBJ_DIR)
	@make -C $(LIBFT_PATH) clean > /dev/null 2>&1

fclean : clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean > /dev/null 2>&1

re : clean fclean all
