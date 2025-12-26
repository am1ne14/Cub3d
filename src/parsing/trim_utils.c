#include "../../includes/cub3d.h"

char	*find_trim_start(char *str)
{
	char	*start;

	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	return (start);
}

char	*find_trim_end(char *start)
{
	char	*end;

	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		end--;
	return (end);
}

char	*copy_trimmed_string(char *start, int len)
{
	char	*result;
	int		i;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

char	*trim_line_spaces(char *str)
{
	char	*start;
	char	*end;
	int		len;

	if (!str)
		return (NULL);
	start = find_trim_start(str);
	if (*start == '\0')
		return (ft_strdup(""));
	end = find_trim_end(start);
	len = end - start + 1;
	return (copy_trimmed_string(start, len));
}
