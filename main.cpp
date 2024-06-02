
#include <curl/curl.h>
#include <json/json.h>
#include "url_helper.h"
using namespace std;


/**
 * 
 * This is only an example using C/C++ to have a token/detokenize in multiple JSON Array
 * sandy.haryono@thalesgroup.com
 * 
 */

int main() {

    string token_url        = "https://YOUR_CTS_FQDN/vts/rest/v2.0/tokenize";
    string detoken_url      = "https://YOUR_CTS_FQDN/vts/rest/v2.0/detokenize";
    string username_token   = "your_username_for_token", password_token = "your_password_for_token",
           username_detoken = "your_username_for_detoken", password_detoken = "your_password_for_detoken";
    Json::Value response, token, detoken;

    /**
     * initiate the data that need to tokenize
     */

    for(int i=0;i<5;i++){
        Json::Value rootToken;
        char data[100];
        snprintf(data,100,"This is my house that want to token %d",i);
        rootToken["tokengroup"]      = "group1";
        rootToken["tokentemplate"]   = "token_alphanum";
        rootToken["data"]            = data;
        token.append(rootToken);
    }

    
    /**
     * do tokenize and parse the results
     */

    if(hitTheUrl(token_url, username_token, password_token, response, token)){
        u_int size_token = response.size();
        for(int i=0;i<size_token;i++){
            char print_token[100];
            int max_len_token = sizeof print_token;
            const char *tokenString = response[i]["token"].asCString();
            snprintf(print_token,max_len_token,"index = [%d] token = [%s] \n",i, tokenString);
            cout << print_token;

            
            /**
              * try to construct json to perform detokenization
              */
            Json::Value rootDetoken;
            rootDetoken["tokengroup"]      = "group1";
            rootDetoken["tokentemplate"]   = "token_alphanum";
            rootDetoken["token"]            = tokenString;
            detoken.append(rootDetoken);

        }
    }



    /**
      * do detokenize and parse the results
      */ 
    
    if(hitTheUrl(detoken_url, username_detoken, password_detoken, response, detoken)) {
        u_int size_detoken = response.size();
        for(int i=0;i<size_detoken;i++) {
            char print_detoken[100];
            int max_len_detoken = sizeof print_detoken;
            const char *dataString = response[i]["data"].asCString();
            snprintf(print_detoken, max_len_detoken, "index = [%d] data = [%s] \n", i, dataString);
            cout << print_detoken;
        }
    }




    return 0;
}