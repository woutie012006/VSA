    #include "mainwindow.h"
    #include <gtkmm/stock.h>
    #include <iostream>
    #include <fstream>
    #include <math.h>
    #include "unit.h"

    MainWindow::MainWindow()
    :
    d_Box(Gtk::ORIENTATION_VERTICAL),
    h1_Box(Gtk::ORIENTATION_HORIZONTAL),
    h2_Box(Gtk::ORIENTATION_HORIZONTAL),
    h3_Box(Gtk::ORIENTATION_HORIZONTAL),

    m_adjustment( Gtk::Adjustment::create(0, 0, 100, 1, 1)),
    m_HScale(m_adjustment, Gtk::ORIENTATION_HORIZONTAL)
    {
    set_title("Time Tracker");
    set_default_size(800, 400);
    set_icon_from_file(iconpath);
    add(d_Box);


    /*  //initially it was supposed to be a text between menu and entry. Later it was removed
        d_Box.add(h1_Box);
        h1_Box.set_vexpand(false);
        topText->set_text("Make you own TODO List");
        h1_Box.pack_start(*topText, true, true, 5);
    */
        //add h2_Box to main box
        d_Box.add(h2_Box);
        h2_Box.set_vexpand(false);

    //set and add entry to box
        todo_entry->set_text("add Items");
        set_focus_child(*todo_entry);
        todo_entry->set_text(todo_entry->get_text() + " to TODO List");
        todo_entry->select_region(0, todo_entry->get_text_length());
        todo_entry->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_text_changed));
        h2_Box.pack_start(*todo_entry, true, true, 5);
        
      
        //set and add entry to box
        todo_entry2->set_text("add Items");
        set_focus_child(*todo_entry2);
        todo_entry2->set_text(todo_entry2->get_text() + " to TODO List");
        todo_entry2->select_region(0, todo_entry2->get_text_length());
        todo_entry2->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_text_changed));
        h2_Box.pack_start(*todo_entry2, true, true, 5);
        

        //add scrollbar percentage
        m_HScale.set_digits(1);
        m_HScale.set_value_pos(Gtk::POS_TOP);
        m_HScale.set_draw_value();
        m_HScale.set_digits(0);
        m_HScale.signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_scale_changed));
        h2_Box.pack_start(m_HScale, true, true, 5);

        //add Entry button
        b_add->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_addEntry_clicked));
        h2_Box.pack_start(*b_add, false, true, 5);

        Glib::ustring someTask = "some task";
        //add Button which saves editing
        b_saveEdit->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onSaveEdit_clicked));
        b_saveEdit->set_sensitive(false);
        h2_Box.pack_start(*b_saveEdit, false, true, 5);

        b_delete->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_delete_clicked));
        b_delete->set_sensitive(false);
        h2_Box.pack_start(*b_delete, false, true, 5);

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
    //set counter for rows
    count = 3;
    //Add the TreeView's view columns:
    //This number will be shown with the default numeric formatting.
    m_TreeView.append_column("ID", m_Columns.m_col_id);

    //Display a progress bar instead of a decimal number:
    Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
    int cols_count = m_TreeView.append_column("Task Completed", *cell);
    pColumn = m_TreeView.get_column(cols_count - 1);
    if(pColumn)
    {
        pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
    }

    m_TreeView.append_column("Task Description", m_Columns.m_col_name);

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
        count++;

        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_id] = count;
        std::cout<<row[m_Columns.m_col_id]<<std::endl;
        std::cout<<(check_running("vsc") ? "true" : "false")<<std::endl;
        row[m_Columns.m_col_name] = todo_entry->get_text();
        row[m_Columns.m_col_percentage] = m_HScale.get_value();
    }

    void MainWindow::add_entry(Glib::ustring task, int percentage)
    {
    std::cout << task << std::endl;
        std::cout << percentage << std::endl;
    }


    void MainWindow::on_selection_changed()
    {
        any_row_selected = true;

        b_saveEdit->set_sensitive(true);
        b_delete->set_sensitive(true);

        Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
        Gtk::TreeModel::Row row = *iter;
        //get data from selected row
        Glib::ustring task_string = row.get_value(m_Columns.m_col_name);
        int selected_percentage = row.get_value(m_Columns.m_col_percentage);
        unsigned int selected_id = row.get_value(m_Columns.m_col_id);

        todo_entry->set_text(task_string);
        double scale_value = (double) selected_percentage;
        m_HScale.set_value(scale_value);


    std::cout << selected_id << std::endl;
    }

    void MainWindow::onSaveEdit_clicked()
    {
        b_saveEdit->set_sensitive(false);

        Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected();
        Gtk::TreeModel::Row row = *iter;

        Glib::ustring new_entry = todo_entry->get_text();
        row.set_value(m_Columns.m_col_name, new_entry);
        int new_percentage = m_HScale.get_value();
        row.set_value(m_Columns.m_col_percentage, new_percentage);

    std::cout << new_percentage << std::endl;
    }

    void MainWindow::on_delete_clicked()
    {
        Gtk::TreeModel::iterator store_iter = m_refTreeSelection->get_selected();
        m_refTreeModel->erase(store_iter);
    }

    void MainWindow::on_text_changed()
    {
        bool is_button_active = b_saveEdit->get_sensitive();

        if(any_row_selected && !is_button_active) {
            b_saveEdit->set_sensitive(true);
        }

        std::cout << "text has changed" << std::endl;
    }

    void MainWindow::on_scale_changed()
    {
        bool is_button_active = b_saveEdit->get_sensitive();

        if(any_row_selected && !is_button_active) {
        b_saveEdit->set_sensitive(true);
        }
    }

    void MainWindow::on_help_clicked()
    {
        Gtk::MessageDialog dlg("Help", false,
                Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        dlg.set_title("Help Dialog");
        dlg.set_secondary_text("Add items to your TODO list by writing the task in the entry box, and then press Ctrl+S or button Add. ");
        dlg.run();
    }

    bool MainWindow::check_running(std::string code)
    {    
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
            
        //this needs to be higher than 2 because  grep spawns a new command 
        if(i>2){
            return 1;
        }else{
            return 0;
        }
    }


