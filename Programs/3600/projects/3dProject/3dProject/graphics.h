#pragma once
enum viewtype { top_view, perspective_view, rat_view };
enum DIRECTIONS { NORTH, SOUTH, EAST, WEST };


void SetPerspectiveView(int w, int h);
void SetTopView(int w, int h);


void DrawLine(double x1, double y1, double x2, double y2);
void DrawQuad(int x1, int y1, int x2, int y2);
void InitializeMyStuff();
void DrawCircle(double x, double y, double r);
void DrawTriangle(double x, double y, double height, double width, double length, double idk);