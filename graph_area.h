#ifndef GRAPH_AREA_H
#define GRAPH_AREA_H

#include <gtkmm/drawingarea.h>

class GraphArea : public Gtk::DrawingArea {
    public:
    GraphArea();
    virtual ~GraphArea();

    protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
};


#endif