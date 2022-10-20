# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 17:04:34 by zoukaddo          #+#    #+#              #
#    Updated: 2022/10/14 20:08:03 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= shell.c token.c parser.c build_nodes.c argument_cleaner.c \
				  $(BUILTIN)echo_cmd.c  $(BUILTIN)env.c $(BUILTIN)cd_cmd.c $(EXECUTION)utils/env_handler.c  $(EXECUTION)/utils/utils.c \
				  $(BUILTIN)pwd.c $(BUILTIN)export_cmd.c $(BUILTIN)unset_cmd.c $(BUILTIN)exit_cmd.c \
				  $(EXECUTION)executer.c $(EXECUTION)execute_builtins.c $(EXECUTION)signals.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc -g

RM				= rm -f

READLINE_PATH =  -lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include
#-lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include
#-lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include


BUILTIN 		= ./excution/builtin/

EXECUTION		= ./excution/

CFLAGS			=  #-fsanitize=address -fno-omit-frame- #-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJS)
				
				gcc ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME} $(READLINE_PATH) -g

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re