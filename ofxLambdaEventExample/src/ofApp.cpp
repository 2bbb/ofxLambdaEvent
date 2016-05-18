#include "ofMain.h"

#include "ofxLambdaEvent.h"

class ofApp : public ofBaseApp {
    ofEvent<int> my_event;
    ofEventListener lis;
    float p;
public:
    void setup() {
        int q;
        ofxAddLambdaListener(my_event,
                             [this, &q](int &x) { std::cout << x << std::endl; });
    }
    void update() {}
    void draw() {}
    
    void exit() {}
    
    void keyPressed(int key) {
        static int i = 0;
        ++i;
        my_event.notify(i);
    }
    void keyReleased(int key) {}
    void mouseMoved(int x, int y) {}
    void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void mouseEntered(int x, int y) {}
    void mouseExited(int x, int y) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp);
}
