// Include the standard preprocessors directives
#include <stdio.h>
#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    fwrite(ptr, size, nmemb, stdout);
    return size * nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "");
        curl_easy_setopt(curl, CURLOPT_URL, "");

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("Login successful!\n");
        }

        curl_easy_cleanup(curl);
    }
    else
    {
        fprintf(stderr, "Failed to initialize CURL.\n");
    }

    return 0;
}