/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:08:35 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/23 12:18:04 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static int	digits_num(int n)
{
	int	num;

	num = 1;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		num++;
	}
	return (num);
}

static char	*underflow(void)
{
	char	*str;

	str = (char *)malloc(12);
	if (!str)
	{
		return (NULL);
	}
	ft_strcpy(str, "-2147483648");
	return (str);
}

static char	convert_num(int total, int ind, char *res, int num)
{
	while (total > 0)
	{
		ind--;
		res[ind] = '0' + (num % 10);
		num /= 10;
		total--;
	}
	return (*res);
}

char	*ft_itoa(int n)
{
	int		total_num;
	int		sign;
	char	*result;
	int		index;

	total_num = digits_num(n);
	sign = 0;
	if (n == -2147483648)
		return (underflow());
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	result = (char *)malloc(total_num + sign + 1);
	if (!result)
		return (NULL);
	index = total_num + sign;
	result[index] = '\0';
	convert_num(total_num, index, result, n);
	if (sign == 1)
		result[0] = '-';
	return (result);
}

// int	main(void)
// {
// 	int		num;
// 	char	*str;

// 	num = -2147483648;
// 	str = ft_itoa(num);
// 	if (str)
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	return (0);
// }
