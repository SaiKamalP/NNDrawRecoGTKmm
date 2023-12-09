#pragma once
#include<gtkmm.h>
#include "NN.h"
#include "drawingArea.h"

class Window :public Gtk::Window{
    NN numberGuesserNN=NN::load("mnistTrained-p89.nnFile");
    DrawingArea *drawingArea;
    public:
    Window();
    virtual ~Window();

    void guess();
};