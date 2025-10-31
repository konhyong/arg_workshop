#include <iostream>
#include <vector>

#include "al/app/al_App.hpp"
#include "al/graphics/al_BufferObject.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_VAOMesh.hpp"

using namespace al;

struct MyApp : App {
  VAOMesh mesh;
  BufferObject buffer;
  std::vector<Vec3f> positions;
  double phase = 0;

  void onCreate() override
  {
    addTetrahedron(mesh);
    mesh.update();
    lens().near(0.1).far(25).fovy(45);
    nav().pos(0, 0, 4);
    nav().quat().fromAxisAngle(0. * M_2PI, 0, 1, 0);

    positions.reserve(100);
    for (unsigned int i = 0; i < 100; ++i) {
      positions.emplace_back(0, 0, 0.5f * i);
    }

    buffer.bufferType(GL_ARRAY_BUFFER);
    buffer.usage(GL_DYNAMIC_DRAW);

    buffer.create();

    buffer.bind();
    for (int i = 0; i < 4; ++i) {
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), 0);
      glEnableVertexAttribArray(1);
      glVertexAttribDivisor(1, 1);
    }

    buffer.data(positions.size() * sizeof(Vec3f), positions.data());
    buffer.unbind();
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
    g.polygonLine();
    g.pushMatrix();
    g.rotate(phase * 360, 0, 1, 0);
    g.color(1);
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
