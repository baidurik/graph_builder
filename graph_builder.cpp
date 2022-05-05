
#include "graph_area.h"
#include "graph_area.cpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>


int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    Gtk::Window graph;

    graph.resize(900, 900);

    GraphArea area;
    graph.add(area);
    area.show();

    return app->run(graph);
}