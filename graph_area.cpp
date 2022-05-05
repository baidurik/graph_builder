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

    // Fill all window with white color
    ctx->set_source_rgb(1, 1, 1);
    ctx->move_to(0, 0);
    ctx->rectangle(0, 0, width, height);                            
    ctx->fill();

    // Draw borders
    int x1 = 30, y1 = 30, x2 = width - 30, y2 = height - 30;

    ctx->set_line_width(2);
    ctx->set_source_rgb(0, 0, 0);
    ctx->move_to(x1, y1);
    ctx->line_to(x2, y1);
    ctx->line_to(x2, y2);                                           
    ctx->line_to(x1, y2);
    ctx->line_to(x1, y1);
    ctx->stroke();

    // Find min and max value of f(x) on the given interval
    double max_y = f(a);
    double min_y = f(a);

    for (int canvas_x = 0; canvas_x < (x2 - x1); canvas_x++) {
        double real_x = a + (b - a)  / (x2 - x1) * canvas_x;           
        max_y = std::max(max_y, f(real_x));
        min_y = std::min(min_y, f(real_x));
    }

    double scope = max_y - min_y;

    // If function is a horizontal line
    if (scope == 0) {
        scope = 2;
        max_y++;                                                                                               
        min_y--;
    }

    // Drawing the graph
    ctx->set_line_width(2);
    ctx->set_source_rgb(1, 0, 0);
    double y0 = y2 - (f(a) - min_y) / scope * (y2 - y1);
    ctx->move_to(x1, y0);
    for (int canvas_x = 0; canvas_x < (x2 - x1); canvas_x++) {      
        double real_x = a + (b - a) / (x2 - x1) * canvas_x;
        double real_y = f(real_x);
        double canvas_y = (y2 - y1) - (real_y - min_y) / scope * (y2 - y1);
        ctx->line_to(x1 + canvas_x, y1 + canvas_y);
    }
    ctx->stroke();

    // Draw axes if possible
    ctx->set_source_rgb(0, 0, 0);
    int oy_axis = x1;
    if (a <= 0 && 0 <= b) {
        double oy_on_canvas = x1 + (0 - a) / (b - a) * (x2 - x1);
        ctx->move_to(oy_on_canvas, y1);
        ctx->line_to(oy_on_canvas, y2);
        ctx->stroke();
        oy_axis = oy_on_canvas;
    }

    int ox_axis = y2;
    if (min_y <= 0 && 0 <= max_y) {
        double ox_on_canvas = y2 - (0 - min_y) / scope * (y2 - y1);
        ctx->move_to(x1, ox_on_canvas);
        ctx->line_to(x2, ox_on_canvas);
        ctx->stroke();
        ox_axis = ox_on_canvas;
    }

    // Some strokes on axes/borders
    ctx->set_source_rgb(0, 0, 0);
    for (int i = x1 + 100; i < x2; i += 100) {                           
        ctx->move_to(i, ox_axis - 5);
        ctx->line_to(i, ox_axis + 5);
        ctx->stroke();
    }
    for (int i = y1 + 100; i < y2; i += 100) {
        ctx->move_to(oy_axis - 5, i);
        ctx->line_to(oy_axis + 5, i);
        ctx->stroke();
    }

    return true;
}