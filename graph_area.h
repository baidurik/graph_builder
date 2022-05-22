#ifndef GRAPH_AREA_H
#define GRAPH_AREA_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <vector>

class GraphArea : public Gtk::DrawingArea {

    double a, b;
    double x1, y1, x2, y2, min_y, max_y;

    double x_real_to_canvas(double x);
    double x_canvas_to_real(double x);
    double y_real_to_canvas(double y);

    double find_optimal_range(double a, double b);

    public:
    double (*f)(double x);
    double (*f_stroke)(double x);

    GraphArea();
    virtual ~GraphArea();
    void set_interval(double a, double b);
    void force_redraw();

    std::vector<double> iter;

    protected:
    void draw_number(const Cairo::RefPtr<Cairo::Context>& ctx, int x, int y, double num, int axis);
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
};


#endif