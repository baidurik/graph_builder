#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <gtkmm.h>
#include "graph_area.h"
#include "graph_area.cpp"

class GraphWindow : public Gtk::Window {

    double eps1 = 1e-3, eps2 = 1e-3;

public:
    GraphWindow();
    virtual ~GraphWindow();
    GraphArea area;

protected:

    //Child widgets:
    Gtk::Grid container;
    Gtk::Grid ui;
    Gtk::Entry a_entry;
    Gtk::Entry b_entry;
    Gtk::Entry x0_entry;
    Gtk::Entry eps1_entry;
    Gtk::Entry eps2_entry;
    Gtk::Button redraw_btn;
    Gtk::Button nxt_btn;
    Gtk::Button prv_btn;

    void on_nxt_clicked();
    void on_prv_clicked();
};

#endif