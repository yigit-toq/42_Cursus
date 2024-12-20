/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:12:06 by ytop              #+#    #+#             */
/*   Updated: 2024/12/20 18:26:41 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <string.h>
#include <zlib.h>

#define MAX_FRAME   75

typedef struct s_zip
{
	int		size;
	char	*path;
	char	*data;
}			t_zip;

void	init_zip(void *mlx)
{
	const char	*zip_path = "../Frame/Reaver/vandal_xpm.zip";
	const char	*temp_dir = "temp_frames";
	char		command[256];

	snprintf(command, sizeof(command), "mkdir -p %s && unzip -o %s -d %s", temp_dir, zip_path, temp_dir);
	if (system(command))
		error_controller("Failed to extract zip file.", NULL);

    snprintf(command, sizeof(command), "ls %s", temp_dir);

    FILE *fp = popen(command, "r");
    if (!fp)
		error_controller("Failed to list files in directory.", NULL);

    char filename[256];
    while (fgets(filename, sizeof(filename), fp))
	{
        filename[strcspn(filename, "\n")] = '\0';

        char	filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", temp_dir, filename);

        // XPM dosyasını yükle
        void *image = mlx_xpm_file_to_image(mlx, filepath, NULL, NULL);
        if (image == NULL) {
            fprintf(stderr, "Failed to load XPM image: %s\n", filepath);
        } else {
            printf("Successfully loaded: %s\n", filepath);
        }
    }
    pclose(fp);

    // Geçici dosyaları temizle
    snprintf(command, sizeof(command), "rm -rf %s", temp_dir);
    system(command);
}
