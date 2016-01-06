#include "helloworld.h"
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
#include <string>
#include "rapidjson/document.h"
#include <fstream>
#include <stdio.h>
#include <cstdio>

using namespace rapidjson;

HelloWorld::HelloWorld()
:   m_box(Gtk::ORIENTATION_VERTICAL),
    button_download("Get all images")   // creates a new button with label "Hello World".

{
  add(m_box);//main_box

  set_size_request(500, 100);
  set_title("Image downloader");
  set_border_width(10);

  //add(m_VBox);
  button_download.set_size_request(10,10);
  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  button_download.signal_clicked().connect(sigc::mem_fun(*this,
              &HelloWorld::on_button_clicked));
  // This packs the button into the Window (a container).
  m_box.add(txt_board);
  m_box.add(txt_thread);
  m_box.add(button_download);

 txt_board.set_max_length(50);
 txt_board.set_text("Paste the board acronim in here");
 txt_board.select_region(0, txt_board.get_text_length());


  txt_thread.set_max_length(50);
  txt_thread.set_text("Paste the thread number in here");
  txt_thread.select_region(0, txt_thread.get_text_length());


  // The final step is to display this newly created widget...
  button_download.show();
  txt_board.show();
  txt_thread.show();

  m_box.show();

  show_all_children();
}

HelloWorld::~HelloWorld()
{
  //do nothing on destuction
}



void HelloWorld::on_button_clicked()
{
  std::cout << "Getting all images" << std::endl;
  std::string board = txt_board.get_text();
  std::string thread = txt_thread.get_text();

  std::cout << board <<"-" << thread<<std::endl;
  std::string JsonLink = "http://a.4cdn.org/" + board + "/thread/" + thread + ".json";
  std::cout <<"JsonLink:"<<JsonLink << std::endl;
  get_json(JsonLink);
  parse_json(board);
}



void HelloWorld::get_json(std::string file_url) {

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
}



void HelloWorld::get_image(std::string board,  std::string tim,  std::string ext, std::string filename, std::string folder) {

  CURL *curl;
  FILE *fp;
  CURLcode res;

  std::string web_url = "http://i.4cdn.org/" +board+"/"+tim + ext;
  std::cout<<web_url<<std::endl;
  char *url = const_cast<char*>(web_url.c_str());

  char outfilename[FILENAME_MAX] =  "testfile";

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
   std::string new_name= "./"+folder+"/"+filename + ext;

   char new_file_name[100];
   for (int i=0;i<=new_name.size();i++)
   {
       new_file_name[i]=new_name[i];
   }

   rename( oldname , new_file_name );

}


size_t HelloWorld::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


void HelloWorld::parse_json(std::string board){
   std::string line,text;
   std::ifstream in("./test.json");
   while(std::getline(in, line))
   {
       text += line + "\n";
   }

  Document document;
  document.Parse<0>(text.c_str());

  rapidjson::Value& post = document["posts"];
  std::string tim;
  int k =0;
   std::string temp = RemoveSpecialCharacters(post[k]["sub"].GetString());

  system(("mkdir ./" + temp + "/").c_str());

  for (SizeType i = 0; i < post.Size(); i++) {
    if(post[i].HasMember("filename")){

      std::cout << "now getting image" << std::endl;
      tim = std::to_string(post[i]["tim"].GetDouble());
      tim = tim.substr(0, tim.find("."));
      get_image(board, tim, post[i]["ext"].GetString(), post[i]["filename"].GetString(), temp);
    }
  }


}

std::string HelloWorld::RemoveSpecialCharacters(std::string str) {
   std::string s;
   for (char & c : str) {
      if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '.' || c == '_') {

         s.push_back(c);
      }
   }
   return s;
}
