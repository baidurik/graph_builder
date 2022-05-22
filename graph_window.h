#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <gtkmm.h>
#include "graph_area.h"
#include "graph_area.cpp"

double eps1 = 1e-3;

class GraphWindow : public Gtk::Window {

public:
    GraphWindow();
    virtual ~GraphWindow();
    GraphArea area;
    double eps2 = 1e-3;

protected:

    Gtk::Grid container;

    Gtk::Grid input;
    Gtk::Entry a_entry;
    Gtk::Entry b_entry;
    Gtk::Entry x0_entry;
    Gtk::Entry eps1_entry;
    Gtk::Entry eps2_entry;
    Gtk::Button redraw_btn;
    Gtk::Button nxt_btn;
    Gtk::Button prv_btn;

    Gtk::Grid output;
    Gtk::Entry answer_entry;
    Gtk::Entry f_entry;

    void on_nxt_clicked();
    void on_prv_clicked();
    void on_redraw_clicked();
};

#endif