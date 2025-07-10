##
## EPITECH PROJECT, 2025
## B-OOP-400-COT-4-1-raytracer-vanessa.bokove
## File description:
## Makefile pour les implémentations d'Emmanuela
##

NAME	=	test_emma

CC		=	g++ -g3
RM		=	rm -rf

# Sources
CORE_SRC		= core/helpers/Color.cpp
LIGHTS_SRC		= lights/directionalLight/DirectionalLight.cpp
PRIMITIVES_SRC	= primitives/plane/Plane.cpp
DESIGN_SRC		= core/designPatterns/Factory.cpp
TEST_SRC		= test_emma.cpp

# Objects
CORE_OBJ		= $(CORE_SRC:.cpp=.o)
LIGHTS_OBJ		= $(LIGHTS_SRC:.cpp=.o)
PRIMITIVES_OBJ	= $(PRIMITIVES_SRC:.cpp=.o)
DESIGN_OBJ		= $(DESIGN_SRC:.cpp=.o)
TEST_OBJ		= $(TEST_SRC:.cpp=.o)

FLAGS	= 	-std=c++20 -Wall -Wextra -Werror

$(NAME):	$(CORE_OBJ) $(LIGHTS_OBJ) $(PRIMITIVES_OBJ) $(DESIGN_OBJ) $(TEST_OBJ)
	@$(CC) -o $(NAME) $(CORE_OBJ) $(LIGHTS_OBJ) $(PRIMITIVES_OBJ) $(DESIGN_OBJ) $(TEST_OBJ) $(FLAGS)

%.o: %.cpp
	@$(CC) -c $< -o $@ $(FLAGS)

all:	$(NAME)

clean:
	@$(RM) $(CORE_OBJ) $(LIGHTS_OBJ) $(PRIMITIVES_OBJ) $(DESIGN_OBJ) $(TEST_OBJ)
	@find . -name "*~" -delete -o -name "#*#" -delete
	@$(RM) vgcore.*
	@$(RM) a.out
	@find . -name "*.gc*" -delete

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

test:	$(NAME)
	@echo "=== Lancement des tests ==="
	@./$(NAME)

.PHONY: all clean fclean re test 