# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoizel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 09:30:09 by aoizel            #+#    #+#              #
#    Updated: 2023/11/22 15:46:37 by aoizel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	libftprintf.a

LIBFT 			=	libft/libft.a

LIBFT_DIR 		=	libft/

CFLAGS 			=	-Wall -Wextra -Werror

CC 				=	cc $(CFLAGS)

SOURCES 		=	ft_printc.c ft_printf.c ft_prints.c ft_printx.c ft_getformat.c \
					ft_printd.c ft_printp.c ft_printu.c utilities.c

OBJECTS 		=	$(SOURCES:.c=.o)

DEPENDENCIES	=	ft_printf.h libft/libft.h Makefile libft/Makefile libft

MAKE			=	make --no-print-directory


all:		 
			$(MAKE) -C $(LIBFT_DIR)
			cp $(LIBFT) $(NAME)
			$(MAKE) $(NAME)

$(NAME):	$(LIBFT) $(OBJECTS) $(DEPENDENCIES)
				ar -rc $@ $(OBJECTS)

$(LIBFT):	$(LIBFT_DIR)
				$(MAKE) -C $(LIBFT_DIR)
				cp $(LIBFT) $(NAME)

%.o:		%.c $(DEPENDENCIES)
				$(CC) -c -I. $<

clean:
				$(MAKE) clean -C $(LIBFT_DIR)
				rm -rf $(OBJECTS)

fclean:		clean
				$(MAKE) fclean -C $(LIBFT_DIR)
				rm -rf $(NAME)

re:			fclean 
				make all

bonus: 		all

.PHONY: 	all clean fclean re bonus
