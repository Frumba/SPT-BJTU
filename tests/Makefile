NAME		= fps-shell
SRCS		= $(SRCS_DIR)/test-shell-command.cpp		\
		  $(SRCS_DIR)/ShellCommands.cpp
SRCS_DIR	= ../srcs
OBJS		= $(SRCS:.cpp=.o)
CXXFLAGS	+= -W -Wall -Werror -I../includes
CXX		= g++

all		: $(NAME)

$(NAME)		: $(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(LDXXFLAGS)

clean		:
		rm -rf $(OBJS)
		rm -rf *~

fclean		: clean
		rm -rf $(NAME)

re		: fclean all