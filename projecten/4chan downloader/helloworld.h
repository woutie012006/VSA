#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <stdio.h>
#include <curl/curl.h>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <cstring>
#include <string>

class HelloWorld : public Gtk::Window
{

public:
  HelloWorld();
  virtual ~HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //methods
  void get_json(std::string);
  void get_image(std::string,  std::string,  std::string, std::string,std::string);
  void parse_json(std::string);
  static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) ;
  std::string RemoveSpecialCharacters(std::string);
  //Member widgets:
  Gtk::Button button_download;
  Gtk::Entry txt_board;
  Gtk::Entry txt_thread;
  Gtk::Box m_box;
};

#endif // HELLOWORLD_H
