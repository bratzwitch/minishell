/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:26:02 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 11:46:30 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num * size;
	if (num == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (total_size / num != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

// int	main(void)
// {
// 	int *arr = (int *)ft_calloc(5, sizeof(int));
// 	int i;
// 	i = 0;

// 	if (arr)
// 	{
// 		while (i < 5)
// 		{
// 			printf("%d ", arr[i]);
// 			i++;
// 		}

// 		free(arr);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}

// 	return (0);
// }