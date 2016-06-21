#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = 1280;
    height = 800;
    
    ofHideCursor();
    //ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    ofBackground(0, 0, 0);
    ofEnableNormalizedTexCoords();
    ofEnableAlphaBlending();

    // syphon
    //mClient.set("","Simple Server");
    //mClient.set("","Render - Delicode_Z_Vector");
    mClient.setup();
    
    // warp
    mSettings = "settings.xml";
    
    mWarps.push_back( WarpBilinear::create() );
    mWarps.push_back( WarpBilinear::create() );
    
    Warp::setSize(mWarps, width, height);

    // load settings
    ofXml xml;
    if (xml.load(mSettings)){
        mWarps = Warp::readSettings( mSettings );
        Warp::setSize( mWarps, width, height );
    }

    // make plane
    makeMesh(mesh1);
    makeMesh(mesh2);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int i = 0;
    for( auto &warp : mWarps ){
        warp->begin();
        
        mClient.bind();

            mesh1.draw();
        
        mClient.unbind();

        warp->end();

        i++;
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofKeyEventArgs event;
    event.key = key;
    
    Warp::handleKeyDown(mWarps, event);
    
    switch(event.key){
        case 'w':
            // toggle warp edit mode
            mWarps[0]->enableEditMode(!mWarps[0]->isEditModeEnabled() );
            mWarps[1]->enableEditMode(!mWarps[1]->isEditModeEnabled() );
            break;
        case 115: // s
            Warp::writeSettings( mWarps, mSettings );
            break;
        case 108: // l
            mWarps.clear();
            mWarps = Warp::readSettings( mSettings );
            Warp::setSize( mWarps, width, height );
        case 'b':
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ofKeyEventArgs event;
    event.key = key;
    Warp::handleKeyUp(mWarps, event);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofMouseEventArgs event;
    event.set(x, y);
    event.button = button;
    mWarps[0]->handleMouseDown(mWarps, event);
    mWarps[1]->handleMouseDown(mWarps, event);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofMouseEventArgs event;
    event.set(x, y);
    event.button = button;
    mWarps[0]->handleMouseUp(mWarps, event);
    mWarps[1]->handleMouseUp(mWarps, event);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    ofMouseEventArgs event;
    event.set(x, y);
    event.button = button;
    mWarps[0]->handleMouseDrag(mWarps, event);
    mWarps[1]->handleMouseDrag(mWarps, event);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    ofMouseEventArgs event;
    event.set(x, y);
    mWarps[0]->handleMouseMove(mWarps, event);
    mWarps[1]->handleMouseMove(mWarps, event);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    //Warp::handleResize( mWarps );
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

//--------------------------------------------------------------
void ofApp::makeMesh(ofMesh &mesh){
    
    int rows = 4;
    int columns = 4;
    
    ofVec3f vert;
    ofVec3f normal(0, 0, 1);
    ofVec2f texcoord;
    
    // add the vertices //
    for(int iy = 0; iy < rows; iy++) {
        for(int ix = 0; ix < columns; ix++) {
            // normalized tex coords //
            texcoord.x = ((float)ix/((float)columns-1.f));
            texcoord.y = ((float)iy/((float)rows-1.f));
            
            vert.x = texcoord.x * width;
            vert.y = texcoord.y * height;
            
            mesh.addVertex(vert);
            mesh.addTexCoord(texcoord);
            mesh.addNormal(normal);
        }
    }
    
    // Triangles //
    for(int y = 0; y < rows-1; y++) {
        for(int x = 0; x < columns-1; x++) {
            // first triangle //
            mesh.addIndex((y)*columns + x);
            mesh.addIndex((y)*columns + x+1);
            mesh.addIndex((y+1)*columns + x);
            
            // second triangle //
            mesh.addIndex((y)*columns + x+1);
            mesh.addIndex((y+1)*columns + x+1);
            mesh.addIndex((y+1)*columns + x);
        }
    }
    
}
