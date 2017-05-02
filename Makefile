PROG_NAME	= 42sh

COMPILER	= clang -c
CFLAGS 		= -Wall -Wextra -Werror -g -I$(INCL_ROOT) -I./libft/includes/

LINKER 		= clang
LFLAGS		= -L./libft/ -lft -lncurses

SDEC		= .
CPUIDLE		= 0
BOGOMIPS	= 0
NBTHREADS	= 2
ESTIMATED 	= 0
ifeq ($(shell uname), Linux)
SDEC		= $(shell locale -k LC_NUMERIC | grep decimal_point | grep -o '=".' | cut -d '"' -f 2)
CPUIDLE		= $(shell top -bn 2 -d "0$(SDEC)1" | grep Cpu | tail -n 1 | grep -o '......id' | cut -d '$(SDEC)' -f 1)
BOGOMIPS	= `cat /proc/cpuinfo | grep bogomips | head -n 1 | cut -d ' ' -f 2 | cut -d '.' -f 1`
NBTHREADS	= `cat /proc/cpuinfo | grep processor | wc -l`
ESTIMATED	= $(shell echo "scale=2;($(BOGOMIPS_BASE)*$(COMPILATION_TIME)/$(BOGOMIPS)/($(CPUIDLE)/100))" | bc -l)
endif

$(eval BOGOMIPS=$(shell echo $$(($(BOGOMIPS) * $(NBTHREADS)))))
$(eval NBTHREADS=$(shell echo $$(($(NBTHREADS)*2))))

BOGOMIPS_BASE	= 40000
CPUIDLE			= $(shell top -bn 2 -d "0$(SDEC)1" | grep Cpu | tail -n 1 | grep -o '......id' | cut -d '$(SDEC)' -f 1)
ESTIMATED		= $(shell echo "scale=2;($(BOGOMIPS_BASE)*$(COMPILATION_TIME)/$(BOGOMIPS)/($(CPUIDLE)/100))" | bc -l)

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

travis:
	@$(eval COMPILATION_TIME=15)
	@echo "Begin compilation $(PROG_NAME) + Test with $(NBTHREADS) thread"
	@echo "Cpu $(BOGOMIPS) mips, idle $(CPUIDLE)%"
	@echo "Estimated time $(ESTIMATED) sec"
	@make prog $(MAKE_OPTS)
	@make test $(MAKE_OPTS)
	@make testsh $(MAKE_OPTS)

all:
	@$(eval COMPILATION_TIME=2.7)
	@echo "Begin compilation $(PROG_NAME) with $(NBTHREADS) thread"
	@echo "Cpu $(BOGOMIPS) mips, idle $(CPUIDLE)%"
	@echo "Estimated time $(ESTIMATED) sec"
	@make prog $(MAKE_OPTS)

prog:
	@make -C ./libft $(MAKE_OPTS)
	@$(MAKE) $(PROG_NAME) $(MAKE_OPTS) $(MAKE_OPTS_THREAD)

test:
	@make re -C ./tests $(MAKE_OPTS) $(MAKE_OPTS_THREAD)

testsh:
	@gcc -o segv testcomp/testsegv.c
	@./test detail

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

.PHONY: all clean fclean re test testsh travis prog
