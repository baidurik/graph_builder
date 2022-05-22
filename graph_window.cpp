#include "graph_window.h"
#include <gtkmm/messagedialog.h>
#include <iostream>

GraphWindow::GraphWindow() : redraw_btn("Redraw"), prv_btn("<"), nxt_btn(">") {
    container.set_orientation(Gtk::ORIENTATION_VERTICAL);

    container.add(area);

    prv_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_prv_clicked));
    nxt_btn.signal_clicked().connect(sigc::mem_fun(*this, &GraphWindow::on_nxt_clicked));

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

    add(container);
    show_all_children();
}

GraphWindow::~GraphWindow() {}

void GraphWindow::on_prv_clicked() {
    if (area.iter.size() <= 1) return;
    area.iter.pop_back();
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
}