#include <string>
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <tic.h>
#include "url_debug.h"

/**
 *
 * sandy.haryono@thalesgroup.com
 * This is sample code for using REST API
 *
 */

const u_int DEBUG = 1;


using namespace std;

// Callback function to handle curl's response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


// Function to perform CURL request
bool request(const string& url, const string& username, const string& password, string& response, Json::Value& appended) {

    CURL *curl = curl_easy_init();

    config.trace_ascii = 1; /* enable ascii tracing */

    struct curl_slist *headers = NULL;

    if (!curl) {
        cerr << "Failed to initialize CURL" << endl;
        return false;
    }

    Json::FastWriter writer;
    const std::string jsonObj = writer.write(appended);
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "User-Agent: mozilla/4.0");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    if(config.trace_ascii == DEBUG){
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
        curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
    }
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);


    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return false;
    }

    return true;
}


// Function to parse JSON response
bool parseJsonResponse(const string& jsonResponse, Json::Value& parsedRoot) {
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    string errs;

    bool parsingSuccessful = reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &parsedRoot, &errs);
    delete reader;

    if (!parsingSuccessful) {
        cerr << "Failed to parse JSON: " << errs << endl;
        return false;
    }

    return true;
}


bool hitTheUrl(const string& url,const string& username,const string& password, Json::Value& response, Json::Value& appended){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    string stringResponse;
    if(request(url, username, password, stringResponse, appended)) {
        Json::Value root;
        if (!parseJsonResponse(stringResponse, response))
            return false;
    }
    curl_global_cleanup();
    return true;
}

