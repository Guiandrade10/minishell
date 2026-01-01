/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:52:55 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 15:14:49 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
	size_t		len;
	t_token		*tokens;
}	t_lexer;

bool		is_quote(char c);
void		advance(t_lexer *lex);
bool		is_whitespace(char c);
char		peek_char(t_lexer *lex);
bool		is_operator_char(char c);
t_token		*lexer(const char *input);
char		current_char(t_lexer *lex);
void		token_free(t_token *token);
bool		tokenize_word(t_lexer *lex);
bool		lexer_tokenize(t_lexer *lex);
t_token		*token_last(t_token *tokens);
void		skip_whitespace(t_lexer *lex);
bool		tokenize_operator(t_lexer *lex);
void		token_list_free(t_token *tokens);
int			token_list_size(t_token *tokens);
bool		advance_to_word_end(t_lexer *lex);
bool		token_add(t_lexer *lex, t_token *new_token);
void		lexer_init(t_lexer *lex, const char *input);
const char	*token_type_to_printable(t_token_type type);
ssize_t		skip_quoted_section(const char *str, size_t pos);
char		*extract_quoted_content(const char *str, size_t *pos);
t_token		*token_create(t_token_type type, const char *value, bool owned);

#endif
