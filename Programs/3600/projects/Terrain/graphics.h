#pragma once
enum viewtype { top_view, perspective_view, rat_view };
//double hoverHeight;


void SetPerspectiveView(int w, int h);
void SetTopView(int w, int h);

double function(double x, double y);

double GetTime();
void Interpolate(double t, double t0, double t1, double & v, double v0, double v1);

void DrawQuad(int x1, int y1, int x2, int y2);
void InitializeMyStuff();
void DrawCircle(double x, double y, double r);
void DrawTriangle(double x, double y, double height, double width, double length, double idk);