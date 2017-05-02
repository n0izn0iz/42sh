PROG_NAME	= 42sh

COMPILER	= clang -c
CFLAGS 		= -Wall -Wextra -Werror -g -I$(INCL_ROOT) -I./libft/includes/

LINKER 		= clang
LFLAGS		= -L./libft/ -lft -lncurses

ifeq ($(shell uname), Linux)
NBTHREADS	=`cat /proc/cpuinfo | grep processor | wc -l`
else ifeq ($(shell uname), Darwin)
NBTHREADS	=`sysctl -a | grep hw.logicalcpu: | cut -d ' ' -f 2`
else
NBTHREADS	= 1
endif
$(eval NBTHREADS=$(shell echo $$(($(NBTHREADS)*2))))

SRCS_ROOT = srcs
INCL_ROOT = includes
OBJS_ROOT = objs

SRCS_DIRS = $(shell find $(SRCS_ROOT) -type d)
OBJS_DIRS = $(patsubst $(SRCS_ROOT)%, $(OBJS_ROOT)%, $(SRCS_DIRS))

SRCS = $(filter %.c,$(shell find $(SRCS_ROOT) -type f))
OBJS = $(patsubst $(SRCS_ROOT)/%.c, $(OBJS_ROOT)/%.o, $(SRCS))

HEADERS = $(filter %.h,$(shell find $(INCL_ROOT) -type f))

MAKE_OPTS 			= --no-print-directory
MAKE_OPTS_THREAD 	= -j$(NBTHREADS)

all:
	@echo "Begin compilation with $(NBTHREADS) thread"
	@make -C ./libft $(MAKE_OPTS)
	@$(MAKE) $(PROG_NAME) $(MAKE_OPTS) $(MAKE_OPTS_THREAD)

test:
	@make re -C ./tests $(MAKE_OPTS) $(MAKE_OPTS_THREAD)

testsh:
	@gcc -o segv testcomp/testsegv.c
	@./test detail bonus allsh

$(PROG_NAME): $(OBJS_DIRS) $(OBJS)
	@echo "LINK   " $@
	@$(LINKER) -o $@ $(OBJS) $(LFLAGS)

$(OBJS_DIRS):
	@mkdir -p $@

$(OBJS_ROOT)/%.o: $(SRCS_ROOT)/%.c $(HEADERS)
	@echo "COMPILE" $(patsubst $(SRCS_ROOT)/%.c,%,$<)
	@$(COMPILER) -o $@ $(CFLAGS) -I$(dir $(patsubst $(SRCS_ROOT)%,$(INCL_ROOT)%,$<)) $<

clean:
	@make -C ./libft clean $(MAKE_OPTS)
	@make -C ./tests clean $(MAKE_OPTS)
	@rm -fr $(OBJS_ROOT)

fclean: clean
	@make -C ./libft fclean $(MAKE_OPTS)
	@make -C ./tests fclean $(MAKE_OPTS)
	@rm -f $(PROG_NAME)

re: fclean all

.PHONY: all clean fclean re test testsh
