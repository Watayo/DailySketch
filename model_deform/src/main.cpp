#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
    ofGLWindowSettings glSettings;
    glSettings.setSize(1024, 768); //was 748 vertical
    //glSettings.windowMode = OF_WINDOW;
    glSettings.setGLVersion(3, 2);
    ofCreateWindow(glSettings);

    printf("%s\n", glGetString(GL_VERSION));
    ofRunApp(new ofApp());


}

