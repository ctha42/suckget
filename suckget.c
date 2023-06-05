#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Usage: %s <urls>\n", argv[0]);
        return 1;
    }
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return 2;
    }
    for (int i = 0; i < argc - 1; i++){
            CURLcode res;
            long http_code = 0;
            char errbuf[CURL_ERROR_SIZE];
            curl_easy_setopt(curl, CURLOPT_URL, argv[i + 1]);
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
            curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
            res = curl_easy_perform(curl); // Perform the operation
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            if (res != CURLE_OK){
                if (res == CURLE_HTTP_RETURNED_ERROR){
                    fprintf(stderr, "HTTP Error: %lu\n", http_code);
                }
                else{ 
                    // Error handling for internal curl errors
                    size_t len = strlen(errbuf);
                    if(len)
                        fprintf(stderr, "%s%s", errbuf, ((errbuf[len - 1] != '\n') ? "\n" : ""));
                    else{
                        fprintf(stderr, "%s\n", curl_easy_strerror(res));
                    }
                }
            }
    }
    curl_easy_cleanup(curl);
}