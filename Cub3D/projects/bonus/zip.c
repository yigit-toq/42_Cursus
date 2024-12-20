/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:12:06 by ytop              #+#    #+#             */
/*   Updated: 2024/12/20 13:12:06 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "zip.h"

#define MAX_FRAME   75

typedef struct s_zip
{
	int		size;
	char	*path;
	char	*data;
}			t_zip;

static void	init_zip(char *path)
{
	char	*zip_path = "./Frame/Reaver/vandal_xpm.zip";
	zip_t	*zip;
	int		err;
	int		f_count;
	t_zip	frame[MAX_FRAME];

	f_count = 0;
	zip = zip_open(zip_path, ZIP_RDONLY, &err);
	error_controller("Failed to open zip file", zip);

	zip_int64_t num_entries = zip_get_num_entries(zip, 0);
	for (zip_int64_t i = 0; i < num_entries; i++)
	{
		const char *name = zip_get_name(zip, i, 0);
		if (ft_strnstr(name, path, ft_strlen(path)))
		{
			frame[f_count].path = ft_strdup(name);
			frame[f_count].size = zip_get_file_size(zip, i, 0);
			frame[f_count].data = ft_calloc(frame[f_count].size + 1, sizeof(char));
			zip_file_t *file = zip_fopen_index(zip, i, 0);
			zip_fread(file, frame[f_count].data, frame[f_count].size);
			zip_fclose(file);
			f_count++;
		}
	}
}
