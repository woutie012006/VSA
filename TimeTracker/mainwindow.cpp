    #include "mainwindow.h"
    #include <gtkmm/stock.h>
    #include <iostream>
    #include <fstream>
    #include <math.h>
    #include "unit.h"
    #include <thread>
    #include <unistd.h>
    MainWindow::MainWindow()
    :
    d_Box(Gtk::ORIENTATION_VERTICAL),
    h1_Box(Gtk::ORIENTATION_HORIZONTAL),
    h2_Box(Gtk::ORIENTATION_HORIZONTAL),
    h3_Box(Gtk::ORIENTATION_HORIZONTAL),

    m_adjustment( Gtk::Adjustment::create(0, 0, 100, 1, 1))
    //m_HScale(m_adjustment, Gtk::ORIENTATION_HORIZONTAL)
    {

      //std::thread t1(check_running);

    set_title("Time Tracker");
    set_default_size(800, 400);
    set_icon_from_file(iconpath);
    add(d_Box);

        //add h2_Box to main box
        d_Box.add(h2_Box);
        h2_Box.set_vexpand(false);

        //set and add entry to box
        txt_code->set_text("Code");
        set_focus_child(*txt_code);
        txt_code->select_region(0, txt_code->get_text_length());
        txt_code->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_text_changed));
        h2_Box.pack_start(*txt_code, true, true, 5);

        //set and add entry to box
        txt_description->set_text("Description");
        set_focus_child(*txt_description);
        txt_description->select_region(0, txt_description->get_text_length());
        txt_description->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_text_changed));
        h2_Box.pack_start(*txt_description, true, true, 5);

        //add Entry button
        btn_add->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_addEntry_clicked));
        h2_Box.pack_start(*btn_add, false, true, 5);

        Glib::ustring someTask = "some task";
        //add Button which saves editing
        btn_saveEdit->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onSaveEdit_clicked));
        btn_saveEdit->set_sensitive(false);
        h2_Box.pack_start(*btn_saveEdit, false, true, 5);

        btn_delete->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_delete_clicked));
        btn_delete->set_sensitive(false);
        h2_Box.pack_start(*btn_delete, false, true, 5);

        //add check running button
        btn_check->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::check_running));
        h2_Box.pack_start(*btn_check, false, true, 5);


        //Add the TreeView, inside a ScrolledWindow:
        m_ScrolledWindow.add(m_TreeView);

        //Only show the scrollbars when they are necessary:
        m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_TreeView.set_model(m_refTreeModel);

        //set selection listener on list
        m_refTreeSelection = m_TreeView.get_selection();
        m_refTreeSelection->signal_changed().connect( sigc::mem_fun(*this, &MainWindow::on_selection_changed));

    //Add the TreeView's view columns:
    //This number will be shown with the default numeric formatting.
    m_TreeView.append_column("Time spent", m_Columns.m_col_time);
    m_TreeView.append_column("Code", m_Columns.m_col_code);
    m_TreeView.append_column("Description", m_Columns.m_col_description);

    //Make all the columns reorderable:
    for(guint i = 0; i <= 2; i++)
    {
        Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
        pColumn->set_reorderable();
    }

        d_Box.add(h3_Box);

        h3_Box.set_vexpand(true);

    h3_Box.pack_start(m_ScrolledWindow, true, true, 5);

    show_all_children();
    }
















    MainWindow::~MainWindow()
    {
    }

    void MainWindow::on_addEntry_clicked() {

        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_time] = 0;
        row[m_Columns.m_col_code] = txt_code->get_text();
        row[m_Columns.m_col_description] = txt_description->get_text();
    }


    void MainWindow::on_selection_changed()
    {
        any_row_selected = true;

        btn_saveEdit->set_sensitive(true);
        btn_delete->set_sensitive(true);

        Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
        Gtk::TreeModel::Row row = *iter;
        //get data from selected row
        Glib::ustring task_string = row.get_value(m_Columns.m_col_description);
        std::string selected_percentage = row.get_value(m_Columns.m_col_code);
        unsigned int selected_id = row.get_value(m_Columns.m_col_time);

        txt_description->set_text(task_string);
    }

    void MainWindow::onSaveEdit_clicked()
    {
        btn_saveEdit->set_sensitive(false);

        Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
        Gtk::TreeModel::Row row = *iter;

        Glib::ustring new_entry = txt_description->get_text();
        row.set_value(m_Columns.m_col_description, new_entry);

        Glib::ustring new_entry2 = txt_code->get_text();
        row.set_value(m_Columns.m_col_code, new_entry2);

        timeSpent[new_entry] = 0;

        //std::cout << new_percentage << std::endl;
    }

    void MainWindow::on_delete_clicked()
    {
        Gtk::TreeModel::iterator store_iter = m_refTreeSelection->get_selected();
        m_refTreeModel->erase(store_iter);
    }

    void MainWindow::on_text_changed()
    {
        bool is_button_active = btn_saveEdit->get_sensitive();

        if(any_row_selected && !is_button_active) {
            btn_saveEdit->set_sensitive(true);
        }

        std::cout << "text has changed" << std::endl;
    }

    void MainWindow::on_scale_changed()
    {
        bool is_button_active = btn_saveEdit->get_sensitive();

        if(any_row_selected && !is_button_active) {
        btn_saveEdit->set_sensitive(true);
        }
    }

    void MainWindow::check_running()
    {

      int counter = 0;
      //while(true){


      typedef Gtk::TreeModel::Children type_children;
      type_children children = m_refTreeModel->children();

      for(auto iter = children.begin();  iter != children.end(); ++iter){

          Gtk::TreeModel::Row row = *iter;//dereferencing it so i can actually use it and not the pointer
          counter = row[m_Columns.m_col_time];//////////////////////
          std::cout << "counter start of loop :"<<counter << std::endl;
          Glib::ustring code = row.get_value(m_Columns.m_col_code);


            //using a file purely so i learned how to read and write
            //to files
            std::ofstream outputFile;
            outputFile.open("test.txt");

            FILE *fp;
            char path[1035];

            /* Open the command for reading. */
            fp = popen(("ps -ef | grep -i " + code).c_str(), "r");

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
            std::ifstream f("test.txt");
            std::string line;
            int i=0;
            for (i = 0; std::getline(f, line); ++i);
            f.close();

            std::cout << "counter before counting lines :"<<counter << std::endl;
            bool running=false;
            //this needs to be higher than 2 because  grep spawns a new command
            if(i>2){
                running = true;
            }else{
            //    running = false; //redundant
                ++counter;
            }
            std::cout << "counter after counting lines :"<<counter << std::endl;
            row[m_Columns.m_col_time] =counter ;

      }
    // }

}
