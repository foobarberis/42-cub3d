static char *f_strchrnul(const char *s, int c)
{
	while (*s && *(unsigned char *)s != c)
		s++;
	return ((char *)s);
}

static int	here_doc_split(char **arr, char *buf)
{
	int		i;
	char	c;
	char	*p;

	i = 0;
	p = buf;
	while (*p && *buf)
	{
		if (f_isspace(*p))
			while (*p && f_isspace(*p))
				p++;
		else
			while (*p && (!f_isspace(*p)))
				if (*++p == '$')
					break ;
		c = *p;
		*p = 0;
		arr[i] = f_strdup(buf);
		if (!arr[i++])
			return (env_array_destroy(arr, i), 1);
		*p = c;
		buf = p;
	}
	return (0);
}
