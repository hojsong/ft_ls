/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojsong <hojsong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:47:28 by hojsong           #+#    #+#             */
/*   Updated: 2024/03/29 20:57:10 by hojsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

size_t ft_strlen(const char* str){
    size_t i;

    if(str == NULL)
        return 0;
    i = 0;
    while(str && str[i]){
        i++;
    }
    return (i);
}

int     ft_strcmp(char *str1, char *str2){
    size_t i;

    if(str1 == NULL || str2 == NULL){
        if (str1 == NULL && str2)
            return (-str2[0]);
        else if (str2 == NULL && str1)
            return (str1[0]);
        else
            return (1);
    }
    i = 0;
    while (str1[i] && str2[i]){
        if (str1[i] != str2[i])
            return(str1[i] - str2[i]);
        i++;
    }
    if (str1[i] || str2[i])
        return(str1[i] - str2[i]);
    return (0);
}

char    *ft_replace(char *str, size_t n){
    char    *result;
    size_t i, size;

    size = ft_strlen(str);
    i = n;
    result = malloc(sizeof(char) * (size - i + 1));
    if (result == NULL)
        return NULL;
    while (i < size){
        result[i - n] = str[i];
        i++;
    }
    result[i - n] = '\0';
    return result;
}

char    *ft_pathjoin(char *str1, char *str2){
    char    *result;
    size_t  s1;
    size_t  s2;
    size_t  i;
    size_t  i2;

    s1 = ft_strlen(str1);
    s2 = ft_strlen(str2);
    i = 0;
    result = malloc(sizeof(char) * (s1 + s2 + 2));
    while(i < s1){
        result[i] = str1[i];
        i++;
    }
    result[i++] = '/';
    i2 = 0;
    while(i2 < s2){
        result[i + i2] = str2[i2];
        i2++;
    }
    result[i + i2] = '\0';
    return (result);
}

char    *ft_strdup(char *str){
    char    *result;
    size_t  size;
    size_t  i;

    size = ft_strlen(str);
    result = malloc(sizeof(char) * size + 1);
    i = 0;
    while (i < size){
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return result;
}
