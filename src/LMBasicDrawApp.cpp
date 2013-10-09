#include "cinder/app/AppNative.h"
#include "cinder/BSpline.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/CinderMath.h"
#include "Leap.h"

using namespace ci;
using namespace ci::app;
using namespace std;

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
  vector<Vec2f>	_currentpoints;
  vector<BSpline2f> _splines;
  int _splinedegree;
};

LMBasicDrawApp::LMBasicDrawApp()
  :_windowWidth(1024),
   _windowHeight(768),
   _currentBrushSize(5.0f),
   _currentPressure(0.0f),
   _splinedegree(3)
{
}

LMBasicDrawApp::~LMBasicDrawApp()
{
}

void LMBasicDrawApp::setup()
{
  setWindowSize(_windowWidth, _windowHeight);
  setFrameRate(60);
}

void LMBasicDrawApp::draw()
{
  // clear to the background color
  cairo::Context ctx( cairo::createWindowSurface() );
  ctx.setSourceRgb( 0.96f, 0.96f, 0.88f );
  ctx.paint();

  Leap::InteractionBox iBox = _leap.frame().interactionBox();
  Leap::PointableList pointables = _leap.frame().pointables();

  // only use the 1st pointable
  if(pointables.count() >= 1)
  {
    Leap::Pointable pointable = pointables[0]; // get first tool
    Leap::Vector normalizedPosition = iBox.normalizePoint(pointable.stabilizedTipPosition());
    float x = normalizedPosition.x * _windowWidth;
    float y = _windowHeight - normalizedPosition.y * _windowHeight;
    float z = pointable.tipPosition().z;

    _currentPressure = -(z-10.0f);
    console() << "current pressure = " << _currentPressure << endl;
    drawCursor(Vec2f(x, y), ctx);

    if(_currentPressure <= 0.0f) // hovering
    {
      size_t numofpoints = _currentpoints.size();
      if(numofpoints>2)
      {
        int degree = (numofpoints>(size_t)_splinedegree) ? _splinedegree : numofpoints-1;
        _splines.push_back(BSpline2f(_currentpoints, degree, false, true));
        _currentpoints.clear();
      }      
    }
    else // drawing
    {
      _currentpoints.push_back(Vec2f(x, y));
    }
  }
  drawSplines(ctx);
}

void LMBasicDrawApp::resize()
{
  _windowWidth = getWindowWidth();
  _windowHeight = getWindowHeight();
}

void LMBasicDrawApp::drawCursor(const Vec2f &pos, cairo::Context &ctx)
{
  float alpha = math<float>::clamp((0.8f / 75.0f) * fabs(_currentPressure));
  //console() << "alpha = " << alpha << endl;
  float radius = _currentBrushSize*2.0f;
  if(_currentPressure <= 0.0f) // hovering
  {
    ctx.setSourceRgba(1.0f, 0.0f, 0.0f, alpha);
    ctx.newSubPath();
    ctx.circle(pos, radius);
    ctx.fill();

    ctx.setSourceRgba(1.0f, 0.0f, 0.0f, 0.8f);
    ctx.newSubPath();
    ctx.circle(pos, radius);
    ctx.stroke();
  }
  else // touching
  {    
    ctx.setSourceRgba(0.0f, 1.0f, 0.0f, alpha);
    ctx.newSubPath();
    ctx.circle(pos, radius);
    ctx.fill();

    ctx.setSourceRgba(0.0f, 1.0f, 0.0f, 0.8f);
    ctx.newSubPath();
    ctx.circle(pos, radius);
    ctx.stroke();
  }  
}

void LMBasicDrawApp::drawSpline(const BSpline2f &spline, cairo::Context &ctx)
{
  ctx.setLineWidth(_currentBrushSize);
  ctx.setSourceRgb(0.0f, 0.0f, 0.0f);
  ctx.appendPath(Path2d(spline));
  ctx.stroke();
}

void LMBasicDrawApp::drawSplines(cairo::Context& ctx)
{
  size_t numofpoints = _currentpoints.size();
  if(numofpoints>2)
  {
    int degree = (numofpoints>(size_t)_splinedegree) ? _splinedegree : numofpoints-1;
    drawSpline(BSpline2f(_currentpoints, degree, false, true), ctx);
  }

  for(size_t i=0; i<_splines.size(); ++i)
  {
    drawSpline(_splines[i], ctx);
  }
}

void LMBasicDrawApp::keyDown( KeyEvent event )
{
  if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
    quit();
  }
  if(event.getChar() == 'f') { // toggle fullscreen
    setFullScreen(!isFullScreen());
  }
  if(event.getChar() == 'x') {
    _splines.clear();
    _currentpoints.clear();
  }
}

CINDER_APP_NATIVE( LMBasicDrawApp, Renderer2d )
