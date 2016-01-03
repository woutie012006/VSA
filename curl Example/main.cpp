#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <cstring>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
    CURL *curl;
    FILE *fp;
    CURLcode res;

    char *url = "http://media.giphy.com/media/QwUvfDemn0bK0/giphy.gif";
    std::string str = url;
    std::cout << "Splitting: " << str << '\n';

    std::size_t found = str.find_last_of("/");
    std::cout << " path: " << str.substr(0,found) << '\n';
    std::cout << " file: " << str.substr(found+1) << '\n';
    str = str.substr(found+1);

    char outfilename[FILENAME_MAX];
    strcpy(outfilename, str.c_str());
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}
