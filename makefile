# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 17:04:34 by aamoussa          #+#    #+#              #
#    Updated: 2022/09/15 19:01:34 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= shell.c token.c parser.c build_nodes.c argument_cleaner.c
				

OBJS			= $(SRCS:.c=.o)

CC				= gcc

RM				= rm -f

READLINE_PATH =  -lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include

CFLAGS			=  #-Wall -Wextra -Werror -Werror 

all:			$(NAME)

$(NAME):		$(OBJS)
				
				gcc ${CFLAGS} $(READLINE_PATH) ${OBJS} ./libft/libft.a -o ${NAME}

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re