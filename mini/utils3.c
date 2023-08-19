/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:50:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/19 16:30:11 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int noptions(t_list *lst)
{
    t_list *tmp;
    int i;
    i = 0;
    tmp = lst;
    while(tmp)
    {
        if(tmp->token == 0)
            i++;
        tmp = tmp->next;
    }
    return (i);
}
char	*stock(char *av)
{
	char	*line;
	char	*tmp;
    char *all;
    // char *exp;

    all = NULL;
    // exp = NULL;
	line = readline("here_doc: ");
	while (line)
	{
		if (ft_strcmp(line, av) == 0)
			break ;
        // exp = check_expend(tmp);
		tmp = ft_strjoin(line, "\n");
        all = ft_strjoin(all, tmp);
		line = readline("here_doc: ");
		free(tmp);
	}
	free(line);
    return (all);
}
int count_x(t_list *lst, int j)
{
    t_list *tmp;
    int i;
    i = 0;
    tmp = lst;
    while(tmp)
    {
        if(tmp->token == j)
            i++;
        tmp = tmp->next;
    }
    return (i);
}
// char *lst_fdin(t_list *lst, int n)
// {
//     t_list *tmp;
//     tmp = lst;
//     while((lst))
//     {
//         if((lst)->token == n)
//             return (tmp);
//         else if((lst)->token == 5 || (lst)->token == 2)
//             tmp = lst;
//         (lst) = (lst)->next;
//     }
//     return (NULL);
// }
char 	**open_here(t_list *lst)
{
	char	**data;
    int i;
    i = 0;
    data = malloc(sizeof(char *) * (count_x(lst, 5) + 1));
    if(!data)
        return (0);
    while(lst)
    {
        if(lst->token == 5)
        {
            data[i] = stock(lst->next->content);
            i++;
        }
        lst = lst->next;
    }
    data[i] = NULL;
    return (data);
}
int openin(t_list *tmp, char **s, int j)
{
    int fd;
    char *here;
    if(tmp->token == 5)
    {
        here = ft_strjoin("/tmp/her", ft_itoa(j));
        fd = open(here, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if(fd == -1)
            return (perror("open"), -2);
        ft_putstr_fd(s[j], fd);
    }
    else
    {
        fd = open(tmp->next->content, O_RDONLY);
        if(fd == -1)
        return (perror("open"), -2);
    }
    return (fd);
}
int openout(t_list *lst)
{
    int fd;
    fd = 1;
    if(lst->token == 3)
    {
        fd = open(lst->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
        if(fd == -1)
            return (perror("open"), -2);

    }
    else if(lst->token == 4)
    {
        fd = open(lst->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
        if(fd == -1)
            return (perror("open"), -2);
    }
    return (fd);
}
void  allocate(t_data **data, int i)
{
    t_data *tmp;
    (*data)->in = -1;
    (*data)->out = 1; 
    (*data)->cmd = NULL;
    (*data)->next = NULL;
    tmp = *data;
    while(i -1 > 0)
    {
        ft_lstadd_back2(&tmp, ft_lstnew2(NULL, -1, 1));
        tmp = tmp->next;
        i--;
    }
}

void ft_skip(t_list **lst)
{
    while((*lst))
    {
        if((*lst)->next && (*lst)->next->content[0] == '|')
            break;
        if((*lst)->next == NULL)
            break;
        (*lst) = (*lst)->next;
    }
}
void handle_tokens(t_list **lst, t_data **data, char **s, int j)
{
    t_list *tmp;
    t_data *tmp1;
    tmp1 = *data;
    tmp = *lst;
    if(tmp->token == 2 || tmp->token == 5)
    {
        if(tmp1->in)
            close(tmp1->in);
        tmp1->in = openin(tmp, s, j);
        if(tmp1->in == -2)
            ft_skip(lst);
    }
    else if(tmp->token == 4 ||  tmp->token == 3)
    {
        if(tmp1->out > 1)
            close(tmp1->out);
        tmp1->out = openout(tmp);
        if(tmp1->out == -2)
            ft_skip(lst);
    }
}

void  fill(t_data **data, t_list *lst, char **s)
{
    t_data *tmp;
    tmp = *data;
    int j;
    j = 0;
    while(lst)
    {
        if(lst->token == 1)
        {
            if(tmp->out == 1)
                tmp->out = 0;
            tmp = tmp->next;
            tmp->in = 0;
        }
        else if(lst->token)
        {
            handle_tokens(&lst, &tmp, s, j);
            if(lst && lst->token == 5)
                j++;
        }
        lst = lst->next;
    }
}
int    convert_lst(t_list *lst)
{
    char **s;
    t_data *data;
    // t_data *tmp1;
    // int i = 0;
    // int j = 0;
    // // t_list *tmp;
    // tmp = NULL;
    data = malloc(sizeof(t_data));
    if(!data)
        return (0);
    allocate(&data, count_x(lst, 1) + 1);
    s = open_here(lst);
    fill(&data, lst, s);
    // tmp1 = data;
    // while(lst)
    // { 
    //     if(lst->token == 1 || lst->next == NULL)
    //     {
    //         if(tmp)
    //             tmp1->in = openin(tmp, s[j]);
    //         if(lst->token == 1 && tmp1->out < 2)
    //             tmp1->out = 0;
    //       tmp1 = tmp1->next;
    //         if(tmp1 != NULL)
    //             tmp1->in = 1;
    //       tmp = NULL;
    //     }
    //    else if(lst->token == 5 || lst->token == 2)
    //     {
    //         if(lst->token == 5)
    //            j++;
    //         tmp = lst;
    //     }
    //     else if(lst->token == 3 || lst->token == 4)
    //             tmp1->out = openout(lst);
    //         else if(lst->token == 0)
    //             i++;
    //     lst = lst->next;
    // }
    while(data)
    {
        printf("in = %d\n", data->in);
        printf("out = %d\n", data->out);
        data = data->next;
    }
        return(1);
}