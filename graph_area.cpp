#include "graph_area.h"
#include <cairomm/context.h>

#include <assert.h>
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>

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

void GraphArea::draw_number(const Cairo::RefPtr<Cairo::Context>& ctx, int x, int y, double num, int axis=0) {
    Pango::FontDescription font;

    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);
    // font.set_size(1);

    std::ostringstream ss;
    ss.precision(2);
    ss << num;

    Glib::RefPtr<Pango::Layout> layout = create_pango_layout(ss.str());

    layout->set_font_description(font);

    int text_width, text_height;
    layout->get_pixel_size(text_width, text_height);
    if (axis == 0) ctx->move_to(x - text_width - 10, y - text_height / 2);
    else ctx->move_to(x - text_width / 2, y + 10);

    layout->show_in_cairo_context(ctx);
}

bool GraphArea::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // Fill background with white
    ctx->set_source_rgb(1, 1, 1);
    ctx->move_to(0, 0);
    ctx->rectangle(0, 0, width, height);                            
    ctx->fill();

    // Draw borders
    int x1 = 90, y1 = 20, x2 = width - 20, y2 = height - 90;
    ctx->set_line_width(2);
    ctx->set_source_rgb(0, 0, 0);
    ctx->rectangle(x1, y1, x2 - x1, y2 - y1);
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

    // Some strokes and captions on borders
    ctx->set_source_rgb(0, 0, 0);
    for (int canvas_x = 0; canvas_x <= x2 - x1; canvas_x += 100) {                           
        ctx->move_to(canvas_x + x1, y2 - 5);
        ctx->line_to(canvas_x + x1, y2 + 5);
        ctx->stroke();
        double real_x = a + (b - a) / (x2 - x1) * canvas_x;

        draw_number(ctx, canvas_x + x1, y2, real_x, 1);
    }
    for (int canvas_y = 0; canvas_y <= y2 - y1; canvas_y += 100) {
        ctx->move_to(x1 - 5, y2 - canvas_y);
        ctx->line_to(x1 + 5, y2 - canvas_y);
        ctx->stroke();
        double real_y = min_y + (max_y - min_y) / (y2 - y1) * (y2 - y1 - canvas_y);

        draw_number(ctx, x1, y2 - canvas_y, real_y, 0);
    }

    return true;
}