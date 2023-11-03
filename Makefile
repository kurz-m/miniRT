NAME := miniRT
.DEFAULT_GOAL := all
CC := cc

################################################################################
###############                 PRINT OPTIONS                     ##############
################################################################################

G := \033[32m
X := \033[0m
BO := $(shell tput bold)
LOG := printf "[$(BO)$(G)ⓘ INFO$(X)] %s\n"

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
LIBFT_DIR := libft
MLX_DIR := MLX42

INC_DIRS := include $(LIBFT_DIR)/include $(MLX_DIR)/include/MLX42
# SRC_DIRS := <all source dirs>

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
# vpath %.c $(SRC_DIRS)

LIBFT := $(LIBFT_DIR)/libft.a
MLX42 := $(MLX_DIR)/build/libmlx42.a

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS := ft_strtod.c helpers.c main.c parse_obj1.c parse_obj2.c parser.c
SRCS += vec3d_math.c mrt_colors.c camera_utils.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

CFLAGS := -g $(addprefix -I, $(INC_DIRS))
# CFLAGS ?= -Wextra -Wall -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -L $(MLX_DIR)/build -lmlx42
LDFLAGS += -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OBJS) | $(LIBFT) $(MLX42)
	@$(LOG) "Linking object files to $@"
	@$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(LIBFT) $(MLX42)
	@$(LOG) "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating object directory."
	@mkdir -p $@

# add any submodule here
$(LIBFT):
	@git submodule update --init --recursive
	@make -C $(LIBFT_DIR) -B --no-print-directory

$(MLX42):
	@git submodule update --init --recursive
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

debug: CFLAGS += -g
debug: fclean all

clean:
	@$(MAKE) -C ./libft/ clean --no-print-directory
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(LOG) "Cleaning $(notdir $(OBJ_DIR))"; \
		rm -rf $(OBJ_DIR); \
	else \
		$(LOG) "No objects to clean."; \
	fi

fclean: clean
	@$(MAKE) -C ./libft/ fclean --no-print-directory
	@if [ -f "$(NAME)" ]; then \
		$(LOG) "Cleaning $(notdir $(NAME))"; \
		rm -f $(NAME); \
	else \
		$(LOG) "No library to clean."; \
	fi
	@rm -rf $(MLX_DIR)/build

re: fclean all

-include $(OBJS:%.o=%.d)

.PHONY: all fclean clean re
