#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> // sudo apt-get install -y libcurl-dev
#include<json-c/json.h> //  sudo apt-get install -y libjson-c-dev

//to run gcc get_weather.c -o weather -lcurl

int main() {

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?q=Lyon&appid=4e81568c8c18c6195181ab11c04fbf25&units=metric)");

        FILE *weather = fopen("weather.json", "w");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, weather);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            printf("error");

        curl_easy_cleanup(curl);
    }
}
