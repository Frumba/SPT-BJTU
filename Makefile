NAME		= fps-shell
SRCS		= $(SRCS_DIR)/main.cpp		\
		  $(SRCS_DIR)/FPSShell.cpp
SRCS_DIR	= srcs
OBJS		= $(SRCS:.cpp=.o)
CXXFLAGS	+= -W -Wall -Werror -Iincludes
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