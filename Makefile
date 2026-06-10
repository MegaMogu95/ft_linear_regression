NAME1 = predict
NAME2 = train
NAME3 = error
SOURCES1 = mandatory/predict/main.cpp
SOURCES2 = mandatory/train/main.cpp
BSOURCES = bonuses/error.cpp
OBJ1 = $(SOURCES1:.cpp=.o)
OBJ2 = $(SOURCES2:.cpp=.o)
BOBJ = $(BSOURCES:.cpp=.o)
INCLUDE = mandatory/includes

CC = c++
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME1) $(NAME2)

bonus: $(NAME3)

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME1) $^

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $^

$(NAME3): $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME3) $^

mandatory/predict/%.o: mandatory/predict/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

mandatory/train/%.o: mandatory/train/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

bonuses/error/%.o: bonuses/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

clean:
	rm -f $(OBJ1) $(OBJ2) $(BOBJ)

fclean: clean
	rm -f $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all bonus clean fclean re