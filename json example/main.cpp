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

int get_image(std::string board,  std::string tim,  std::string ext, std::string filename) {

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
   std::string new_name= "./test/"+filename + ext;

   char new_file_name[100];
   for (int i=0;i<=new_name.size();i++)
   {
       new_file_name[i]=new_name[i];
   }

   rename( oldname , new_file_name );
    return 0;
}

void parse_json(std::string board){

  system("mkdir ./test/");


   std::string line,text;
   std::ifstream in("./test.json");
   while(std::getline(in, line))
   {
       text += line + "\n";
   }

  Document document;
  document.Parse<0>(text.c_str());

  Value& post = document["posts"];
  std::string tim;
  for (SizeType i = 0; i < post.Size(); i++) {
    if(post[i].HasMember("filename")){

      std::cout << "now getting image" << std::endl;
      tim = std::to_string(post[i]["tim"].GetDouble());
      tim = tim.substr(0, tim.find("."));
      get_image(board, tim, post[i]["ext"].GetString(), post[i]["filename"].GetString());
    }
  }


}





int main() {
  std::string board = "wg";
  std::string thread = "6431912";
  std::string json_link = "http://a.4cdn.org/" + board + "/thread/" + thread + ".json";
  get_json(json_link);
  //get_image("wg",  "1449884662622", ".jpg" );
  parse_json("wg");
  return 0;
}
