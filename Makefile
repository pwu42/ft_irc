CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g
NAME		:= ircserv

INC			:= -Iinc
SRC			:= $(addprefix src/, \
					main.cpp \
					Server.cpp \
				)

OBJ_DIR	:= ./obj
OBJ		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEP		:= $(OBJ:.o=.d)

all: $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -MMD -o $@

$(NAME): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

-include $(DEP)

clean:
	@rm -rvf $(OBJ_DIR)/*

fclean: clean
	@rm -rvf $(NAME)

re: fclean
	make all

v: all
	@valgrind \
		--leak-check=full \
		--track-origins=yes \
		--track-fds=yes \
		--show-leak-kinds=all \
		--show-reachable=yes \
	./$(NAME) 6666 a

.PHONY: all clean fclean re