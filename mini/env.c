/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:34:51 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/19 18:41:56 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct s_env
{
	char *value;
	char *name;
	struct s_env *next;
}		t_env;

t_env *ft_lstdadd_back1(t_env **lst, t_env *new)
{
    t_env *tmp;
    if(!lst || !new)
        return (0);
    if(!(*lst))
        *lst = new;
    else
    {
        tmp = *lst;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (new);
}

t_env *ft_lstnew1(char *name, char *value)
{
    t_env *node;
    node = malloc(sizeof(t_env));
    if(!node)
        return (0);
    if(node)
    {
        node->name = name;
        node->value = value;
        node->next = NULL;
    }
    return (node);
}

char *get_name(char *str)
{
    int i;
    char *name;
    i = 0;
    while(str[i] != '=')
        i++;
    name = malloc(sizeof(char) * i);
    i = 0;
    while(str[i] != '=')
    {
        name[i] = str[i];
        i++;
    }
    name[i] = '\0';
    return (name);
}
char *get_value(char *str)
{
    int i;
    int j;
    char *value;
    i = 0;
    while(str[i] != '=')
        i++;
    i++;
    j = i;
    while(str[i])
        i++;
    value = malloc(sizeof(char) * (i - j));
    i = 0;
    while(str[j])
    {
        value[i] = str[j];
        i++;
        j++;
    }
    value[i] = '\0';
    return (value);
}
void get_environ(t_env *envi)
{
    extern char	**environ;
    int i;
    char *name;
    char *value;
    i = 1;
    name = get_name(environ[i]);
    value = get_value(environ[i]);
    envi = ft_lstnew1(name, value);
    while(environ[i])
    {
        name = get_name(environ[i]);
        value = get_value(environ[i]);
        ft_lstdadd_back1(&envi, ft_lstnew1(name, value));
        i++;
    }
    while(envi)
    {
        printf("name:  %s|  value: %s\n", envi->name, envi->value);
        envi = envi->next;
    }
}

int main()
{
    t_env *envi;
    get_environ(envi);
    return (0);
}