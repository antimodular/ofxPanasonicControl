/*
 *  pjControl.cpp
 *
 *
 *  Created by Noah Shibley on 8/9/10.
 *  Copyright 2010 Noah Shibley. All rights reserved.
 *
 */

#include "ofxPanasonicControl.h"
#include "ofMain.h"

ofxPanasonicControl::ofxPanasonicControl() {
    connected = false;
    projStatus = false;
}

ofxPanasonicControl::~ofxPanasonicControl() {
    
}

bool ofxPanasonicControl::getProjectorStatus() {
    return projStatus;
}

void ofxPanasonicControl::setProjectorType(int protocol) { 
    commMode = protocol;
}

void ofxPanasonicControl::setup(string IP_add, int protocol, string user, string password) {
    setProjectorIP(IP_add);
    setProjectorType(protocol);
    setProjectorPassword(password);
    setProjectorUserName(user);
}

void ofxPanasonicControl::setProjectorIP(string IP_add) {
    IPAddress = IP_add;
}

void ofxPanasonicControl::setProjectorPassword(string passwd) {
    password = passwd;
}

void ofxPanasonicControl::setProjectorUserName(string user) {
    adminUser = user;
}


void ofxPanasonicControl::sendCommand(string command, int amount) {
    
    string msgRx="";
    
    if(!pjClient.isConnected()) {
        pjClient.setVerbose(true);
        connected = pjClient.setup(IPAddress, PANASONIC_PORT,true);
        //ofLog() << "connection established: " << IPAddress << ":" << PANASONIC_PORT << endl;
        cout<< "connection established: " << IPAddress << ":" << PANASONIC_PORT << endl;
        string response = "";
        while (msgRx.length() < 8) {
            msgRx = pjClient.receiveRaw();
        }
        ofLog() << "received response: " << msgRx << endl;
        
    }
    
    string randomResponseMessage;
    randomResponseMessage =msgRx.substr(msgRx.length()-9,8);
    
    ofLog() <<"token received: "<< randomResponseMessage<<".";
    
    //eg. PJLINK 1 604cc14d
    /*
     3.Generate 32 bytes hash value (message digest) from the following data by using the MD5 (Message Digest Algorithm 5).
     "xxxxxx:yyyyy: zzzzzzzz"
     á xxxxxx: Administrator authority user-name on WEB CONTROL [default = "admin1"]
     á yyyyy: Password corresponding to above-mentioned user-name (admin1) [default = "panasonic"] á zzzzzzzz: 8 bytes random characters obtained from the response message
     á (colon): Separator
     */
    string authToken = "";
    string comboToken = "";
    if(randomResponseMessage != "") {
//        ofLog() << "with authentication" << endl;
        MD5Engine md5;
        md5.reset();
//        string hash = msgRx.substr(9,8);
        comboToken = adminUser+":"+password+":"+randomResponseMessage;
        
        ofLog() <<comboToken<<endl;
        md5.update(comboToken); //adminUser+":"+password+":"+authToken);
        authToken = DigestEngine::digestToHex(md5.digest());
    }
    ofLog() << "sending command: " << authToken <<" + "<<command<< endl;
    pjClient.sendRaw(authToken+command);
    
    //------receive response
//    msgRx = "";
//    while (msgRx.length() < 8) {
//        msgRx = pjClient.receiveRaw();
//    }
    msgRx = "";
    //    for(int i=0; i<msgRx.length(); i++) {
    //        msgRx += pjClient.receiveRaw();
    //    }
    
    if(pjClient.isConnected()) {
        msgRx = pjClient.receiveRaw();
        //        cout << msgRx << endl;
    }
    
    ofLog() << "received response: " << msgRx << endl;
    
    pjClient.close();
    //connected = false;

    
}



void ofxPanasonicControl::sendPJLinkCommand(string command) {
    string msgRx="";
    
    if(!pjClient.isConnected()) {
        pjClient.setVerbose(true);
        connected = pjClient.setup(IPAddress, PJLINK_PORT,true);
        ofLog() << "connection established: " << IPAddress << ":" << PJLINK_PORT << endl;
        
        ofLog()<<"msgRx.length() "<<msgRx.length();
        /*
         string response = "";
         while (msgRx.length() < 8) {
         msgRx = pjClient.receiveRaw();
         ofLog() << "response: " << msgRx << endl;
         }
         ofLog() << "received response: " << msgRx << endl;
         */
    }
    string authToken = "";
    
    //eg. PJLINK 1 604cc14d
    if(msgRx[7] == '1') {
        ofLog() << "with authentication" << endl;
        MD5Engine md5;
        md5.reset();
        string hash = msgRx.substr(9,8);
        ofLog() << hash << endl;
        md5.update(hash + password);
        authToken = DigestEngine::digestToHex(md5.digest());
    }
    
    
    ofLog() << "sending command: " << authToken+command << endl;
    pjClient.sendRaw(authToken+command);
    
    /*
     msgRx = "";
     while (msgRx.length() < 8) {
     msgRx = pjClient.receiveRaw();
     }
     ofLog() << "received response: " << msgRx << endl;
     */
    
    pjClient.close();
    //connected = false;
}

