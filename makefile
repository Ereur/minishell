# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 17:04:34 by zoukaddo          #+#    #+#              #
#    Updated: 2022/10/30 13:56:33 by aamoussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
				  
SRCS			= shell.c ./parser/token.c ./parser/parser.c ./parser/build_nodes.c ./parser/argument_cleaner.c ./parser/her_doc.c  ./parser/parse_cmd.c ./parser/redirection_parser.c\
					./parser/utils.c ./parser/arg_cleaner_utils.c ./parser/arg_cleaner.c\
				  $(BUILTIN)echo_cmd.c  $(BUILTIN)env.c $(BUILTIN)cd_cmd.c $(EXECUTION)utils/env_handler.c  $(EXECUTION)utils/env_handler_utils.c $(EXECUTION)/utils/utils.c \
				  $(BUILTIN)pwd.c $(BUILTIN)export_cmd.c $(BUILTIN)export_cmd_helper.c $(BUILTIN)unset_cmd.c $(BUILTIN)exit_cmd.c \
				  $(EXECUTION)executer.c $(EXECUTION)executer_helper.c $(EXECUTION)execute_builtins.c $(EXECUTION)signals.c

OBJS			= $(SRCS:.c=.o)

CC				= cc -g 

RM				= rm -f

READLINE_PATH = -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include
#-lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include
#-lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include


BUILTIN 		= ./excution/builtin/

EXECUTION		= ./excution/

CFLAGS			=  #-fsanitize=address -g  -Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJS)
				cd ./libft && make
				cd ./libft && make bonus
				$(CC) ${OBJS} $(CFLAGS) ./libft/libft.a -o ${NAME} $(READLINE_PATH) -g

clean:
				$(RM) $(OBJS) 
				cd ./libft && make clean

fclean:			clean
				$(RM) $(NAME)
				cd ./libft && make fclean
				
re:				fclean $(NAME)

.PHONY:			all clean fclean re