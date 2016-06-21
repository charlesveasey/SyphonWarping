#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.width = 1280*2;
    settings.height = 800;
    settings.setPosition(ofVec2f(0,0));
    settings.setGLVersion(3, 2);
    settings.windowMode = OF_FULLSCREEN;
    settings.multiMonitorFullScreen = true;
    auto mainWindow = ofCreateWindow(settings);
    auto mainApp = make_shared<ofApp>();
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
	ofRunApp(new ofApp());
}
