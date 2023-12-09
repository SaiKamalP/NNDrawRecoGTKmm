#include "window.h"
#include<iostream>
using namespace std;
Window::Window(){
    set_title("NN for doodle predection");
    set_default_size(600,500);

    //have a horizontal box
    auto h_box=Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL,10);
    set_child(*h_box);

    //add the drawing area to the h_box
    drawingArea=Gtk::make_managed<DrawingArea>();
    drawingArea->set_hexpand(true);
    h_box->append(*drawingArea);

    //add a veritcal box to the h_box
    auto v_box=Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL,10);
    h_box->append(*v_box);

    //add a clear button to the v_box
    auto clearButton=Gtk::make_managed<Gtk::Button>("Clear");
    v_box->append(*clearButton);
    clearButton->signal_clicked().connect(sigc::mem_fun(*drawingArea,&DrawingArea::clear));

    //add the guess button to the v_boc
    auto guessButton=Gtk::make_managed<Gtk::Button>("Guess");
    v_box->append(*guessButton);
    guessButton->signal_clicked().connect(sigc::mem_fun(*this,&Window::guess));
}

Window::~Window(){

}

void Window::guess(){
    vector<double> out=numberGuesserNN.guess(drawingArea->pixelValues);
    double m=-1;
    int ans=0;
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
            if(drawingArea->pixelValues[i*28+j]>0.5){
                cout<<"@";
            }
            else{
                cout<<".";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<10;i++){
        cout<<i<<":"<<out[i]<<" ";
        if(m<out[i]){
            m=out[i];
            ans=i;
        }
    }
    cout<<endl;
    cout<<"I think it should be "<<ans<<endl;
}