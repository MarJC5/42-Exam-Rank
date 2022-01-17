#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_printf_char(char c, int *count)
{
	*count += write(1, &c, 1);
	return(*count);
}

int	ft_printf_str(char *str, int *count)
{
	int	i;

	i = -1;
	while(str[++i])
		ft_printf_char(str[i], count);
	return (*count);
}

int	ft_printf_base(long nbr, int *count, int base)
{
	if (nbr == 0)
		ft_printf_char('0', count);
	if (nbr < 0)
	{
		ft_printf_char('-', count);
		nbr *= -1;
		ft_printf_base(nbr, count, base);
	}
	if (nbr > base)
	{
		ft_printf_base(nbr / base, count, base);
		ft_printf_base(nbr % base, count, base);
	}
	else
	{
		if (nbr < 10)
			nbr += 48;
		else
			nbr += 87;
		ft_printf_char(nbr, count);
	}
	return (*count);
}

int	ft_printf_args(va_list args, char convert, int *count)
{
	if (convert == 's')
		ft_printf_str(va_arg(args, char *), count);
	else if (convert == 'd')
		ft_printf_base((int)va_arg(args, int), count, 10);
	else if (convert == 'x')
		ft_printf_base((unsigned int)va_arg(args, int), count, 16);
	return (*count);
}

int	ft_printf(const char *input, ...)
{
	int	i;
	int count;
	va_list args;

	i = -1;
	count = 0;
	va_start(args, input);
	while (input[++i])
	{
		if (input[i] != '%')
			ft_printf_char(input[i], &count);
		if (input[i] == '%' && input[i + 1])
			ft_printf_args(args, input[++i], &count);
	}
	va_end(args);
	return (count);
}
