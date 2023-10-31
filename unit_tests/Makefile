# Single tests can be run with using make and the specific name
####################################################################
#>>>>>>>>>>>>>>>>>>>>>>>>>> Basic Setup <<<<<<<<<<<<<<<<<<<<<<<<<<<#
####################################################################
.DEFAULT_GOAL := all
CC := cc

M := \033[35m
RST := \033[0m
LOG := printf "[$(M)INFO$(RST)] %s\n"

TESTS := vector

# define include dirs and search paths
INC_DIRS := -I.
VPATH := ../
OBJ_DIR := ./_obj

# define compiler and linker flags
CFLAGS_TEST := -g
CFLAGS := $(CFLAGS_TEST) -MMD -MP
#TEST_FLAG := -Wno-error=unused-command-line-argument
# LDFLAGS := -L $(LIBFT_DIR) -lft -lreadline -lcriterion # -Wno-write-strings -fpermissive
LDFLAGS := -lcriterion
# define a variable to run the tests
define run
	$(CC) $^ $(INC_DIRS) $(LDFLAGS) -o $@ && ./$@ --verbose
endef

####################################################################
#>>>>>>>>>>>>>>>>>>>>>>>> Individual Setup <<<<<<<<<<<<<<<<<<<<<<<<#
####################################################################

# Source files for vec3d
SRC_VEC := vec3d_math.c
OBJ_VEC := $(addprefix $(OBJ_DIR)/, $(SRC_VEC:%.c=%.o))

####################################################################
#>>>>>>>>>>>>>>>>> Here is the start of the tests <<<<<<<<<<<<<<<<<#
####################################################################

all: $(TESTS)

# $(LIBFT):
# 	@$(MAKE) -C ../libft -B --no-print-directory

# Test cases for the lexer
.PHONY: vector
vector: $(OBJ_VEC) vec_test.c
	@$(call run, "$^")

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	@$(CC) -c $< $(CFLAGS_TEST) $(INC_DIRS) -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(LOG) "Removing object files"

fclean: clean
	@$(RM) $(TESTS)
	@$(LOG) "Removing executables"

-include $(OBJS:%.o=%.d)
