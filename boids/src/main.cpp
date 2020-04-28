#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.setSize(1024, 768); //was 748 vertical
    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());

}
