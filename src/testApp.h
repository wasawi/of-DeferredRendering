//  testApp.h
//
//  Created by James Acres on 12-08-15
//  http://www.jamesacres.com
//  http://github.com/jacres
//  @jimmyacres

#pragma once

#include "ofMain.h"
#include "gBuffer.h"
#include "ssaoPass.h"
#include "pointLight.h"
#include "primitives.h"
#include "ofxFBX.h"

class testApp : public ofBaseApp {

  struct Box {
    ofVec3f pos;
    float size;
    float angle;
    float axis_x;
    float axis_y;
    float axis_z;

    Box(ofVec3f pos=ofVec3f(0.0f, 0.0f, 0.0f), float angle=0.0f, float ax=0.0f, float ay=0.0f, float az=0.0f, float size=2.0f) :
      pos(pos),
      size(size),
      angle(angle),
      axis_x(ax),
      axis_y(ay),
      axis_z(az)
    {}
  };

  static const int skNumBoxes = 50;
  static const int skNumLights = 100;
  static const int skRadius = 20;
  static const int skMaxPointLightRadius = 8;

  enum TEXTURE_UNITS {
    TEX_UNIT_ALBEDO,
    TEX_UNIT_NORMALS_DEPTH,
    TEX_UNIT_SSAO,
    TEX_UNIT_POINTLIGHT_PASS,
    TEX_UNIT_NUM_UNITS
  };

public:
  testApp();

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  void setupModel();
  void setupLights();
  void setupScreenQuad();
  void setupPointLightPassFbo();
  void resizeBuffersAndTextures();

  void addRandomLight();
  void createRandomBoxes();
  void randomizeLightColors();

  void unbindGBufferTextures();
  void bindGBufferTextures();

  void drawScreenQuad();

  void geometryPass();
  void pointLightStencilPass();
  void pointLightPass();
  void deferredRender();
	
  GBuffer m_gBuffer;
  SSAOPass m_ssaoPass;

  ofVbo m_quadVbo;

  ofShader m_shader;
  ofShader m_pointLightPassShader;
  ofShader m_pointLightStencilShader;

  ofEasyCam m_cam;

  ofImage m_texture;

  GLuint m_textureUnits[TEX_UNIT_NUM_UNITS];

  ofVbo  m_sphereVbo;
  int    m_numSphereVerts;

  ofVbo  m_boxVbo;
  int    m_numBoxVerts;

  float   m_angle;

  bool    m_bDrawDebug;
  bool    m_bPulseLights;

  int     m_windowWidth;
  int     m_windowHeight;

  vector<Box> m_boxes;
  vector<PointLight> m_lights;
	
	//______j
	void drawScene();
	vector<ofLight*>      OFlights;
	/// 3d MODEL
    ofxFBXScene             fbx;
    vector<ofxFBXMesh*>     meshes;
    vector<ofxFBXLight*>    lights;
    vector<ofxFBXNode*>     nulls;

	// params
    ofParameter <bool> p_renderSolid;
	ofParameter <float> p_lightAttConstant;
    ofParameter <float> p_lightAttLinear;
    ofParameter <float> p_lightAttQuadratic;

};
