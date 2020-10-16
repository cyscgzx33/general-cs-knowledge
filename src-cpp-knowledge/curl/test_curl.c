#include <curl/curl.h>
#include <stdio.h>

/* 
 * A sample downloadable picture:
 *     https://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Nusfjord_road%2C_2010_09.jpg/1280px-Nusfjord_road%2C_2010_09.jpg
 */

void testNobody(char* file_path, char* web_url) {
    int res;
    CURL* curl;
    FILE* fp;
    curl = curl_easy_init();
    fp = fopen(file_path, "wb");
    curl_easy_setopt(curl, CURLOPT_URL, web_url);
    
    /* get us the resource without a body - use HEAD! */
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // actually, no matter if there's this nobody, the getinfo will always get length
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /* Perform the request */
    res = curl_easy_perform(curl);
    if(!res) {
        /* check the size */
        curl_off_t cl;
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &cl);
        if(!res) {
            printf("Download size: %" CURL_FORMAT_CURL_OFF_T "\n", cl);
        }
    }

    fclose(fp);
    curl_easy_cleanup(curl);
}

void testWriteData(char* file_path, char* web_url) {
    CURL* curl;
    FILE* fp;
    int res;

    fp = fopen(file_path, "wb");
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, web_url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);

    if (res == CURLE_OK)
        printf("Download successfully!\n");
    else
        printf("Error: %s\n", curl_easy_strerror(res));

    fclose(fp);
    curl_easy_cleanup(curl);
}

int main(int argc, char** argv) {
    // testWriteData(argv[1], argv[2]);
    testNobody(argv[1], argv[2]);
    return 0;
}