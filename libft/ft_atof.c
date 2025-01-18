/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:26:24 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 11:46:12 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	ft_parse_integer_part(char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	ft_parse_fractional_part(char **str)
{
	double	result;
	double	factor;

	result = 0.0;
	factor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			factor *= 10.0;
			result += (**str - '0') / factor;
			(*str)++;
		}
	}
	return (result);
}

double	ft_atof(char *str)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	result = ft_parse_integer_part(&str);
	result += ft_parse_fractional_part(&str);
	return (result * sign);
}
