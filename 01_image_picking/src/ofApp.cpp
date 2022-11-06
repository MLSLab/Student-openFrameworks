#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    std::string fn;
    //fn = "dog_and_sun_small.jpg";
    fn = "2560px-Sungkyunkwan_University_Bicheondang_and_600th_Anniversary_Hall.jpg";
    g_img1.load(fn);
    
    g_cnt = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}


#include "bbutilstring.h"

//-------------------------------------------------------------- //60Hz
void ofApp::draw(){

    ofSetColor(255,255,255);
    g_img1.draw(0,0);
    std::string buf;
    
    if(g_pts.size()>0)
    {
        ofPoint pt = g_pts[g_pts.size()-1]; //
        buf = StringFormat("%d\t%d (%.f, %.f)",g_cnt, g_pts.size(),  pt.x, pt.y);
        
        //ofDrawLine(pt.x, pt.y, pt.x, pt.y+5);
        
    }
    else
    {
        buf = StringFormat("%d\t%d", g_cnt, g_pts.size());
    }
    
    ofDrawBitmapString(buf, 30, 30);
    
    /// cross_hair
    ofSetColor(255,0,255);
    for(int i=0; i<g_pts.size(); i++)
    {
        ofPoint pt = g_pts[i];
        ofDrawLine(pt.x+10, pt.y+10, pt.x-10, pt.y-10);
        ofDrawLine(pt.x+10, pt.y-10, pt.x-10, pt.y+10);
        
    }
    
    
    //g_cnt = g_cnt+1;
    g_cnt++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    

}

#include<fstream>
void ofApp::savePts()
{
    std::cout << "Saving..." << std::endl;
    std::string datestr = ofGetTimestampString("%Y%m%d_%H%M%S");
    std::string fname = "points_" + datestr + ".txt";
    //std::ofstream of;
    ofFile of;
    
    //of.open(fname.c_str(), std::ofstream::out | std::ofstream::app);
    of.open(fname,ofFile::WriteOnly);
    
    if (!of) {
        std::cerr << "can't open output file" << std::endl;
    }
    
    for(int i=0; i<g_pts.size(); i++)
    {
        ofPoint pt = g_pts[i];
        std::string buf = StringFormat("%d\t%.f\t%.f\n", i, pt.x, pt.y);
        std::cout << buf;

        of<<buf;
        
    }
    of.close();
    g_pts.clear();
    std::cout << "Done..." << std::endl;
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch (key){
        case 'k':
            g_pts.clear();
            break;
        
        case 'r':
            if(g_pts.size()>0)
                g_pts.pop_back();
            break;
            
        case 's':
            savePts();
            break;
            
        default:
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(g_pts.size()>0)
    {
        ofPoint pt;
        pt.x = x;
        pt.y = y;
        
        g_pts.at(g_pts.size() -1) = pt;
        
        std::cout << x << " , " << y << " ---  " << g_pts.size() << std::endl;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofPoint pt;
    pt.x = x;
    pt.y = y;
 
    g_pts.push_back(pt);
    
    std::cout << x << " , " << y << " ---  " << g_pts.size() << std::endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
}


//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
