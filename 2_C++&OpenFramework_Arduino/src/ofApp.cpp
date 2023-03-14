#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    font.load("Helvetica", 18);
    
    // Display the list of available serial devices
        serial.listDevices();
        vector <ofSerialDeviceInfo> devicelist = serial.getDeviceList();

        // Set the serial communication baud rate
        int baud = 9600;
        
        // Connect to the serial device
        // Change this line depending on your platform and device
        serial.setup("/dev/tty.usbmodem1301", baud);
        //serial.setup("COM10", baud); // windows example
        //serial.setup("/dev/ttyUSB0", baud); //linux example
    

}

    //--------------------------------------------------------------
    void ofApp::update(){
        // Check if there is any serial data available
          if (serial.available() > 0) {
            // Read the byte data from the serial connection
            byteData = serial.readByte();
              
            cout << "Received byte data: " << byteData << endl;
          }
          else {
                  // Set the `byteData` to a default value (for example, 0)
                  byteData = 0;
                }

          // Check if the mouse is pressed
          if (ofGetMousePressed()) {
            // Set the `whiteScreen` variable to `true`
            whiteScreen = true;
              
              cout << "Mouse pressed, whiteScreen set to true" << endl;
          }

          // Check if the `byteData` is equal to 99
          if (byteData == 99) {
            // Set the `whiteScreen` variable to `false`
            whiteScreen = false;
              
              cout << "byteData is 99, whiteScreen set to false" << endl;
          }
    }
    
    //--------------------------------------------------------------
    void ofApp::draw(){
        if (whiteScreen) {
               ofBackground(255,255,0); // White background
               ofSetColor(255,0,0);
               msg = "MCDONALDS";
               font.drawString(msg, 50, 60);
           }

           if (!whiteScreen || byteData == 99) {
               if (ofGetMousePressed()) {
                 // Set the `whiteScreen` variable to `true`
                 whiteScreen = true;
               }
               
               ofBackground(255,0,0);    // Black background
               ofSetColor(255);    // Text color is white
               msg = "KFC";
               font.drawString(msg, 50, 60);
           }
        cout << "mousePressed: " << ofGetMousePressed() << endl;
       
    }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    serial.writeByte(sendData); // sending the data to arduino
//    cout << "Mouse pressed, sending data: " << sendData << endl;
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
