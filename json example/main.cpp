#include "rapidjson/document.h"
#include <cstdio>
#include <iostream>
#include <gtkmm/stock.h>
#include <fstream>
#include <math.h>
#include <thread>
#include <unistd.h>
#include <gtkmm.h>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>
#include "rapidjson/document.h"
#include <string>
#include <fstream>

using namespace rapidjson;



size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
int get_json(std::string file_url) {

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = const_cast<char*>(file_url.c_str());
    char outfilename[FILENAME_MAX] = "./test.json";
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

int get_image(std::string board,  std::string tim,  std::string ext) {

  CURL *curl;
  FILE *fp;
  CURLcode res;

  std::string web_url = "http://i.4cdn.org/" +board+"/"+tim + ext;
  std::cout<<web_url<<std::endl;
  std::string local_url;
  char *url = const_cast<char*>(web_url.c_str());

  local_url ="./"+tim + ext;
  char outfilename[FILENAME_MAX] =  "testfile";
  //char *outfilename[FILENAME_MAX] =  local_url;



   curl = curl_easy_init();
   if (curl) {
       fp = fopen(outfilename,"wb");
       curl_easy_setopt(curl, CURLOPT_URL, url);
       curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
       curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
       res = curl_easy_perform(curl);
       curl_easy_cleanup(curl);
       fclose(fp);
   }
   char oldname[] ="testfile";
   std::string new_name= tim + ext;

   char new_file_name[100];
   for (int i=0;i<=new_name.size();i++)
   {
       new_file_name[i]=new_name[i];
   }

   rename( oldname , new_file_name );
    return 0;
}

// void parse_json(){
//
//
//
//
//
//
//    std::string line,text;
//    std::ifstream in("./test.json");
//    while(std::getline(in, line))
//    {
//        text += line + "\n";
//    }
//    const char* json[] = "{ \"hello\" : \"world\" }";
//    //const char* json = text.c_str();
//
//   Document document;
//   document.Parse(json);
//
//   const Value& a = document["hello"];
//
//   for (rapidjson::SizeType i = 0; i < a.Size(); i++)
//      {
//          const Value& c = a[i];
//
//          printf("%s \n",c["no"].GetString());
//      }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// }





int main() {
  std::string board = "wg";
  std::string thread = "6424505";
  std::string json_link = "http://a.4cdn.org/" + board + "/thread/" + thread + ".json";
  //get_json(json_link);
  get_image("wg",  "1449884662622", ".jpg" );
  //parse_json();
  return 0;
}
