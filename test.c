#include <curl/curl.h>
#include "cbotnet/cbotntasks.c"

int main()
{
	CURL *curl = curl_easy_init();
	char tk[3][TKNSIZE] = {"TOKEN", "TOKEN", "TOKEN"};
	tokens *tkns = TOKENS(tk, 3);
	append_token(*&tkns, "TOKEN");
	message *msg = MESSAGE("@xarlmc", "<b>HELLO FROM C</b>", "html");
	while(1)
	{
		send_all_message(curl, tkns, msg, WRITECB);
	}
}