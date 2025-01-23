/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:21:43 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/23 12:18:46 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	return (result);
}

// int main(void) {
//     const char *s1 = "Hello, ";
//     const char *s2 = "world!";

//     char *result = ft_strjoin(s1, s2);

//     if (result) {
//         printf("Concatenated string: %s\n", result);
//         free(result);
//     } else {
//         printf("Memory allocation failed.\n");
//     }

//     return (0);
// }
