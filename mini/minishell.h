/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:28:50 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/19 17:38:48 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define word 0
# define PIPE 1
# define redin 2
# define redout 3
# define append 4
# define heredoc 5
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
char				*quote(char *in);
int					pparss(char *input);
void				parss(void);
int					ft_strchrr(char *s, char c);
typedef struct s_data
{
	char **cmd;
	int in;
	int out;
	struct s_data	*next;
	
}	t_data;
typedef struct s_env
{
	char *value;
	char *name;
	struct s_env *next;
}		t_env;

typedef struct s_list
{
	int g;
	char			*content;
	int				token;
	char			**env;
	int				num;
	t_env 			*envi;
	struct s_list	*next;
}					t_list;
int    convert_lst(t_list *lst);
int	ft_lstsize(t_data *lst);
t_data	*ft_lstnew2(char **s,int in, int out);
void	ft_lstadd_back2(t_data **lst, t_data *new);
int					ft_word(char *s, t_list **lst);
int					fil_env(t_list **lst);
int					detach_separted(char *str, t_list **lst);
int					end_struct(t_list **lst);
int					ft_len(char *str);
int					ft_count(char *str);
t_list				*ft_lstnew(char *s, int content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **st_a, t_list *new);
char				*searsh_env(char *c, char **env);
int					syntax_error(char *str);
int					check_spacial(char *str);
void				add_node(t_list **head, char *content, int token);
// typedef struct s_list
// {
// 	char			*content;
// 	int				token;
// 	int 			in;
// 	int 			out;
// 	struct s_list	*next;
// }					t_list;

#endif