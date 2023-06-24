#include "../../minishell.h"

/* -------------------- 1.If $env_var ----------------------------*/
static char	*if_env_var(char *str,  t_env *env, t_dlist **trash)
{
	int		i;
	int 	j;
	char	*tmp[3];
	t_list	*ret;

	i = 0;
	j = 0;
	tmp[0] = "";
	ret = NULL;
	while (ft_isalnum(str[i]))
		i++;
	if (!ft_isquote(str[i]) && ft_issigle(str[i])
			&& str[i])
	{
		while (str[i + j] != '\"' && str[i + j])
			j++;
		tmp[1] = ft_substr(str + i, 0, j, trash);
	}
	tmp[2] = ft_substr(str, 0, i, trash);
	ret = find_var_env(env, tmp[2], 1);
	if (ret)
		tmp[0] = ft_strdup(ret->valeur, trash);
	if (j > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 2.If $? ----------------------------*/
static char	*if_errno(char *str, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	if (*str && *str != '\"')
	{
		while (!ft_isquote(str[i]))
			i++;
		tmp[1] = ft_substr(str, 0, i, trash);
	}
	tmp[0] = ft_strdup(ft_itoa(g_errno, trash), trash);
	if (i > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 3.If $ on d_quote ----------------------------*/
static char	*ft_quote_d(char *str, t_env *env, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	tmp[0] = str;
	while (str[i] != '\"' && str[i] != '$')
		i++;
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		tmp[0] = ft_substr(str, 0, i, trash);
	if (ft_isalnum(str[i + 1]))
	{
		tmp[1] = if_env_var(str + (i + 1), env, trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	else if (str[i + 1] == '?')
	{
		tmp[1] = if_errno(str + (i + 2), trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	return (tmp[0]);
}
/* -------------------- 4.Double quote function ----------------------------*/
char	*ft_dquote(char *str, t_shell *info)
{
	int		i;
	int		check;
	char	*tmp;

	tmp = NULL;
	i = 1;
	check = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && check == 0)
		{
			tmp = ft_quote_d(str + 1, info->env, &info->trash_lst);
			check++;
		}
		else if (str[i] == '$' && check != 0)
			tmp = ft_quote_d(tmp, info->env, &info->trash_lst);
			
		i++;
	}
	creat_and_add(tmp, str, WORD, i, info);
	return (str + (i + 1));
}

/* -------------------- 5.Simple quote function ----------------------------*/
char	*ft_squote(char *str, t_shell *info)
{
	int		i;

	i = 1;
	while (!ft_isquote(str[i]))
		i++;
	creat_and_add(NULL, str, WORD, i, info);
	return (str + (i + 1));
}