#include "unit.h"
    
    Unit::Unit (int id){
        this->id = id;
    }
        
    int Unit::get_id(){
        return id;
    }
    int Unit::get_minutes(){
        return minutes;
    }
