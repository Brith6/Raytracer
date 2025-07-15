##
## EPITECH PROJECT, 2024
## B-OOP-400-COT-4-1-raytracer-vanessa.bokove
## File description:
## Makefile
##

NAME	=	raytracer

CC		=	g++ -g3
RM		=	rm -rf

CORE_SRC				= $(shell find new_repo -type f -name "*.cpp")
POINTLIGHT_SRC 			= $(shell find new_repo/lights/pointLight -type f -name "*.cpp")
DIRECTIONALLIGHT_SRC	= $(shell find new_repo/lights/directionalLight -type f -name "*.cpp")
SPHERE_SRC 				= $(shell find new_repo/primitives/sphere -type f -name "*.cpp")
PLANE_SRC 				= $(shell find new_repo/primitives/plane -type f -name "*.cpp")


CORE_OBJ				= $(CORE_SRC:.cpp=.o)
POINTLIGHT_OBJ 			= $(POINTLIGHT_SRC:.cpp=.o)
DIRECTIONALLIGHT_OBJ	= $(DIRECTIONALLIGHT_SRC:.cpp=.o)
SPHERE_OBJ 				= $(SPHERE_SRC:.cpp=.o)
PLANE_OBJ 				= $(PLANE_SRC:.cpp=.o)

FLAGS	= 	-std=c++20 -Wall -Wextra -Werror

$(NAME):	core lights primitives

core:	$(CORE_OBJ)
	@$(CC) -o $(NAME) $(CORE_OBJ) -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system

lights:	$(POINTLIGHT_OBJ) $(DIRECTIONALLIGHT_OBJ)
	@$(CC) -shared -fPIC -o new_repo/plugins/point_light.so $(POINTLIGHT_OBJ)
	@$(CC) -shared -fPIC -o new_repo/plugins/directional_light.so $(DIRECTIONALLIGHT_OBJ)

primitives:	$(SPHERE_OBJ) $(PLANE_OBJ)
	@$(CC) -shared -fPIC -o new_repo/plugins/sphere.so $(SPHERE_OBJ)
	@$(CC) -shared -fPIC -o new_repo/plugins/plane.so $(PLANE_OBJ)

%.o: %.cpp
	@$(CC) -c $< -o $@ -fPIC $(FLAGS)

all:	$(NAME)

clean:
	@$(RM) $(CORE_OBJ) $(POINTLIGHT_OBJ) $(DIRECTIONALLIGHT_OBJ) $(SPHERE_OBJ) $(PLANE_OBJ) $(LIGHTS_OBJ) $(PRIMITIVES_OBJ)
	@find . -name "*~" -delete -o -name "#*#" -delete
	@$(RM) vgcore.*
	@$(RM) a.out
	@find . -name "*.gc*" -delete

fclean:	clean
	@$(RM) $(NAME) plugins/*.so

re:	fclean all
