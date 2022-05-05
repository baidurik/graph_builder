
#include "graph_area.h"
#include "graph_area.cpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>

double f(double x) {
    return x * x;
}

double a = 0;
double b = 1;


int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    Gtk::Window graph;
    GraphArea area;

    area.set_f(f);
    area.set_interval(a, b);

    graph.resize(900, 900);

    graph.add(area);
    area.show();

    return app->run(graph);
}