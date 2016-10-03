#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
  
    string baseIP = "192.168.0.8";
    
    projector1.setup(baseIP,Panasonic_MODE,"admin1","panasonic");
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'l'){
        projector1.sendCommand("%1NTCONTROL 1\r");
        cout << projector1.getProjectorStatus() << endl;
    }
    if (key == 'p'){
        //query power status
        projector1.sendCommand("00QPW\r");
        cout << projector1.getProjectorStatus() << endl;
        //response 00001 = projector is powered on
    }
    if(key == 'i')  projector1.sendCommand("00PON\r"); //power on
    if(key == 'o')  projector1.sendCommand("00POF\r"); //power off
    
    
    if(key == '1')  projector1.sendCommand("00QSH\r"); //query shutter status
    if(key == '2')  projector1.sendCommand("00OSH:0\r"); //shutter open
    if(key == '3')  projector1.sendCommand("00OSH:1\r"); //shutter closed


    
    if(key == '-' || key == '_')  projector1.sendCommand("00VXX:LNSI4=+00001\r"); // LENS FOCUS slow -
    if(key == '+' || key == '=')  projector1.sendCommand("00VXX:LNSI4=+00000\r"); // LENS FOCUS slow +
//    if(key == '-' || key == '_')  projector1.sendCommand("00VXX:LNSI4=+00101\r"); // LENS FOCUS normal -
//    if(key == '+' || key == '=')  projector1.sendCommand("00VXX:LNSI4=+00100\r"); // LENS FOCUS normal +

//    if(key == '{' || key == '[')  projector1.sendCommand("00VXX:LNSI5=+00001\r");// LENS FOUCS slow -
//    if(key == '}' || key == ']')  projector1.sendCommand("00VXX:LNSI5=+00000\r");// LENS FOUCS slow +
    if(key == '{' || key == '[')  projector1.sendCommand("00VXX:LNSI5=+00101\r");// LENS FOUCS normal -
    if(key == '}' || key == ']')  projector1.sendCommand("00VXX:LNSI5=+00100\r");// LENS FOUCS normal +
    
//manual page 26   section 3.37
    if(key == 'q')  projector1.sendCommand("00QVB\r"); // darkest == -31 (001), brightest == 31 (063)
    if(key == 'a')  projector1.sendCommand("00VBR:001\r"); //brightness set to a value = 1
    if(key == 'z')  projector1.sendCommand("00VBR:063\r"); //brightness set to a value = 63
    
    //page 95 section 3.225. BRIGHTNESS CONTROL - GAIN, query section 3.444
        if(key == 'w')  projector1.sendCommand("00QVX:TGAI0\r");
        if(key == 's')  projector1.sendCommand("00VXX:TGAI0=+00020\r"); //gain 20%
        if(key == 'x')  projector1.sendCommand("00VXX:TGAI0=+00100\r"); //gain 100%
    
    //manual page 96 section 3.224
//    if(key == 'e')  projector1.sendCommand("ecoGet"); //return 1d01 == eco is used, return 1d == eco is not used
    if(key == 'd')  projector1.sendCommand("00VXX:LPWI1=+00000\r"); // lamp power ECO
    if(key == 'c')  projector1.sendCommand("00VXX:LPWI1=+00001\r"); // lamp power normal
//
    
    //manual page 93 section 3.221, query 3.440
    if(key == 'r')  projector1.sendCommand("00QSL\r");
    if(key == 'f')  projector1.sendCommand("00LPM:0\r"); //lamp selection dual
    if(key == 'g')  projector1.sendCommand("00LPM:1\r"); //lamp selection singal
    if(key == 'v')  projector1.sendCommand("00LPM:2\r"); //lamp selection lamp 1
    if(key == 't')  projector1.sendCommand("00LPM:3\r"); //lamp selection lamp 2
    
//    if(key == 'g')  projector1.sendCommand("lampAlternate");
//    if(key == 'b')  projector1.sendCommand("lampAlternateAuto");
//    if(key == 'y')  projector1.sendCommand("lampAlternateCycle");
//    
//    if(key == '3')  projector1.sendCommand("lamp1TimeLB");
//    if(key == '4')  projector1.sendCommand("lamp1TimeHB");
//    if(key == '5')  projector1.sendCommand("lamp2TimeLB");
//    if(key == '6')  projector1.sendCommand("lamp2TimeHB");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
