# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/10/22 18:02:12 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

INC_FILES = includes/wolf.h

INC = includes/

SRC_DIR = srcs/

SRC = main.c \
event/event_key_on.c \
event/event_key_off.c \
event/event_fire.c \
event/event_red_cross.c \
update/loop.c \
update/update_key_event.c \
update/update_sprite_position.c \
update/update_fps.c \
raycast_aff/raycast_aff_view_2d.c \
raycast_aff/raycast_aff_floor.c \
raycast_aff/raycast_aff_sky.c \
raycast_aff/raycast_aff_basic.c \
raycast_aff/raycast_aff_tex.c \
raycast_aff/raycast_aff.c \
sprite/sprite.c \
sprite/sprite_hit.c \
raycast.c \
raycast_wolf.c \
free.c \
radar.c \
move.c \
tools.c \
init_var.c \
init_map.c \
import_texture.c \
fvector2d/fvector2d_magnitude.c \
fvector2d/fvector2d_distance.c \
fvector2d/fvector2d_normalize.c \
fvector2d/fvector2d_normalized.c \
fvector2d/fvector2d_aequals.c \
fvector2d/fvector2d_limit.c \
fvector2d/fvector2d_construct.c \
fvector2d/fvector2d_rotation.c \
end_of_program.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)

#SDL_FLAGS = -I SDL2-2.0.5/include SDL2-2.0.5/build/.libs/libSDL2.a -framework Cocoa -framework CoreAudio -framework AudioToolbox -framework ForceFeedback -framework CoreVideo -framework Carbon -framework IOKit -liconv

DIR_LFT = libft/

DIR_MLXJI = libmlxji/

DIR_MLX = minilibx_macos/

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl
#FRAMEWORK = -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext -lm

DIR_LIB = libs/

#.PHONY de $(NAME) = Pas de message, car Verification
.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) lib $(addprefix $(OBJ_DIR), $(OBJET))
	@$(CC) -I $(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) -lft -lmlxji -lmlx $(FRAMEWORK) -o $(NAME)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
	@(cd $(DIR_MLXJI) && $(MAKE))
	@(cd $(DIR_MLX) && $(MAKE))
	@(cp $(DIR_MLX)libmlx.a $(DIR_LIB))
	@(cp $(DIR_MLXJI)libmlxji.a $(DIR_LIB))
	@(cp $(DIR_LFT)libft.a $(DIR_LIB))

$(OBJ_DIR) :
	@mkdir $(DIR_LIB)
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)$(SRC_DIR)
	@mkdir $(OBJ_DIR)/fvector2d
	@mkdir $(OBJ_DIR)/event
	@mkdir $(OBJ_DIR)/update
	@mkdir $(OBJ_DIR)/raycast_aff
	@mkdir $(OBJ_DIR)/sprite

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	$(CC) $(CFLAGS) -I ./$(INC) -o $@ -c $<

clean:
	@echo "Clean wolf3d"
	@(cd $(DIR_LFT) && $(MAKE) clean)
	@(cd $(DIR_MLXJI) && $(MAKE) clean)
	@(cd $(DIR_MLX) && $(MAKE) clean)
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -rf $(DIR_LIB)

fclean:
	@echo "fClean wolf3d"
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && $(MAKE) fclean)
	@(cd $(DIR_MLXJI) && $(MAKE) fclean)
	@/bin/rm -rf $(DIR_LIB)
	@/bin/rm -f $(NAME)

re: fclean all
