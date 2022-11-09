#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    public:
        void jsonWriteTest();
        void checkMode();
    
    public: //custom
        
        void savePts();
        void saveJSON();
        std::string g_fn;
        int g_cnt;
        ofImage g_img1;
        ofColor g_clr;
    
        int g_draw_mode;
        
        //vector
        std::vector<ofPoint> g_vpts;
        std::vector<int> g_vmode;
};
