#include "helloworld.h"
#include "helloworld.cpp"
#include <gtkmm/application.h>

int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    HelloWorld helloworld;

    return app->run(helloworld);
}