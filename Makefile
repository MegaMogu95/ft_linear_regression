NAME1 = predict
NAME2 = train
NAME3 = r_squared
SOURCES1 = mandatory/predict.cpp
SOURCES2 = mandatory/train.cpp
BSOURCES = bonuses/r_squared.cpp
OBJ1 = $(SOURCES1:.cpp=.o)
OBJ2 = $(SOURCES2:.cpp=.o)
BOBJ = $(BSOURCES:.cpp=.o)
INCLUDE = includes

CC = c++
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME1) $(NAME2) $(NAME3)

bonus: $(NAME3)

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME1) $^

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $^

$(NAME3): $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME3) $^

mandatory/%.o: mandatory/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

bonuses/error/%.o: bonuses/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

clean:
	rm -f $(OBJ1) $(OBJ2) $(BOBJ)

fclean: clean
	rm -f $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all bonus clean fclean re