#pragma once

#include "Leap.h"
#include "cinder/app/AppNative.h"
#include "cinder/BSpline.h"
#include "cinder/cairo/Cairo.h"

using namespace ci;
using namespace ci::app;

class LMBasicDrawApp : public AppNative
{
public:
  LMBasicDrawApp();
  virtual ~LMBasicDrawApp();
  virtual void setup();
	virtual void draw();
  
  virtual void resize();
  virtual void keyDown( KeyEvent event );
  
private:
  void drawCursor(const Vec2f &pos, cairo::Context& ctx);
  void drawSpline(const BSpline2f &spline, cairo::Context &ctx);
  void drawSplines(cairo::Context &ctx);
  
  
  int _windowWidth;
  int _windowHeight;
  Leap::Controller _leap;
  float _currentBrushSize;
  float _currentPressure;
  std::vector<Vec2f>	_currentpoints;
  std::vector<BSpline2f> _splines;
  int _splinedegree;
};
