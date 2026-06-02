NAME1 = predict
NAME2 = train
SOURCES1 = mandatory/predict/main.cpp
SOURCES2 = mandatory/train/main.cpp
BSOURCES = 
OBJ1 = $(SOURCES1:.cpp=.o)
OBJ2 = $(SOURCES2:.cpp=.o)
INCLUDE = mandatory/includes

CC = c++
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME1) $^

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $^


mandatory/predict/%.o: mandatory/predict/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

mandatory/train/%.o: mandatory/train/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

clean:
	rm -f $(OBJ1) $(OBJ2)

fclean: clean
	rm -f $(NAME1) $(NAME2)

re: fclean all

.PHONY: all bonus clean fclean re