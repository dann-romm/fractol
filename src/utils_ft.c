/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:58:19 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 17:40:13 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	i = 0;
	ans = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') * (-1) + (str[i] == '+');
		i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] > '0' && str[i] <= '9')
		ans = sign * (str[i++] - '0');
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((ans * 10 + sign * (str[i] - '0') > 0) != (ans > 0))
			return (0);
		ans = ans * 10 + sign * (str[i] - '0');
		i++;
	}
	return (ans);
}

double	ft_atof(const char *str)
{
	int		i;
	double	num;
	double	pow;
	char	sign;

	if ((str[0] == '-' || str[0] == '+') && (str[1] < '0' || str[1] > '9'))
		return (0);
	num = (double)ft_atoi(str);
	sign = (num < 0) * -1 + (num >= 0);
	pow = 1;
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	while (str[++i] == '0')
		pow *= 10;
	while (str[i] >= '0' && str[i] <= '9')
	{
		pow *= 10;
		num += sign * (str[i++] - '0') / pow;
	}
	return (num);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
