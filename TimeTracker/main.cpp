#include "mainwindow.h"
#include <gtkmm.h>

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.wouterv");

  MainWindow window;

  //Shows the window and returns when it is closed.
  return app->run(window);
}
