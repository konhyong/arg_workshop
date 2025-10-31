#include <iostream>

#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"

using namespace al;

struct MyApp : App {
  Mesh mesh;
  double phase = 0;

  void onCreate() override
  {
    mesh.primitive(Mesh::TRIANGLE_STRIP);
    mesh.vertex(-1.f, -1.f, 0);
    mesh.vertex(1.f, -1.f, 0);
    mesh.vertex(-1.f, 1.f, 0);
    mesh.vertex(1.f, 1.f, 0);
    mesh.texCoord(0, 0);
    mesh.texCoord(1, 0);
    mesh.texCoord(0, 1);
    mesh.texCoord(1, 1);
    mesh.color(1, 0, 0);
    mesh.color(1, 1, 0);
    mesh.color(0, 0, 1);
    mesh.color(0, 1, 1);

    // addTetrahedron(mesh);
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);
  }

  void onAnimate(double dt) override
  {
    double period = 10;
    phase += dt / period;
    if (phase >= 1.) phase -= 1.;
  }

  void onDraw(Graphics& g) override
  {
    g.clear(0, 0, 0);
    // g.polygonLine();
    g.pushMatrix();
    g.rotate(phase * 360, 0, 1, 0);
    // g.color(1);
    g.meshColor();
    g.draw(mesh);
    g.popMatrix();
  }
};

int main()
{
  MyApp app;
  app.dimensions(600, 400);
  app.start();
}
