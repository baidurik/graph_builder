#ifndef GRAPH_AREA_H
#define GRAPH_AREA_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

class GraphArea : public Gtk::DrawingArea {

    double (*f)(double x);
    double a, b;

    double find_optimal_range(double a, double b);

    public:
    GraphArea();
    virtual ~GraphArea();
    void set_interval(double a, double b);
    void set_f(double f(double));

    protected:
    void draw_number(const Cairo::RefPtr<Cairo::Context>& ctx, int x, int y, double num, int axis);
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
};


#endif