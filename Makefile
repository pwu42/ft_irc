CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98

NAME		:= ircserv

SRC			:= $(addprefix src/, \
					main.cpp \
				)

INC			:= $(addprefix inc/, \
					ft_irc.hpp \
				)

OBJ		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR	:= ./obj

all: $(NAME)

$(NAME): $(OBJ)

clean:
	@rm -rvf $(OBJ_DIR)/*

fclean: clean
	@rm -rvf $(NAME)

re: fclean
	make all