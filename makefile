# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 17:04:34 by aamoussa          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/09/16 16:38:42 by zoukaddo         ###   ########.fr        #
=======
#    Updated: 2022/09/16 13:39:04 by aamoussa         ###   ########.fr        #
>>>>>>> c6c1840004ea643bb4d1d128133d08be6f27a232
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= shell.c token.c parser.c build_nodes.c argument_cleaner.c \
				  $(BUILTIN)echo.c $(BUILTIN)env.c ./excution/utils/env_handler.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc -g

RM				= rm -f

<<<<<<< HEAD
READLINE_PATH =  -lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include 

BUILTIN 		= ./excution/builtin/
=======
READLINE_PATH =  -lreadline  -I ~/homebrew/opt/readline/include -g
>>>>>>> c6c1840004ea643bb4d1d128133d08be6f27a232

CFLAGS			=  #-Wall -Wextra -Werror -Werror 

all:			$(NAME)

$(NAME):		$(OBJS)
				
				gcc ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME} $(READLINE_PATH)

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re