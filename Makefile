CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g
NAME		:= ircserv
NAMEB		:= ircbot
ARG			:= 6666 password

INC			:= -Iinc
SRC			:= $(addprefix src/, \
					$(addprefix class/, \
						Client.cpp \
						Server.cpp \
						SplitMsg.cpp \
					) \
					$(addprefix commands/, \
						kill.cpp \
						mode.cpp \
						nick.cpp \
						oper.cpp \
						pass.cpp \
						ping.cpp \
						pong.cpp \
						privmsg.cpp \
						quit.cpp \
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

SRCB		:= $(addprefix src/, \
					$(addprefix bot/, \
						bot_main.cpp \
						Bot.cpp \
					) \
					$(addprefix class/, \
						SplitMsg.cpp \
					) \
				)

OBJ_DIR	:= ./obj
OBJ		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJB	:= $(SRCB:%.cpp=$(OBJ_DIR)/%.o)
DEP		:= $(OBJ:.o=.d)
DEPB	:= $(OBJB:.o=.d)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -MMD -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

bonus: $(NAMEB)

$(NAMEB): $(OBJB)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $(NAMEB)

-include $(DEP)
-include $(DEPB)

clean:
	@rm -rvf $(OBJ_DIR)

fclean: clean
	@rm -rvf $(NAME)
	@rm -rvf $(NAMEB)

re: fclean
	make all

exe: all
	@./$(NAME) $(ARG)

exeb: bonus
	@./$(NAMEB) $(ARG)

v: all
	@valgrind \
		--leak-check=full \
		--track-origins=yes \
		--track-fds=yes \
		--show-leak-kinds=all \
		--show-reachable=yes \
	./$(NAME) $(ARG)

vb: bonus
	@valgrind \
		--leak-check=full \
		--track-origins=yes \
		--track-fds=yes \
		--show-leak-kinds=all \
		--show-reachable=yes \
	./$(NAMEB) $(ARG)

.PHONY: all clean fclean re exe v bonus exeb vb