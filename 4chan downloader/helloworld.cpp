#include "helloworld.h"
#include <iostream>
#include <gtkmm/stock.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <thread>
#include <unistd.h>
#include <gtkmm.h>
#include <stdio.h>
#include <curl/curl.h>

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
  std::string JsonLink = "http://a.4cdn.org/" + board + "/" + thread + "/threadnumber.json"
  get_file(JsonLink);
  

}

int get_file(std::string file_url) {

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = file_url;
    char outfilename[FILENAME_MAX] = "./test.html";
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

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
