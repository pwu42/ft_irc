CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g
NAME		:= ircserv
ARG			:= 6666 password

INC			:= -Iinc
SRC			:= $(addprefix src/, \
					$(addprefix class/, \
						Client.cpp \
						Server.cpp \
						SplitMsg.cpp \
						Channel.cpp \
					) \
					$(addprefix commands/, \
						join.cpp \
						kill.cpp \
						names.cpp \
						mode.cpp \
						nick.cpp \
						oper.cpp \
						part.cpp \
						pass.cpp \
						ping.cpp \
						pong.cpp \
						privmsg.cpp \
						quit.cpp \
						topic.cpp \
						user.cpp \
					) \
					$(addprefix server/, \
						init.cpp \
						client_connection.cpp \
						reply.cpp \
					) \
					$(addprefix utils/, \
						find_client.cpp \
					) \
					main.cpp \
				)

OBJ_DIR	:= ./obj
OBJ		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEP		:= $(OBJ:.o=.d)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -MMD -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

-include $(DEP)

clean:
	@rm -rvf $(OBJ_DIR)

fclean: clean
	@rm -rvf $(NAME)

re: fclean
	make all

exe: all
	@./$(NAME) $(ARG)

v: all
	@valgrind \
		--leak-check=full \
		--track-origins=yes \
		--track-fds=yes \
		--show-leak-kinds=all \
		--show-reachable=yes \
	./$(NAME) $(ARG)

.PHONY: all clean fclean re exe v
