#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Person.h"
using namespace std;

Gtk::Window* pDialog = nullptr;
Gtk::TextView* textview= nullptr;

static
void on_button_clicked()
{
  if(pDialog)
    cout<<"Hello there";
    pDialog->hide(); //hide() will cause main::run() to end.
}
void on_button2_clicked()
{
    cout<<"Button 2 Clicked-"<<endl;

   ofstream outputFile;
    outputFile.open("test.txt", fstream::in | fstream::out | fstream::app);
    outputFile<<textview->get_buffer()->get_text()<<endl;
    //outputFile<<system("ps -ef")<<endl;
    outputFile.close();
}

void on_button3_clicked()
{
    cout<<"Button3 clicked-"<<endl;
    ofstream outputFile;
    outputFile.open("test.txt");

    FILE *fp;
    char path[1035];

    /* Open the command for reading. */
    fp = popen("ps -ef | grep VSCode", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        outputFile<<path;
    }
     /* close */
    pclose(fp);
    outputFile.close();

    //opens test.txt and reads the amount of lines
    ifstream f("test.txt");
    string line;
    int i=0;
    for (i = 0; std::getline(f, line); ++i);
    if(i>2){
        cout<<"it's running"<<i<<endl;
    }else{
        cout<<"nooooooo"<<endl;
    }
    f.close();



}









int main (int argc, char **argv)
{

    Person p(10);
    cout<<p.get_id()<<endl;





  cout <<endl<< endl<< argc <<"----" << **argv <<endl;
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  //Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("basic2.glade");
  }
  catch(const Glib::FileError& ex)
  {
    cerr << "FileError: " << ex.what() << endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    cerr << "MarkupError: " << ex.what() << endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    cerr << "BuilderError: " << ex.what() << endl;
    return 1;
  }

  //Get the GtkBuilder-instantiated Dialog:
  refBuilder->get_widget("window1", pDialog);
  if(pDialog)
  {
    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    Gtk::Button* p1Button = nullptr;
    refBuilder->get_widget("button1", p1Button);
    if(p1Button)
    {
      p1Button->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }
    // //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    Gtk::Button* p2Button = nullptr;
    refBuilder->get_widget("button2", p2Button);
    if(p2Button)
    {
      p2Button->signal_clicked().connect( sigc::ptr_fun(on_button3_clicked) );
    }
    refBuilder->get_widget("textview1", textview);



    app->run(*pDialog);
  }

  delete pDialog;

  return 0;
}
