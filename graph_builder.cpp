
#include "graph_area.h"
#include "graph_area.cpp"
#include "mathematics.cpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>

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
    
    Gtk::Window graph;
    GraphArea area;

    area.iter.push_back(x_0);
    area.set_f(f);
    area.set_interval(a, b);

    double nxt = x_0 - f(x_0) / f_stroke(x_0);
    while (abs(nxt - area.iter.back()) > eps2) {
        area.iter.push_back(nxt);
        nxt = area.iter.back() - f(area.iter.back()) / f_stroke(area.iter.back());
    }

    // for (double c : area.iter) std::cout << c << " ";
    // std::cout << area.iter.size();

    graph.resize(1010, 1010);

    graph.add(area);
    area.show();

    return app->run(graph);
}