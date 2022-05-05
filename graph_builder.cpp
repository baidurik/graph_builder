
#include "graph_area.h"
#include "graph_area.cpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <math.h>

double f(double x) {
    return 3*cos(x) + 2 * sin(x);
}

double a = -7.1;
double b = -0.5;


int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    Gtk::Window graph;
    GraphArea area;

    area.set_f(f);
    area.set_interval(a, b);

    graph.resize(1010, 1010);

    graph.add(area);
    area.show();

    return app->run(graph);
}