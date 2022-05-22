
#include "graph_window.h"
#include "graph_window.cpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

#include <iostream>
#include <math.h>

double integral_start = 0;

double a = 0;
double b = 10;
double x_0 = 9;

int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    GraphWindow graph;

    graph.area.iter.push_back(x_0);
    graph.area.set_interval(a, b);



    // for (double c : area.iter) std::cout << c << " ";
    // std::cout << area.iter.size();

    return app->run(graph);
}