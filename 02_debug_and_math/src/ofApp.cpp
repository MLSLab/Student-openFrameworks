#include "ofApp.h"

//https://stackoverflow.com/a/26221725
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}


//--------------------------------------------------------------
void ofApp::setup(){
    cnt = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cnt++;
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    std::string buf = string_format("%d", cnt);
    
    ofDrawBitmapString(buf, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1')
    {
        ofVec3f v1;
        ofVec3f v2;
        
        v1.x = 1;
        v1.y = 0.1;
        v1.z = -0.2;
        
        v1 = v1.normalize(); // unit vector
        
        v2 = ofVec3f(0,0,1);
        
        ofQuaternion quat1;
        
        quat1.makeRotate(v1, v2);
        
        //int a = quat1.length();
        
        ofVec3f rotated = quat1 * v1;
        
        
        ofVec3f rotated2 = quat1.inverse() * v2; // v2를 회전하여 v1으로 (역방향 회전)
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
