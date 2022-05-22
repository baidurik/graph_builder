#include "graph_window.h"
#include <gtkmm/messagedialog.h>
#include <iostream>
#include "mathematics.cpp"

double g(double x, double y) {
    return x * x + x * y + y * y - 17;
}

double g_stroke_x(double x, double y) {
    return 2 * x + y;
}

double f(double x) {
    auto g_1 = [x](double y){return g(x, y);};
    return integral(g_1, 0, 1, eps1);
}

double f_stroke(double x) {
    auto g_stroke_x_1 = [x](double y) {return g_stroke_x(x, y);};
    return integral(g_stroke_x_1, 0, 1, eps1);
}

GraphWindow::GraphWindow() : redraw_btn("Redraw"), prv_btn("<"), nxt_btn(">") {
    container.set_orientation(Gtk::ORIENTATION_VERTICAL);

    area.f = f;
    area.f_stroke = f_stroke;
    container.add(area);

    prv_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_prv_clicked));
    nxt_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_nxt_clicked));
    redraw_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_redraw_clicked));

    answer_entry.set_editable(false);
    f_entry.set_editable(false);
    answer_entry.set_placeholder_text("answer");
    f_entry.set_placeholder_text("f(answer)");
    a_entry.set_placeholder_text("a");
    b_entry.set_placeholder_text("b");
    x0_entry.set_placeholder_text("x0");
    eps1_entry.set_placeholder_text("eps1");
    eps2_entry.set_placeholder_text("eps2");

    input.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    input.add(a_entry);
    input.add(b_entry);
    input.add(x0_entry);
    input.add(eps1_entry);
    input.add(eps2_entry);
    input.add(redraw_btn);
    input.add(prv_btn);
    input.add(nxt_btn);
    container.add(input);

    output.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    output.add(answer_entry);
    output.add(f_entry);
    container.add(output);

    add(container);
    show_all_children();
}

GraphWindow::~GraphWindow() {}

void GraphWindow::on_prv_clicked() {
    if (area.iter.size() <= 1) return;
    area.iter.pop_back();
    answer_entry.set_text(std::to_string(area.iter.back()));
    f_entry.set_text(std::to_string(area.f(area.iter.back())));
    area.force_redraw();
}

void GraphWindow::on_nxt_clicked() {
    double nxt = area.iter.back() - area.f(area.iter.back()) / area.f_stroke(area.iter.back());
    if (abs(nxt - area.iter.back()) <= eps2) {
        Gtk::MessageDialog dialog(*this, "Hi, I'm the message dialog");
        dialog.set_secondary_text("Already found the root with required accuracy. Try to change eps2");
        dialog.run();
        return;
    }
    area.iter.push_back(nxt);
    answer_entry.set_text(std::to_string(area.iter.back()));
    f_entry.set_text(std::to_string(area.f(area.iter.back())));
}

void GraphWindow::on_redraw_clicked() {
    eps1 = std::stod(eps1_entry.get_text());
    eps2 = std::stod(eps2_entry.get_text());
    area.set_interval(std::stod(a_entry.get_text()), std::stod(b_entry.get_text()));
    while (!area.iter.empty()) area.iter.pop_back();
    area.iter.push_back(std::stod(x0_entry.get_text()));

    area.force_redraw();
}