NAME1 = predict
NAME2 = train
SOURCES1 = predict/main.cpp
SOURCES2 = train/main.cpp
BSOURCES = 
OBJ1 = $(SOURCES1:.cpp=.o)
BOBJECTS = $(BSOURCES:.cpp=.o)
INCLUDE = mandatory
BINCLUDE = bonus

CC = c++
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME) $^

bonus: $(BOBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE) -I$(BINCLUDE)

clean:
	rm -f $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re