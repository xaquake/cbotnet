#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <curl/curl.h>
#include "tokenize.c"

#define WRITECB fopen("/dev/null", "w+")

typedef struct
{
	char chat_entity[50];
	char text[3100];
	char parse_mode[9];
} message;

message *MESSAGE(const char __chat_entity[50], const char __text[3100], const char __parse_mode[9])
{
	message *msg = (message *)malloc(sizeof(message));
	memcpy(msg->chat_entity, __chat_entity, 50);
	memcpy(msg->parse_mode, __parse_mode, 9);
	memcpy(msg->text, __text, 3100);
	return msg;
}

char *get_token_link(const char __token[47])
{
	char link[2950] = "https://api.telegram.org/bot";
	strncat(link, __token, 47);
	strncat(link, "/sendMessage", 13);
	return link;
}

char *get_token_fields(message *__message)
{
	char fields[3200];
	strncat(fields, "chat_id=", 9);
	strncat(fields, __message->chat_entity, 50);
	strncat(fields, "&text=", 7);
	strncat(fields, __message->text, 3100);
	strncat(fields, "&parse_mode=", 13);
	strncat(fields, __message->parse_mode, 9);
	return fields;
}

void *send_all_message(CURL *curl, tokens *__tokens, message *__message, void *__CB)
{
	for (size_t i = 0; i < __tokens->size; i++)
	{
		curl_easy_setopt(curl, CURLOPT_URL, get_token_link(__tokens->all[i]));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, get_token_fields(__message));
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, __CB);
		curl_easy_perform(curl);
		curl_easy_reset(curl);
		puts(__tokens->all[i]);
	}
}

#ifdef __cplusplus
}
#endif
