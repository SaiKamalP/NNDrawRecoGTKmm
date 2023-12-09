#include "window.h"

int main(int argc,char **argv){
    auto application=Gtk::Application::create("com.saikamal.nntest.org");
    application->make_window_and_run<Window>(argc,argv);
}