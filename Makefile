NAME := miniRT
.DEFAULT_GOAL := multi
CC := cc

################################################################################
###############                 PRINT OPTIONS                     ##############
################################################################################

G := \033[32m
M := \033[35m
X := \033[0m
BO := $(shell tput bold)
LOG := printf "[$(BO)$(G)ⓘ INFO$(X)] %s\n"
WARN := printf "[$(BO)$(M)ⓘ WARN$(X)] %s\n"

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
LIBFT_DIR := libft
MLX_DIR := MLX42

INC_DIRS := include $(LIBFT_DIR)/include $(MLX_DIR)/include/MLX42

vpath %.h $(INC_DIRS)
# vpath %.c $(SRC_DIRS)

LIBFT := $(LIBFT_DIR)/libft.a
MLX42 := $(MLX_DIR)/build/libmlx42.a

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS := main.c utils.c
SRCS += hit_core.c hit_cylinder.c hit_plane.c hit_sphere.c
SRCS += parser_core.c parser_copy.c parser_obj_hittable.c
SRCS += parser_obj_scene.c parser_strtod.c parser_utils.c
SRCS += color_core.c color_utils.c camera_utils.c init.c ray.c
SRCS += vec3d_core.c vec3d_products.c vec3d_utils.c
SRCS += render_core.c render_utils.c hit_cone.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

CFLAGS ?= -Wextra -Wall -Werror -Ofast -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -L $(MLX_DIR)/build -lmlx42
LDFLAGS += -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	@$(LOG) "Linking object files to $@"
	@$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(LOG) "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating object directory."
	@mkdir -p $@

# add any submodule here
# check if submodule needs to be initialized
submodules:
	@if git submodule status | egrep -q '^[-+]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
		git submodule update --init; \
	fi

$(LIBFT):
	@+make -C $(LIBFT_DIR) -B --no-print-directory

$(MLX42):
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j16

debug: CFLAGS += -g
debug: fclean all

clean:
	@$(MAKE) -C ./libft/ clean --no-print-directory
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(WARN) "Cleaning $(notdir $(OBJ_DIR))"; \
		rm -rf $(OBJ_DIR); \
	else \
		$(LOG) "No objects to clean."; \
	fi

fclean: clean
	@$(MAKE) -C ./libft/ fclean --no-print-directory
	@if [ -f "$(NAME)" ]; then \
		$(WARN) "Cleaning $(notdir $(NAME))"; \
		rm -f $(NAME); \
	else \
		$(LOG) "No binary to clean."; \
	fi
	@rm -rf $(MLX_DIR)/build

re: fclean multi

-include $(OBJS:$(OBJ_DIR)/%.o=$(OBJ_DIR)/%.d)

.PHONY: all fclean clean re submodules multi

multi: submodules
	@$(MAKE) -j16 all
