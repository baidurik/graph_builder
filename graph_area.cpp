#include "graph_area.h"
#include <cairomm/context.h>

#include <assert.h>
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>

GraphArea::GraphArea() {}
GraphArea::~GraphArea() {}

double GraphArea::x_real_to_canvas(double x) {
    return x1 + (x - a) / (b - a) * (x2 - x1);
}

double GraphArea::x_canvas_to_real(double x) {
    return a + (b - a)  / (x2 - x1) * x;
}

double GraphArea::y_real_to_canvas(double y) {
    return y2 - (y - min_y) / (max_y - min_y) * (y2 - y1);
}

void GraphArea::set_interval(double a, double b) {
    assert(a < b);
    this->a = a;
    this->b = b;
}

void GraphArea::set_f(double _f(double)) {
    f = _f;
}

double GraphArea::find_optimal_range(double a, double b) {  // Smartly computing the interval between two strokes
    double tenth = (b - a) / 10;

    double p10_low_val = 1;
    int p10_low = 0;
    while (p10_low_val >= tenth) {
        p10_low_val /= 10;
        p10_low--;
    }
    while (p10_low_val <= tenth) {
        p10_low_val *= 10;
        p10_low++;
    }
    p10_low--;
    p10_low_val /= 10;

    double ans = p10_low_val;
    if (std::abs(2 * p10_low_val - tenth) < std::abs(ans - tenth)) ans = 2 * p10_low_val;
    if (std::abs(2.5 * p10_low_val - tenth) < std::abs(ans - tenth)) ans = 2.5 * p10_low_val;
    if (std::abs(5 * p10_low_val - tenth) < std::abs(ans - tenth)) ans = 5 * p10_low_val;
    if (std::abs(10 * p10_low_val - tenth) < std::abs(ans - tenth)) ans = 10 * p10_low_val;

    return ans;
}

void GraphArea::draw_number(const Cairo::RefPtr<Cairo::Context>& ctx, int x, int y, double num, int axis=0) {
    Pango::FontDescription font;

    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);
    // font.set_size(1);

    num = std::round(num * 1000000) / 1000000.0;
    std::ostringstream ss;
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
    const double eps = 1e-9;

    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // Fill background with white
    ctx->set_source_rgb(1, 1, 1);
    ctx->move_to(0, 0);
    ctx->rectangle(0, 0, width, height);                            
    ctx->fill();

    // Draw borders
    x1 = 90, y1 = 20, x2 = width - 20, y2 = height - 90;
    ctx->set_line_width(2);
    ctx->set_source_rgb(0, 0, 0);
    ctx->rectangle(x1, y1, x2 - x1, y2 - y1);
    ctx->stroke();

    // Find min and max value of f(x) on the given interval
    max_y = f(a);
    min_y = f(a);

    for (int canvas_x = 0; canvas_x < (x2 - x1); canvas_x++) {
        double real_x = x_canvas_to_real(canvas_x);           
        max_y = std::max(max_y, f(real_x));
        min_y = std::min(min_y, f(real_x));
    }

    // If function is a horizontal line
    if (max_y == min_y) {
        max_y++;                                                                                               
        min_y--;
    }

    // Drawing the graph
    ctx->set_line_width(2);
    ctx->set_source_rgb(1, 0, 0);
    double y0 = y_real_to_canvas(f(a));
    ctx->move_to(x1, y0);
    for (int canvas_x = 0; canvas_x < (x2 - x1); canvas_x++) {      
        double real_x = x_canvas_to_real(canvas_x);
        double real_y = f(real_x);
        double canvas_y = y_real_to_canvas(real_y);
        ctx->line_to(x1 + canvas_x, canvas_y);
    }
    ctx->stroke();

    // Draw axes if possible
    ctx->set_source_rgb(0, 0, 0);
    int oy_axis = x1;
    if (a <= 0 && 0 <= b) {
        double oy_on_canvas = x_real_to_canvas(0);
        ctx->move_to(oy_on_canvas, y1);
        ctx->line_to(oy_on_canvas, y2);
        ctx->stroke();
        oy_axis = oy_on_canvas;
    }

    int ox_axis = y2;
    if (min_y <= 0 && 0 <= max_y) {
        double ox_on_canvas = y_real_to_canvas(0);
        ctx->move_to(x1, ox_on_canvas);
        ctx->line_to(x2, ox_on_canvas);
        ctx->stroke();
        ox_axis = ox_on_canvas;
    }    

    // Some strokes and labels on borders
    // Also grid

    double x_int = find_optimal_range(a, b);
    double first_stroke_x = x_int * std::ceil(a / x_int);
    for (double real_x = first_stroke_x; real_x <= b + eps; real_x += x_int) {     
        double canvas_x = x_real_to_canvas(real_x);
        ctx->set_line_width(2);
        ctx->set_source_rgb(0, 0, 0);
        ctx->move_to(canvas_x, y2 - 5);
        ctx->line_to(canvas_x, y2 + 5);
        ctx->stroke();

        draw_number(ctx, canvas_x, y2, real_x, 1);

        ctx->set_line_width(0.5);
        ctx->set_source_rgb(0.6, 0.6, 0.6);
        ctx->move_to(canvas_x, y1);
        ctx->line_to(canvas_x, y2);
        ctx->stroke();
    }

    double y_int = find_optimal_range(min_y, max_y);
    double first_stroke_y = y_int * std::ceil(min_y / y_int);
    for (double real_y = first_stroke_y; real_y <= max_y + eps; real_y += y_int) {
        double canvas_y = y_real_to_canvas(real_y);
        ctx->set_line_width(2);
        ctx->set_source_rgb(0, 0, 0);
        ctx->move_to(x1 - 5, canvas_y);
        ctx->line_to(x1 + 5, canvas_y);
        ctx->stroke();      

        draw_number(ctx, x1, canvas_y, real_y, 0);

        ctx->set_line_width(0.5);
        ctx->set_source_rgb(0.6, 0.6, 0.6);
        ctx->move_to(x1, canvas_y);
        ctx->line_to(x2, canvas_y);
        ctx->stroke();
    }

    // Animating Newton method

    ctx->set_source_rgb(0, 0, 1);
    ctx->set_line_width(1);
    double axis_pos = y_real_to_canvas(0);
    ctx->move_to(x_real_to_canvas(iter[0]), axis_pos);
    ctx->line_to(x_real_to_canvas(iter[0]), y_real_to_canvas(f(iter[0])));
    for (int i = 1; i < (int)iter.size(); i++) {
        ctx->line_to(x_real_to_canvas(iter[i]), axis_pos);
        ctx->line_to(x_real_to_canvas(iter[i]), y_real_to_canvas(f(iter[i])));
    }

    ctx->stroke();

    return true;
}