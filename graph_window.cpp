#include "graph_window.h"
#include <gtkmm/messagedialog.h>
#include <iostream>

GraphWindow::GraphWindow() : redraw_btn("Redraw"), prv_btn("<"), nxt_btn(">") {
    container.set_orientation(Gtk::ORIENTATION_VERTICAL);

    container.add(area);

    prv_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_prv_clicked));
    nxt_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_nxt_clicked));
    redraw_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_redraw_clicked));

    answer_entry.set_editable(false);
    answer_entry.set_placeholder_text("answer");
    a_entry.set_placeholder_text("a");
    b_entry.set_placeholder_text("b");
    x0_entry.set_placeholder_text("x0");
    eps1_entry.set_placeholder_text("eps1");
    eps2_entry.set_placeholder_text("eps2");

    ui.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    ui.add(a_entry);
    ui.add(b_entry);
    ui.add(x0_entry);
    ui.add(eps1_entry);
    ui.add(eps2_entry);
    ui.add(redraw_btn);
    ui.add(prv_btn);
    ui.add(nxt_btn);
    container.add(ui);
    container.add(answer_entry);

    add(container);
    show_all_children();
}

GraphWindow::~GraphWindow() {}

void GraphWindow::set_eps1(double _eps1) {
    eps1 = _eps1;
}

void GraphWindow::set_eps2(double _eps2) {
    eps2 = _eps2;
}

void GraphWindow::on_prv_clicked() {
    if (area.iter.size() <= 1) return;
    area.iter.pop_back();
    answer_entry.set_text(std::to_string(area.iter.back()));
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
}

void GraphWindow::on_redraw_clicked() {
    set_eps1(std::stod(eps1_entry.get_text()));
    set_eps2(std::stod(eps2_entry.get_text()));
    area.set_interval(std::stod(a_entry.get_text()), std::stod(b_entry.get_text()));
    while (!area.iter.empty()) area.iter.pop_back();
    area.iter.push_back(std::stod(x0_entry.get_text()));

    area.force_redraw();
}