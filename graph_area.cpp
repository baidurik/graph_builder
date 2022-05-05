#include "graph_area.h"
#include <cairomm/context.h>
#include <assert.h>

#include <math.h>
#include <iostream>

GraphArea::GraphArea() {}
GraphArea::~GraphArea() {}

void GraphArea::set_interval(double a, double b) {
    assert(a < b);
    this->a = a;
    this->b = b;
}

void GraphArea::set_f(double _f(double)) {
    f = _f;
}

bool GraphArea::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    double max_y = f(a);
    double min_y = f(a);

    for (int i = 0; i < width; i++) {
        double x = a + ((b - a) * (double)i / width);
        max_y = std::max(max_y, f(x));
        min_y = std::min(min_y, f(x));
    }

    double scope = max_y - min_y;

    ctx->set_line_width(2.0);
    ctx->set_source_rgb(1.0, 0.0, 0.0);

    if (scope == 0) {

    }
    else {
        ctx->move_to(0, height);
        for (int canvas_x = 0; canvas_x < width; canvas_x++) {
            double real_x = a + ((b - a) / width) * canvas_x;
            double real_y = f(real_x);
            double canvas_y = height - (real_y - min_y) / (max_y - min_y) * height;
            ctx->line_to(canvas_x, canvas_y);
        }
    }
    ctx->stroke();

    return true;
}