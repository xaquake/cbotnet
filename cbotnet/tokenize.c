#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define TKNSIZE 47
#define CHECKS(x) assert(strlen(x) == 46)

typedef struct
{
	size_t size;
	char all[100][47];
} tokens;

tokens *TOKENS(const char __tokens[100][47], const size_t __size)
{
	tokens *tkns = (tokens *)malloc(sizeof(tokens));
	tkns->size = __size;
	for (size_t i = 0; i < __size; i++)
	{
		CHECKS(__tokens[i]);
		memcpy(tkns->all[i], __tokens[i], 47);
	}
	return tkns;
}

void append_token(tokens *restrict __tokens, const char __token[47])
{
	CHECKS(__token);
	memcpy(__tokens->all[__tokens->size], __token, 47);
	__tokens->size++;
}

void change_token(tokens *restrict __tokens, const char __token[47], const size_t __pos)
{
	CHECKS(__token);
	memcpy(__tokens->all[__pos], __token, 47);
}

void clear_tokens(tokens *restrict __tokens)
{
	for (size_t i = 0; i < __tokens->size; i++)
	{
		free(__tokens->all[i]);
		memset(&__tokens->all[i], 0, 47);
	}
	__tokens->size = 0;
	free(__tokens);
}

#ifdef __cplusplus
}
#endif
