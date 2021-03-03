NAME = ft_slae
SRCS = ./srcs/main.cpp ./srcs/FPI.cpp ./srcs/Seidel.cpp
INCLUDE = ./includes/FPI.hpp ./includes/Seidel.hpp
OBJ = $(SRCS:.cpp=.o)
CC = clang++
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

%.o: %.cpp $(INCLUDE)
	$(CC) $(FLAGS) -c $<

$(NAME): $(OBJ)
	mv *.o ./srcs/
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

.PHONY: all clean fclean re
