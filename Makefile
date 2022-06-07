NAME			= saber.a
CC				= c++
LIB				= ar rc
RM				= rm -f
MKDIR			= mkdir -p
DEBUG			= 0

ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
else
	MAKEFLAGS	= -j --output-sync=recurse --no-print-directory
	DEBUG_FLAGS	= -O2 -flto -D_FORTIFY_SOURCE=2 -fpie
endif

WARNING_FLAGS   = -Wall -Wextra -Werror -Wpointer-arith -Wfloat-equal -fpermissive
PROTECT_FLAGS	= -fno-exceptions -fstack-protector-all
COMMON_FLAGS	= -std=c++98 -MMD -pipe
CFLAGS			= $(COMMON_FLAGS) $(DEBUG_FLAGS) $(PROTECT_FLAGS) $(WARNING_FLAGS)

BIN_DIR			= bin
SRC_DIR			= src
TESTS_DIR		= tests
BUILD_DIR		= build
INC_DIR			= include

SRCS			= src/print_binary.cpp\

OBJS			= $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.cpp=%.o))
NAME			:= $(addprefix $(BIN_DIR)/, $(NAME))
DEPS			= $(OBJS:.o=.d)
VPATH			= $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

TESTS_SRC_DIR = $(TESTS_DIR)/$(SRC_DIR)
TESTS_SRCS = $(shell find $(TESTS_SRC_DIR) -name '*.cpp')
TESTS_BUILD_DIR = $(TESTS_DIR)/$(BUILD_DIR)
TESTS_BIN_DIR = $(TESTS_DIR)/bin
TESTS_BIN_PATH = $(TESTS_BIN_DIR)/test_

TESTS_OBJS := $(subst $(TESTS_SRC_DIR), $(TESTS_BUILD_DIR), $(TESTS_SRCS:%.cpp=%.o))
TESTS_BINS := $(subst $(TESTS_BUILD_DIR)/, $(TESTS_BIN_PATH), $(TESTS_OBJS:%.o=%))

all:			$(NAME)

$(NAME):		$(OBJS)
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(LIB) $(NAME) $(OBJS)
				ranlib $(NAME)

$(BUILD_DIR)/%.o:  $(SRC_DIR)/%.cpp
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

test:			$(TESTS_BINS) $(TESTS_OBJS) $(NAME)
				./$<

test_leaks:		$(TESTS_BINS) $(TESTS_OBJS) $(NAME)
				leaks --atExit -- ./$<

$(TESTS_BUILD_DIR)/%.o: $(TESTS_SRC_DIR)/%.cpp
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(TESTS_BIN_PATH)%:	$(TESTS_BUILD_DIR)/%.o $(OBJS)
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $< $(NAME) -o $@

test_clean:
				$(RM) $(TESTS_OBJS)
				$(RM) -rd $(TESTS_BUILD_DIR)

test_fclean:	test_clean
				$(RM) $(TESTS_BINS)
				$(RM) -rd $(TESTS_BIN_DIR)

clean:			test_clean
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean:			clean test_fclean
				$(RM) -rd $(BUILD_DIR)
				$(RM) $(NAME)

re:
				$(MAKE) fclean
				$(MAKE) all

-include $(DEPS)
.PHONY:			all, clean, fclean, re