#include "minishell.h"

// static void    dq_word_expander(t_lx *lx, t_lx *next_lx)
// {

// }

// static void     word_expander(t_lx *lx, t_lx *next_lx)
// {
//     /*to do
//     1. handle default case of dollar at the begging like "$path"
//     if not found replace lexer->content with NULL and set type to EMPTY_VAR
//     2. handel case of dollar at the middle like "ayoub$hamada"
//     if not found take  string before '$' sign and ignore the rest

//     if found sapce in both cases split it as seperate words
//     */
// }

// void    expand_dollar(t_lx *lexer)
// {
//     while(lexer)
//     {
//         if (lexer->type == WORD && could_expand(lexer->content))
//             word_expander(lexer, lexer->next);
//         else if (lexer->type == WORD_D_QUOTES && could_expand(lexer->content))
//             dq_word_expander(lexer, lexer->next);
//         lexer = lexer->next;
//     }
// }