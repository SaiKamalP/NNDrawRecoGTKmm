#pragma once
#include<gtkmm.h>
#include<vector>
using namespace std;
class DrawingArea : public Gtk::DrawingArea{
    public:
    vector<double> pixelValues;
    double pointer_down_position_x,pointer_down_position_y;
    double dimension;
    DrawingArea();
    virtual ~DrawingArea();
    void clear();
    protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

    void on_pointer_down(double x,double y);
    void on_pointer_draw(double x,double y);

    void measure_vfunc(Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
        int& minimum_baseline, int& natural_baseline) const override;
};