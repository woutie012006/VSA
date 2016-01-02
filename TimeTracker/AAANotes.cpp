    //How to call the treeview model

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_percentage] = 15;
    row[m_Columns.m_col_name] = "Buy milk";

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_percentage] = 40;
    row[m_Columns.m_col_name] = "Do Laboratory #2 &#3 on WP";

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_percentage] = 70;
    row[m_Columns.m_col_name] = "Do other laboratory Works";