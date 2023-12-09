#include "drawingArea.h"

DrawingArea::DrawingArea(){
    pixelValues=vector<double>(784,0);
    auto controller=Gtk::GestureDrag::create();
    controller->signal_drag_begin().connect(sigc::mem_fun(*this,&DrawingArea::on_pointer_down));
    controller->signal_drag_update().connect(sigc::mem_fun(*this,&DrawingArea::on_pointer_draw));
    add_controller(controller);
    set_draw_func(sigc::mem_fun(*this,&DrawingArea::on_draw));
}

DrawingArea::~DrawingArea(){

}
void DrawingArea::clear(){
    for(auto &i:pixelValues){
        i=0;
    }
    queue_draw();
}
void DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height){
    //drawing a black background
    cr->move_to(0,0);
    cr->rectangle(0,0,width,height);
    cr->set_source_rgb(0,0,0);
    cr->fill();


    dimension=min(width,height)/28.0;
  
    // drawing the pixels
    cr->set_source_rgb(0.9,0.9,0.9);
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
            cr->move_to(j*dimension,i*dimension);
            cr->rectangle(j*dimension,i*dimension,dimension,dimension);
            double sourceColor=pixelValues[i*28+j];
            cr->set_source_rgb(sourceColor,sourceColor,sourceColor);
            cr->fill();
        }
    } 

    //drawing box outlines
    cr->set_source_rgb(0.1,0.1,0.1);
    cr->set_line_width(1);
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
            cr->move_to((i+1)*dimension,j*dimension);
            cr->line_to((i+1)*dimension,(j+1)*dimension);
            cr->line_to((i)*dimension,(j+1)*dimension);
            cr->stroke();
        }
    }

}
void DrawingArea::on_pointer_down(double x,double y){
    pointer_down_position_x=x;
    pointer_down_position_y=y;
}
void DrawingArea::on_pointer_draw(double x,double y){
    int px=(pointer_down_position_x+x)/dimension;
    int py=(pointer_down_position_y+y)/dimension;
    if(px>=0 && py>=0 && px<28 && py<28){
        if(pixelValues[py*28+px]!=1){
            pixelValues[py*28+px]=1;
            if(py+1<28){
                pixelValues[(py+1)*28+px]=max(pixelValues[(py+1)*28+px],0.75);
            }
            if(py-1>=0){
                pixelValues[(py-1)*28+px]=max(pixelValues[(py-1)*28+px],0.75);
            }
            if(px+1<28){
                pixelValues[py*28+px+1]=max(pixelValues[py*28+px+1],0.75);
            }
            if(px-1>=0){
                pixelValues[py*28+px-1]=max(pixelValues[py*28+px-1],0.75);
            }
            queue_draw();
        }
    }
}

void DrawingArea::measure_vfunc(Gtk::Orientation orientation, int for_size, int& minimum, int& natural,int& minimum_baseline, int& natural_baseline) const{
    minimum_baseline=-1;
    natural_baseline=-1;
    if(orientation==Gtk::Orientation::HORIZONTAL){
        minimum=500;
        natural=500;
    }
    else{
        minimum=500;
        natural=500;
    }

}