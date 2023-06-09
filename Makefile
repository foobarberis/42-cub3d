# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 21:40:52 by mbarberi          #+#    #+#              #
#    Updated: 2023/06/09 11:48:57 by mbarberi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If necessary we can use $(info VARIABLE:$(VARIABLE)) to debug.
# We can also use make -d.

# Edit the $(NAME) and $(SRCS) variables as necessary.
NAME		:=	cub3D
SRCS		:=	main.c \

CC			:=	gcc
RM			:=	rm

SRCDIR		:=	src
OBJDIR		:=	obj
INCDIR		:=	inc
SYSINC		:=	/usr/include
SYSLIB		:=	/usr/lib
MLXDIR		:=	mlx_linux
LFTDIR		:=	libft

INCFLAGS	:= -I$(INCDIR) -I$(SYSINC) -I$(MLXDIR) -I$(LFTDIR)/inc
LIBFLAGS	:= -L$(MLXDIR) -L$(LFTDIR) -L$(SYSLIB) -lmlx_Linux -lft -lXext -lX11 -lm
# CFLAGS		:=	-Wall -Wextra -Werror -O3 -Ofast -march=native -ffast-math $(INCFLAGS)
CFLAGS		:= -g3 -fPIE -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined,address
LDFLAGS		:=	$(CFLAGS)
RMFLAGS		:=	-f

# Edit the $(HEADERS) variable as necessary.
HEADERS		:=	$(INCDIR)/fdf.h

REMOVE		:=	$(RM) $(RMFLAGS)

SOURCES		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJECTS		:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

all: libft mlx $(NAME)

$(OBJECTS): $(HEADERS) Makefile

$(NAME): $(OBJECTS) $(MLCDIR)/libft.a
	$(CC) $(OBJECTS) $(INCFLAGS) $(LIBFLAGS) -o $(NAME)

libft:
	make -C $(LFTDIR)

mlx:
	make -C $(MLXDIR)

clean:
	$(REMOVE) $(OBJECTS)
	make -C $(MLXDIR) clean
	make -C $(LFTDIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C $(LFTDIR) fclean

re: re: fclean
	$(MAKE) all


.PHONY:	all clean fclean re libft mlx
