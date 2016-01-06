#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include "unit.h"
#include <map>

#include <thread>

class MainWindow : public Gtk::Window
{
public:
  MainWindow();

    static const std::vector<Unit> units;

    Gtk::Label *topText = Gtk::manage(new Gtk::Label());
    Gtk::Label *topTextRight = Gtk::manage(new Gtk::Label());
    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    Gtk::Entry *txt_description = Gtk::manage(new Gtk::Entry());
    Gtk::Entry *txt_code = Gtk::manage(new Gtk::Entry());
    Gtk::Button *btn_add = Gtk::manage(new Gtk::Button("Add New Task"));
    Gtk::Button *btn_saveEdit = Gtk::manage(new Gtk::Button("Save Edit"));
    Gtk::Button *btn_delete = Gtk::manage(new Gtk::Button("Delete Task"));
    Gtk::Button *btn_check = Gtk::manage(new Gtk::Button("Check Running"));
    Gtk::TreeViewColumn* pColumn = Gtk::manage(new Gtk::TreeViewColumn);
    Glib::RefPtr<Gtk::AccelGroup> group = Gtk::AccelGroup::create();
    Glib::RefPtr<Gtk::Adjustment> m_adjustment;
  virtual ~MainWindow();

protected:
  //Signal handlers:

  void on_addEntry_clicked();
  void onSaveEdit_clicked();
  void on_selection_changed();
  void on_delete_clicked();
  void on_text_changed();
  void on_scale_changed();
  void onRefresh_clicked();
  //Methods
  void check_running();

  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    {
      add(m_col_time);
      add(m_col_code);
      add(m_col_description);
    }

    Gtk::TreeModelColumn<unsigned int> m_col_time;
    Gtk::TreeModelColumn<Glib::ustring> m_col_code;
    Gtk::TreeModelColumn<Glib::ustring> m_col_description;
  };

  ModelColumns m_Columns;

  bool any_row_selected = false;

  //Child widgets:

  Gtk::Box d_Box;
  Gtk::Box h1_Box;
  Gtk::Box h2_Box;
  Gtk::Box h3_Box;
  Gtk::EventBox event_box;
  Gtk::Label m_Label;
  //Gtk::Scale m_HScale;
  Gdk::Pixbuf *pixmap;
  std::string iconpath="icon.png";
  std::map<std::string,int> timeSpent;



  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  Gtk::TreeModel::Row row;

  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;
};

#endif //MAINWINDOW_H
