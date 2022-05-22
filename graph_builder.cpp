
#include "graph_window.h"
#include "graph_window.cpp"

#include "mathematics.cpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

#include <iostream>
#include <math.h>

double f(double x) {
    return x * x - 4;
}

double f_stroke(double x) {
    return 2 * x;
}

double a = 0;
double b = 10;
double x_0 = 9;

double eps2 = 1e-3;


int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    GraphWindow graph;

    graph.area.iter.push_back(x_0);
    graph.area.f = f;
    graph.area.f_stroke = f_stroke;
    graph.area.set_interval(a, b);

    // for (double c : area.iter) std::cout << c << " ";
    // std::cout << area.iter.size();

    return app->run(graph);
}