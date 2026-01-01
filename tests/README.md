# Minishell Tests

This directory contains unit tests for the minishell project.

## Running Tests

### Quote Handling Tests

Test the quote parsing and removal functionality:

```bash
make test_quotes
```

This will compile and run comprehensive tests for:
- Empty quote handling (`''`, `""`)
- Nested and adjacent quotes (`'a''b'`, `"a""b"`)
- Mixed quote types (`'a'"b"`)
- POSIX single-quote embedding (`'it'"'"'s'`)
- Quotes inside opposite types (`"x'y"`, `'x"y'`)
- NULL and edge case handling

All tests must pass before merging changes to quote handling code.

## Test Files

- `test_quote_handling.c` - Comprehensive quote handling tests (16 test cases)
- `SUMMARY.md` - Detailed documentation of the empty-quote handling fix

## Adding New Tests

When adding new tests:

1. Create test file in this directory
2. Add compilation rule to `Makefile` (similar to `test_quotes` target)
3. Ensure test binary is added to `.gitignore`
4. Document the tests in this README

## Test Standards

All tests should:
- Follow Norminette 42 coding standards
- Have clear test names and descriptions
- Use consistent formatting for pass/fail output
- Clean up all allocated memory
- Return 0 on success, non-zero on failure
