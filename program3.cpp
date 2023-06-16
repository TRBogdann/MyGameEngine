#include "graphic_engine/PSBgraphics.h"
#include "graphic_engine/colors/color.h"
#include "graphic_engine/geometry/geometry.h"
#include "math_engine/PSBmath.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <vector>

bool A_isPressed = 0, W_isPressed = 0, S_isPressed = 0, D_isPressed = 0;
bool Left_isPressed = 0, Right_isPressed = 0;
bool arrowLeft_isPressed = 0, arrowRight_isPressed = 0, arrowDown_isPressed = 0,
     arrowUp_isPressed = 0;

Color cl = red;

void KeyDown(SDL_Event &event) {
  if (event.key.keysym.sym == SDLK_a)
    A_isPressed = 1;

  if (event.key.keysym.sym == SDLK_w)
    W_isPressed = 1;

  if (event.key.keysym.sym == SDLK_s)
    S_isPressed = 1;

  if (event.key.keysym.sym == SDLK_d)
    D_isPressed = 1;

  if (event.key.keysym.sym == SDLK_LEFT)
    arrowLeft_isPressed = 1;

  if (event.key.keysym.sym == SDLK_RIGHT)
    arrowRight_isPressed = 1;

  if (event.key.keysym.sym == SDLK_UP)
    arrowUp_isPressed = 1;

  if (event.key.keysym.sym == SDLK_DOWN)
    arrowDown_isPressed = 1;
}

void KeyUp(SDL_Event &event) {
  if (event.key.keysym.sym == SDLK_a)
    A_isPressed = 0;

  if (event.key.keysym.sym == SDLK_w)
    W_isPressed = 0;

  if (event.key.keysym.sym == SDLK_s)
    S_isPressed = 0;

  if (event.key.keysym.sym == SDLK_d)
    D_isPressed = 0;

  if (event.key.keysym.sym == SDLK_LEFT)
    arrowLeft_isPressed = 0;

  if (event.key.keysym.sym == SDLK_RIGHT)
    arrowRight_isPressed = 0;

  if (event.key.keysym.sym == SDLK_UP)
    arrowUp_isPressed = 0;

  if (event.key.keysym.sym == SDLK_DOWN)
    arrowDown_isPressed = 0;
}

struct triangle3d {
  Math::vec3f p1;
  Math::vec3f p2;
  Math::vec3f p3;
};
struct Cube {
  std::vector<triangle3d> trig;
};
struct Piramid {
  std::vector<triangle3d> trig;
};

float fx = 400.0f, fy = 300.0f;

int main(int argc, char **argv) {
  Cube shape;
  shape.trig = {// Top
                {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
                {{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}},

                // Bottom
                {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
                {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

                // Front
                {{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

                // Back
                {{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
                {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

                // Left
                {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
                {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

                // Right
                {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
                {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}};

  Piramid pir;
  pir.trig = {// Front
              {{0.0f, 0.0f, 0.0f}, {0.5f, 1.0f, 0.5f}, {1.0f, 0.0f, 0.0f}},

              // Back
              {{1.0f, 0.0f, 1.0f}, {0.5f, 1.0f, 0.5f}, {0.0f, 0.0f, 1.0f}},

              // Left
              {{0.0f, 0.0f, 1.0f}, {0.5f, 1.0f, 0.5f}, {0.0f, 0.0f, 0.0f}},

              // Right
              {{1.0f, 0.0f, 0.0f}, {0.5f, 1.0f, 0.5f}, {1.0f, 0.0f, 1.0f}},

              // Bottom
              {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
              {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}

  };

  float a = 600.0f / 800.0f;
  float d1 = 0.01f;
  float d2 = 1000.0f;
  float angle = 90.0f;
  Math::vec3f origin(0.5f, 0.5f, 2.5f);
  Math::vec3f originPir(0, 0, 0);
  originPir += {1.0f, 0.0f, 0.0f};
  originPir += {1.0f, 0.0f, 1.0f};
  originPir += {0.0f, 0.0f, 1.0f};
  originPir += {0.5f, 1.0f, 0.5f};
  originPir /= 5;

  for (int i = 0; i < 12; i++) {
    shape.trig[i].p1.z += 2.0f;
    shape.trig[i].p2.z += 2.0f;
    shape.trig[i].p3.z += 2.0f;
  }

  for (int i = 0; i < 6; i++) {
    pir.trig[i].p1.z += 2.0f;
    pir.trig[i].p2.z += 2.0f;
    pir.trig[i].p3.z += 2.0f;
  }
  originPir.z += 2.0f;

  for (int i = 0; i < 6; i++) {
    pir.trig[i].p1 = Math::rotationVec3f(pir.trig[i].p1 - originPir,
                                         {0.0f, 0.0f, 1.0f}, 180) +
                     originPir;
    pir.trig[i].p2 = Math::rotationVec3f(pir.trig[i].p2 - originPir,
                                         {0.0f, 0.0f, 1.0f}, 180) +
                     originPir;
    pir.trig[i].p3 = Math::rotationVec3f(pir.trig[i].p3 - originPir,
                                         {0.0f, 0.0f, 1.0f}, 180) +
                     originPir;
  }

  SDL_Event event;

  Window window("My Window", 800, 600);

  while (!window.isClosed()) {

    window.pollEvents(event);

    if (1)
      KeyDown(event);

    if (event.type == SDL_KEYUP)
      KeyUp(event);

    if (D_isPressed) {
      cl = green;
      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1.x -= 0.001f;
        shape.trig[i].p2.x -= 0.001f;
        shape.trig[i].p3.x -= 0.001f;
      }

      for (int i = 0; i < 6; i++) {
        pir.trig[i].p1.x -= 0.001f;
        pir.trig[i].p2.x -= 0.001f;
        pir.trig[i].p3.x -= 0.001f;
      }

      origin.x -= 0.001f;
      originPir.x -= 0.001f;
    }

    if (A_isPressed) {
      cl = orange;
      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1.x += 0.001f;
        shape.trig[i].p2.x += 0.001f;
        shape.trig[i].p3.x += 0.001f;
      }

      for (int i = 0; i < 6; i++) {
        pir.trig[i].p1.x += 0.001f;
        pir.trig[i].p2.x += 0.001f;
        pir.trig[i].p3.x += 0.001f;
      }
      origin.x += 0.001f;
      originPir.x += 0.001f;
    }

    if (W_isPressed) {
      cl = red;
      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1.z -= 0.001f;
        shape.trig[i].p2.z -= 0.001f;
        shape.trig[i].p3.z -= 0.001f;
      }

      for (int i = 0; i < 6; i++) {
        pir.trig[i].p1.z -= 0.001f;
        pir.trig[i].p2.z -= 0.001f;
        pir.trig[i].p3.z -= 0.001f;
      }

      origin.z -= 0.001f;
      originPir.z -= 0.001f;
    }

    if (S_isPressed) {
      cl = blue;
      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1.z += 0.001f;
        shape.trig[i].p2.z += 0.001f;
        shape.trig[i].p3.z += 0.001f;
      }

      for (int i = 0; i < 6; i++) {
        pir.trig[i].p1.z += 0.001f;
        pir.trig[i].p2.z += 0.001f;
        pir.trig[i].p3.z += 0.001f;
      }
      origin.z += 0.001f;
      originPir.z += 0.001f;
    }

    if (arrowDown_isPressed) {
      cl = red;
      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1.y -= 0.001f;
        shape.trig[i].p2.y -= 0.001f;
        shape.trig[i].p3.y -= 0.001f;
      }

      for (int i = 0; i < 6; i++) {
        pir.trig[i].p1.y -= 0.001f;
        pir.trig[i].p2.y -= 0.001f;
        pir.trig[i].p3.y -= 0.001f;
      }

      origin.y -= 0.001f;
      originPir.y -= 0.001f;
    }

    if (arrowUp_isPressed) {
      cl = blue;
      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1.y += 0.001f;
        shape.trig[i].p2.y += 0.001f;
        shape.trig[i].p3.y += 0.001f;
      }

      for (int i = 0; i < 6; i++) {
        pir.trig[i].p1.y += 0.001f;
        pir.trig[i].p2.y += 0.001f;
        pir.trig[i].p3.y += 0.001f;
      }
      origin.y += 0.001f;
      originPir.y += 0.001f;
    }

    if (arrowRight_isPressed) {

      /*
        for(int i=0;i<12;i++)
        {
          shape.trig[i].p1=Math::rotationVec3f(shape.trig[i].p1-origin,
        {0.0f,0.0f,1.0f}, 0.1)+origin;
          shape.trig[i].p2=Math::rotationVec3f(shape.trig[i].p2-origin,
        {0.0f,0.0f,1.0f}, 0.1)+origin;
          shape.trig[i].p3=Math::rotationVec3f(shape.trig[i].p3-origin,
        {0.0f,0.0f,1.0f}, 0.1)+origin;
        }
      */

      for (int i = 0; i < 12; i++) {
        shape.trig[i].p1 = Math::rotationVec3f(shape.trig[i].p1 - origin,
                                               {0.0f, 1.0f, 0.0f}, 0.01) +
                           origin;
        shape.trig[i].p2 = Math::rotationVec3f(shape.trig[i].p2 - origin,
                                               {0.0f, 1.0f, 0.0f}, 0.01) +
                           origin;
        shape.trig[i].p3 = Math::rotationVec3f(shape.trig[i].p3 - origin,
                                               {0.0f, 1.0f, 0.0f}, 0.01) +
                           origin;
      }
    }

    for (int i = 0; i < 12; i++)
      if (shape.trig[i].p1.z > d1)
        if (shape.trig[i].p2.z > d1)
          if (shape.trig[i].p3.z > d1) {
            Math::vec2f p1, p2, p3;

            Math::Matrix m1 =
                Math::persProjection3f(shape.trig[i].p1, angle, d1, d2, a);
            Math::Matrix m2 =
                Math::persProjection3f(shape.trig[i].p2, angle, d1, d2, a);
            Math::Matrix m3 =
                Math::persProjection3f(shape.trig[i].p3, angle, d1, d2, a);

            p1 = Math::vec2f(m1.mData[0], m1.mData[1]);
            p2 = Math::vec2f(m2.mData[0], m2.mData[1]);
            p3 = Math::vec2f(m3.mData[0], m3.mData[1]);

            Math::scalevec2f(p1, 800.0f, 600.0f);
            Math::scalevec2f(p2, 800.0f, 600.0f);
            Math::scalevec2f(p3, 800.0f, 600.0f);

            Math::vec3f line1 = shape.trig[i].p2 - shape.trig[i].p1;
            Math::vec3f line2 = shape.trig[i].p3 - shape.trig[i].p1;
            Math::vec3f normal = Math::VectorCrossProduct3D(line1, line2);

            p1 += {window.getWidth() / 2, window.getHeight() / 2};
            p2 += {window.getWidth() / 2, window.getHeight() / 2};
            p3 += {window.getWidth() / 2, window.getHeight() / 2};
            Shape::Triangle t(p1, p2, p3);
            t.setFill(orange);
            if (normal * shape.trig[i].p1 < 0.0f) {
              window.drawShape(t);
              if (i % 2 == 0) {
                window.drawline(p1.x, p1.y, p2.x, p2.y, white);
                window.drawline(p2.x, p2.y, p3.x, p3.y, white);
              }
              if (i % 2 == 1) {
                window.drawline(p2.x, p2.y, p3.x, p3.y, white);
                window.drawline(p3.x, p3.y, p1.x, p1.y, white);
              }
            }
          }

    for (int i = 0; i < 6; i++)
      if (pir.trig[i].p1.z > d1)
        if (pir.trig[i].p2.z > d1)
          if (pir.trig[i].p3.z > d1) {
            Math::vec2f p1, p2, p3;

            Math::Matrix m1 =
                Math::persProjection3f(pir.trig[i].p1, angle, d1, d2, a);
            Math::Matrix m2 =
                Math::persProjection3f(pir.trig[i].p2, angle, d1, d2, a);
            Math::Matrix m3 =
                Math::persProjection3f(pir.trig[i].p3, angle, d1, d2, a);

            p1 = Math::vec2f(m1.mData[0], m1.mData[1]);
            p2 = Math::vec2f(m2.mData[0], m2.mData[1]);
            p3 = Math::vec2f(m3.mData[0], m3.mData[1]);

            Math::scalevec2f(p1, 800.0f, 800.0f);
            Math::scalevec2f(p2, 800.0f, 800.0f);
            Math::scalevec2f(p3, 800.0f, 800.0f);
            Math::vec3f line1 = pir.trig[i].p2 - pir.trig[i].p1;
            Math::vec3f line2 = pir.trig[i].p3 - pir.trig[i].p1;
            Math::vec3f normal = Math::VectorCrossProduct3D(line1, line2);

            p1 += {window.getWidth() / 2, window.getHeight() / 2 - 200.0f};
            p2 += {window.getWidth() / 2, window.getHeight() / 2 - 200.0f};
            p3 += {window.getWidth() / 2, window.getHeight() / 2 - 200.0f};

            Shape::Triangle t(p1, p2, p3);
            t.setFill(cl);

            if (normal * pir.trig[i].p1 < 0.0f) {
              window.drawShape(t);
              window.drawline(p1.x, p1.y, p2.x, p2.y, white);
              window.drawline(p2.x, p2.y, p3.x, p3.y, white);
              window.drawline(p3.x, p3.y, p1.x, p1.y, white);
            }
          }

    window.clear();
  }

  return 0;
}
