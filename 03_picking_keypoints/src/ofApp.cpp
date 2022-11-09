#include "ofApp.h"
#include "ofxJsonUtils.h"
// https://github.com/2bbb/ofxJsonUtils
// https://openframeworks.cc/ko/setup/xcode/
/*
typedef struct __bbox
{
    int v[4];
} bbox;
*/
typedef std::vector<int> bbox;
typedef std::vector<int> keypts;
//--------------------------------------------------------------
void ofApp::setup(){
    //std::string fn;
    //fn = "dog_and_sun_small.jpg";
    //fn = "2560px-Sungkyunkwan_University_Bicheondang_and_600th_Anniversary_Hall.jpg";
    g_fn = "COCO/000000007088.jpg";
    
    //DD::Tokenize(fn, fns, ".");
    
    g_img1.load(g_fn);
    
    g_draw_mode  = 1;
    g_cnt = 0;
    g_clr = ofColor(255,0,255);
    
    // jsonWriteTest();
    
    
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
    ofSetColor(g_clr);
    
    if(g_vpts.size()>0)
    {
        ofPoint pt = g_vpts[g_vpts.size()-1]; //
        buf = StringFormat("%d\t%d (%.f, %.f)",g_cnt, g_vpts.size(),  pt.x, pt.y);
        ofDrawBitmapString(buf, 30, 30);
      
        //ofDrawLine(pt.x, pt.y, pt.x, pt.y+5);
    }
    else
    {
        buf = StringFormat("%d\t%d", g_cnt, g_vpts.size());
        ofDrawBitmapString(buf, 30, 30);
        
    }
    
    
    if(g_draw_mode==1)
    {
        buf = StringFormat("Mode: %d (BBOX)", g_draw_mode);
    }
    else if(g_draw_mode==2)
    {
        buf = StringFormat("Mode: %d (Keypoints)", g_draw_mode);
    }
    
    
    ofDrawBitmapString(buf, 30, 50);
    /// cross_hair
    
    ofSetColor(g_clr);
    
    for(int i=0; i<g_vpts.size(); i++)
    {
        
        ofPoint pt = g_vpts[i];
        ofDrawLine(pt.x+10, pt.y+10, pt.x-10, pt.y-10);
        ofDrawLine(pt.x+10, pt.y-10, pt.x-10, pt.y+10);
        
    }
    
    
    if(g_vpts.size()>1)
    for(int i=0; i<g_vpts.size(); i++)
    {
        ofPoint pt = g_vpts[i];
        if(g_vmode[i]==1 && i%19 ==0) // rect
        {
            if(i<g_vpts.size()-1) // 각 박스는 mode가 1이어도 첫번째 점만 있는 경우는 박스를 그릴수가 없어요.
            {
                ofPoint pt1 = g_vpts[i+1];
            
                float w = pt1.x - pt.x;
                float h = pt1.y - pt.y;
                
                ofDrawLine(pt.x, pt.y, pt1.x, pt.y);
                ofDrawLine(pt1.x, pt.y, pt1.x, pt1.y);
                
                ofDrawLine(pt1.x, pt1.y, pt.x, pt1.y);
                ofDrawLine(pt.x, pt1.y, pt.x, pt.y );
               
            }
        }
    }
    
    g_cnt++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    

}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch (key){
        case 'k':
            g_vmode.clear();
            g_vpts.clear();
            break;
        
        case 'r':
        case '\b': //backspace
            if(g_vpts.size()>0)
            {
                g_vpts.pop_back();
                g_vmode.pop_back();
            }
            break;
            
        case 's':
            savePts();
            break;
        case 'j':
            saveJSON();
            break;
        case 'o':
            g_clr = ofColor(255,0,255);
            break;
            
        case 'p':
            g_clr = ofColor(0,255,255);
            break;
        
        case '1':
            g_draw_mode = 1; //rect
            break;
        case '2':
            g_draw_mode = 2; //point
            break;
        default:
            
            break;
            
        
    }
    checkMode();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(g_vpts.size()>0)
    {
        ofPoint pt;
        pt.x = x;
        pt.y = y;
        
        g_vpts.at(g_vpts.size() -1) = pt;
        
        std::cout << x << " , " << y << " ---  " << g_vpts.size() << std::endl;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofPoint pt;
    pt.x = x;
    pt.y = y;
 
    g_vpts.push_back(pt);
    g_vmode.push_back(g_draw_mode);
    
    std::cout << "Mode:" << g_draw_mode << " (" << x << " , " << y << ") Button (" << button <<") ---  " << g_vpts.size() << std::endl;
}

void ofApp::checkMode()
{
    if(g_vpts.size() % 19 == 2)
    {
        g_draw_mode = 2;    // keypoint mode
    }
    else if(g_vpts.size() % 19 <2)
    {
        g_draw_mode = 1;    // bbox mode
    }
    
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    checkMode();
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
    
    for(int i=0; i<g_vpts.size(); i++)
    {
        ofPoint pt = g_vpts[i];
        std::string buf = StringFormat("%d\t%.f\t%.f\t%d\n", i, pt.x, pt.y, g_vmode[i]);
        std::cout << buf;

        of<<buf;
        
    }
    of.close();
    g_vpts.clear();
    g_vmode.clear();
    std::cout << "Done..." << std::endl;
}


void ofApp::saveJSON()
{
    std::cout << "Saving...into JSON" << std::endl;
    std::string datestr = ofGetTimestampString("%Y%m%d_%H%M%S");
    std::string fname = "points_" + datestr + ".json";
    
    
    std::vector<bbox> vbbox;
    std::vector<keypts> vkpts;
    
    keypts kpts1; // for each person
    //kpts1.resize(17*3);
    
    for(int i=0; i<g_vpts.size(); i++)
    {
        //if(g_vmode[i] ==1 && i%2 ==0) // bbox
        if( g_vmode[i] ==1 &&
            ((i % 19 )==0 ) ) // 0, 2+17, 2*(2+17), ....
        {
            ofVec2f pt1 = g_vpts[i];
            ofVec2f pt2 = g_vpts[i+1];
            
            //ofVec4f bbox = ofVec4f(pt1.x, pt1.y, pt2.x, pt2.y);
            bbox bbox1;
            bbox1.resize(4);
            bbox1[0] = pt1.x;
            bbox1[1] = pt1.y;
            bbox1[2] = pt2.x;
            bbox1[3] = pt2.y;
            
            vbbox.push_back(bbox1);
            if(kpts1.size() >= 17*3 -1 )
                vkpts.push_back(kpts1);
            
            kpts1.clear(); // make it empty
        }
        else if(g_vmode[i] ==2) // keypoints
        {
            ofVec2f pt1 = g_vpts[i];
            kpts1.push_back(pt1.x);
            kpts1.push_back(pt1.y);
            kpts1.push_back(1); //// TODO: check this
            
        }
        
    }
    
    vkpts.push_back(kpts1);
    
    cout << "Preparation done !" << endl;
    cout <<vkpts.size() << " " << vbbox.size() << endl;
    
    std::vector<ofJson> vjson;
    ofJson jsonHuman;
    
    if(vbbox.size()==1)
    {
        ofJson json_values;
        json_values = ofxJsonUtils::create("bbox",  vbbox[0], "keypoints",  vkpts[0]);
        jsonHuman = ofxJsonUtils::create("H0",  json_values);
        
    }
    else if(vbbox.size()==2)
    {
        ofJson json_values0, json_values1;
        json_values0 = ofxJsonUtils::create("bbox",  vbbox[0], "keypoints",  vkpts[0]);
        json_values1 = ofxJsonUtils::create("bbox",  vbbox[1], "keypoints",  vkpts[1]);
        
        jsonHuman = ofxJsonUtils::create("H0",  json_values0, "H1",  json_values1);
        
    }
    //else if(vbbox.size()==3)
    
    string fn_json = g_fn;
    fn_json.replace(fn_json.end()-3, fn_json.end(), "json");
    
    
    //std::string fn ="keypoints.json";
    if(vbbox.size()>0)
    {
        
        ofxJsonUtils::writeToFile( fn_json.c_str(), jsonHuman);
    }
    else
    {
        cout << "No bbox keypoints found !" << endl;
    }
    
    /*
    for(int i=0; i<vbbox.size(); i++)
    {
        
        ofJson json_box = ofxJsonUtils::create("bbox",  vbbox[i], "keypoints",  vkpts[i]);
        //ofJson json_kpts= ofxJsonUtils::create("keypoints",  vkpts[i]);
        
        std::string key1 = StringFormat("H%d", i);
        ofJson jsonHuman = ofxJsonUtils::create(key1,  json_box);
        
        std::string fn =StringFormat("H%d.json", i);
        
        ofxJsonUtils::writeToFile( fn.c_str(), jsonHuman);
        //cout << vbbox[i] << endl;
        cout << fn << endl;
        //cout <<"bbox:\t" << vbbox[i] << endl;
    }
     */
    g_vpts.clear();
    g_vmode.clear();
    std::cout << "Done... writing information into " <<  fn_json << std::endl;
    
}





void ofApp::jsonWriteTest()
{
    // test json write
    // https://github.com/2bbb/ofxJsonUtils/blob/bbe39e50ea007d148ca9fdaa4c81d05403dc939e/SimpleExample/src/ofApp.cpp#L24
    ofVec3f v(1, 2, 3);
    ofVec4f w(4, 5, 6, 7);
    ofColor c(0, 255, 0);
    std::vector<int> xs{10, 11, 12, 13};
    
    ofJson json = ofxJsonUtils::create("vec3", v, "vec4", w, "color", c, "int_array", xs);
    ofxJsonUtils::writeToFile("save_data.json", json);
    
    //변수명으로 json key 설정
    ofJson json2 = ofxJsonUtils::create(kv(v), kv(w), kv(c), kv(xs));
    ofxJsonUtils::writeToFile("save_data2.json", json2);
    
}
