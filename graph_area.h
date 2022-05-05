#ifndef GRAPH_AREA_H
#define GRAPH_AREA_H

#include <gtkmm/drawingarea.h>

class GraphArea : public Gtk::DrawingArea {

    double (*f)(double x);
    double a, b;

    public:
    GraphArea();
    virtual ~GraphArea();
    void set_interval(double a, double b);
    void set_f(double f(double));

    protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
};


#endif