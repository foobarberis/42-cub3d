# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 21:40:52 by mbarberi          #+#    #+#              #
#    Updated: 2023/06/14 13:44:01 by mbarberi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If necessary we can use $(info VARIABLE:$(VARIABLE)) to debug.
# We can also use make -d.

# Edit the $(NAME) and $(SRCS) variables as necessary.
NAME		:=	cub3D
SRCS		:=	create.c \
				destroy.c \
				keys.c \
				parsing/parsing.c \
				test.c \
				utils.c \

CC			:=	cc
RM			:=	rm

SRCDIR		:=	src
OBJDIR		:=	obj
INCDIR		:=	inc
SYSINC		:=	/usr/include
SYSLIB		:=	/usr/lib
MLXDIR		:=	mlx_linux
MLCDIR		:=	mlc

INCFLAGS	:= -I$(INCDIR) -I$(SYSINC) -I$(MLXDIR) -I$(MLCDIR)/inc
# Was -lmlx_Linux
LIBFLAGS	:= -L$(MLXDIR) -L$(MLCDIR) -L$(SYSLIB) -lmlx -lft -lXext -lX11 -lm
# CFLAGS		:=	-Wall -Wextra -Werror -O3 -Ofast -march=native -ffast-math $(INCFLAGS)
CFLAGS		:= -g3 -fPIE -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined,address
RMFLAGS		:=	-f

# Edit the $(HEADERS) variable as necessary.
HEADERS		:=	$(INCDIR)/cub3d.h

REMOVE		:=	$(RM) $(RMFLAGS)

SOURCES		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJECTS		:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

all: libft mlx $(NAME)

$(OBJECTS): $(HEADERS) Makefile

$(NAME): $(OBJECTS) $(MLCDIR)/libft.a $(MLXDIR)/libmlx.a
	$(CC) $(OBJECTS) -fsanitize=address,undefined $(LIBFLAGS) -o $(NAME)

libft:
	make -C $(MLCDIR)

mlx:
	make -C $(MLXDIR)

clean:
	$(REMOVE) $(OBJECTS)
	make -C $(MLXDIR) clean
	make -C $(MLCDIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C $(MLCDIR) fclean
	make -C $(MLXDIR) clean

re: fclean
	$(MAKE) all

.PHONY:	all clean fclean re libft mlx
