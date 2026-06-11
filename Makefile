NAME1 = predict
NAME2 = train
NAME3 = r_squared

VENV = venv
VPYTHON = $(VENV)/bin/python
VPIP    = $(VENV)/bin/pip

SOURCES1 = mandatory/predict.cpp mandatory/utils.cpp
SOURCES2 = mandatory/train.cpp mandatory/utils.cpp
BSOURCES = bonuses/r_squared.cpp mandatory/utils.cpp
OBJ1 = $(SOURCES1:.cpp=.o)
OBJ2 = $(SOURCES2:.cpp=.o)
BOBJ = $(BSOURCES:.cpp=.o)

INCLUDE = includes

CC = c++
CFLAGS = -Wall -Wextra -Werror -g

ITER =

all: $(NAME1) $(NAME2) $(NAME3) $(VENV)/.stamp

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME1) $^

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $^

$(NAME3): $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME3) $^

mandatory/%.o: mandatory/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

bonuses/%.o: bonuses/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@ -I$(INCLUDE)

$(VENV)/.stamp:
	python3 -m venv $(VENV)
	$(VPIP) install matplotlib PyQt5
	touch $(VENV)/.stamp

venv: $(VENV)/.stamp

bonus: plot

plot: all
	echo -e "0\n0" > theta.txt
	./train $(ITER)
	./r_squared
	$(VPYTHON) bonuses/plot.py

clean:
	rm -f $(OBJ1) $(OBJ2) $(BOBJ)

fclean: clean
	rm -f $(NAME1) $(NAME2) $(NAME3)
	rm -rf $(VENV)

re: fclean all

.PHONY: all bonus clean fclean re venv plot