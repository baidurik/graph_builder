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

    ctx->set_source_rgb(1, 1, 1);
    ctx->move_to(0, 0);
    ctx->rectangle(0, 0, width, height);
    ctx->fill();

    int x1 = 30, y1 = 30, x2 = width - 30, y2 = height - 30;

    ctx->set_line_width(2);
    ctx->set_source_rgb(0, 0, 0);
    ctx->move_to(x1, y1);
    ctx->line_to(x2, y1);
    ctx->line_to(x2, y2);
    ctx->line_to(x1, y2);
    ctx->line_to(x1, y1);
    ctx->stroke();

    double max_y = f(a);
    double min_y = f(a);

    for (int i = 0; i < width; i++) {
        double x = a + ((b - a) * (double)i / (x2 - x1));
        max_y = std::max(max_y, f(x));
        min_y = std::min(min_y, f(x));
    }

    double scope = max_y - min_y;

    ctx->set_line_width(2);
    ctx->set_source_rgb(1, 0, 0);

    if (scope == 0) {
        max_y++;
        min_y--;
    }

    double y0 = y2 - (f(a) - min_y) / scope * (y2 - y1);
    ctx->move_to(x1, y0);
    for (int canvas_x = 0; canvas_x < (x2 - x1); canvas_x++) {
        double real_x = a + ((b - a) / (x2 - x1)) * canvas_x;
        double real_y = f(real_x);
        double canvas_y = (y2 - y1) - (real_y - min_y) / scope * (y2 - y1);
        ctx->line_to(x1 + canvas_x, y1 + canvas_y);
    }
    ctx->stroke();

    return true;
}