#include "graph_area.h"
#include <cairomm/context.h>

GraphArea::GraphArea() {}
GraphArea::~GraphArea() {}

bool GraphArea::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int xc = width / 2, yc = height / 2;

    ctx->set_line_width(2.0);

    ctx->set_source_rgb(1.0, 0.0, 0.0);
    ctx->move_to(0, 0);
    ctx->line_to(xc, yc);
    ctx->line_to(0, height);
    ctx->move_to(xc, yc);
    ctx->line_to(width, yc);
    ctx->stroke();

    return true;
}