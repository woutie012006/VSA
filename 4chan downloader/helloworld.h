#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <stdio.h>
#include <curl/curl.h>

class HelloWorld : public Gtk::Window
{

public:
  HelloWorld();
  virtual ~HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //methods
  size_t write_data(void, size_t , size_t , FILE );
  int get_json(std::string);
  int get_image(std::string);

  //Member widgets:
  Gtk::Button button_download;
  Gtk::Entry txt_board;
  Gtk::Entry txt_thread;
  Gtk::Box m_box;
};

#endif // HELLOWORLD_H
