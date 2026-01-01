/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quote_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:00:00 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 15:00:00 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <stdio.h>
#include <string.h>

static bool	test_quote_removal(const char *input, const char *expected)
{
	char	*result;
	bool	passed;

	result = remove_outer_quotes(input);
	if (!result && !expected)
		return (true);
	if (!result || !expected)
	{
		if (result)
			free(result);
		return (false);
	}
	passed = (strcmp(result, expected) == 0);
	free(result);
	return (passed);
}

static bool	test_quote_removal_alt(const char *input, const char *expected)
{
	char	*result;
	bool	passed;

	result = remove_quotes(input);
	if (!result && !expected)
		return (true);
	if (!result || !expected)
	{
		if (result)
			free(result);
		return (false);
	}
	passed = (strcmp(result, expected) == 0);
	free(result);
	return (passed);
}

static void	run_test(const char *name, bool passed)
{
	if (passed)
		printf("✓ %s\n", name);
	else
		printf("✗ %s FAILED\n", name);
}

int	main(void)
{
	printf("Testing empty quote handling:\n");
	run_test("Empty single quotes", test_quote_removal("''", ""));
	run_test("Empty double quotes", test_quote_removal("\"\"", ""));
	run_test("Two adjacent empty single", test_quote_removal("''''", ""));
	run_test("Mixed empty quotes", test_quote_removal("''\"\"", ""));
	printf("\n");
	printf("Testing nested/mixed quote handling:\n");
	run_test("Adjacent single quotes", test_quote_removal("'a''b'", "ab"));
	run_test("Adjacent double quotes", test_quote_removal("\"a\"\"b\"", "ab"));
	run_test("Mixed quote types", test_quote_removal("'a'\"b\"", "ab"));
	run_test("POSIX single quote embed", test_quote_removal("'it'\"'\"'s'", "it's"));
	run_test("Single in double", test_quote_removal("\"x'y\"", "x'y"));
	run_test("Double in single", test_quote_removal("'x\"y'", "x\"y"));
	printf("\n");
	printf("Testing consistency between functions:\n");
	run_test("Alt: Empty single", test_quote_removal_alt("''", ""));
	run_test("Alt: Empty double", test_quote_removal_alt("\"\"", ""));
	run_test("Alt: Adjacent single", test_quote_removal_alt("'a''b'", "ab"));
	run_test("Alt: POSIX embed", test_quote_removal_alt("'it'\"'\"'s'", "it's"));
	printf("\n");
	printf("Testing NULL handling:\n");
	run_test("NULL input", test_quote_removal(NULL, NULL));
	printf("\n");
	return (0);
}
