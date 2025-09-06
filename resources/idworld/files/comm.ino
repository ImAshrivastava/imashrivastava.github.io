/*!
 * 
 *@copyright   Copyright (c) 2021 Esaathy Digitals Pvt. Ltd.
 *@author      [Aman Shrivastava](ashrivastava.as23apr2001@gmail.com)
 *@credits     [fengli](li.feng@dfrobot.com) | [olikraus](olikraus@gmail.com) | [Eddard](Eddard.liu@dfrobot.com)
 *@date        2021-10-17
 *@ https://github.com/DFRobot/DFRobot_ID809 Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@ https://github.com/olikraus/u8glib/ Copyright (c) 2012, olikraus@gmail.com

  * Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  
*/



/*
 * ------LED Colors------
 * Green:   eLEDGreen   (1)
 * Red:     eLEDRed     (2)
 * Yellow:  eLEDYellow  (3)
 * Blue:    eLEDBlue    (4)
 * Cyan:    eLEDCyan    (5)
 * Magenta: eLEDMagenta (6)
 * White:   eLEDWhite   (7)
 * -----------------------
 * 
 * -------LED Blinks---------
 * Breathing:    eBreathing   (1)
 * Fast Blink:   eFastBlink   (2)
 * Keeps ON:     eKeepsOn     (3)
 * Normal Close: eNormalClose (4)
 * Fade In:      eFadeIn      (5)
 * Fade Out:     eFadeOut     (6)
 * Slow Blink:   eSlowBlink   (7)
 * ---------------------------
 * 
 * -> Press Finger:                 fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);
 * -> Release Finger:               fingerprint.ctrlLED(fingerprint.eSlowBlink, fingerprint.eLEDWhite, 1);
 * -> Fingerprint Collection:       fingerprint.ctrlLED(fingerprint.eFastBlink, fingerprint.eLEDYellow, 3);
 * -> Fingeprint Collection Failed: fingerprint.ctrlLED(fingerprint.eFastBlink, fingerprint.eLEDRed, 3);
 * -> Module Function Success:      fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDGreen, 0);
 *                                  delay(2000); 
 *                                  fingerprint.ctrlLED(fingerprint.eNormalClose, fingerprint.eLEDGreen, 0);
 *                                  delay(1000);    
 *    
 * -> Module Function Failed:       fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDRed, 0);
 *                                  delay(2000); 
 *                                  fingerprint.ctrlLED(fingerprint.eNormalClose, fingerprint.eLEDRed, 0);
 *                                  delay(1000);
 * 
 */
#include <DFRobot_ID809.h>
//#include <WiFiNINA.h>

DFRobot_ID809 fingerprint;

char message;
String tempData;
String IDStatus;

//*************************************** GET-SET Parameters 
// A, B, C, D, E, F, H, I, R, S, T, U
  
const char HANDSHAKE             = 'H';
const char CONNECT               = 'C';
const char OK                    = 'O';
const char DONE                  = 'D';

const char GET_DEVICE_INFO       = 'F';
const char GET_DEVICE_ID         = 'I';
const char GET_DEVICE_SECURITY   = 'U';
const char GET_DUPLICATION_CHECK = 'L';
const char GET_BAUDRATE          = 'B';
const char GET_AUTOLEARN         = 'A';
const char GET_EMPTY_ID          = 'E';
const char GET_STATUS            = 'S';
const char GET_BROKEN_ID         = 'R';
const char GET_MODULE_SN         = 'N';         
const char GET_ENROLL_COUNT      = 'T';     
//-----------------------------------------------------------

//*************************************** SET Parameters
const char SET_DEVICE_ID         = 'i';
const char SET_DEVICE_SECURITY   = 'u';
const char SET_DUPLICATION_CHECK = 'd';
const char SET_BAUDRATE          = 'b';
const char SET_AUTOLEARN         = 'a';
const char SET_MODULE_SN         = 'n';         
//-----------------------------------------------------------

// G, J, P, W
//*************************************** Fingerprint Module Functions
const char REGISTER              = 'Q';
const char MATCH                 = 'M';
const char TEMP_DATA             = 'K';
const char FP_IMG                = 'X';
const char TEMP_MATCH            = 'V'; 
const char DELFP                 = 'Y';
const char DELALLFP              = 'Z';
//--------------------------------------------------------------------

void setup() {
   Serial.begin(9600);
   Serial1.begin(115200);
   fingerprint.begin(Serial1);

   while(!Serial);

   //pinMode(LEDR, OUTPUT);
   //pinMode(LEDG, OUTPUT);
   //pinMode(LEDB, OUTPUT);
   //digitalWrite(LEDR, LOW);
   //digitalWrite(LEDG, LOW);
   //digitalWrite(LEDB, LOW);

   while(fingerprint.isConnected() == false){
    //Serial.println("Communication with device failed, please check connection");
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
    //delay(1000);
    //digitalWrite(LEDR, HIGH);
    //delay(200);
    //digitalWrite(LEDR, LOW);
    //delay(200);
   }
}


void loop() {
  Serial.println("accepting");
  if (Serial.available()>0) {
     Serial.print("waiting");
     message = Serial.read(); 

     if(isLowerCase(message)) {
      switch(message) {
        case SET_DEVICE_ID:
          set_device_id();
          break;
        case SET_DEVICE_SECURITY: 
          set_device_security();
          break;
        case SET_DUPLICATION_CHECK:
          set_duplication_check();
          break;
        case SET_BAUDRATE:
          set_baudRate();
          break;
        case SET_AUTOLEARN:
          set_autoLearn();
          break;
        case SET_MODULE_SN:
          set_moduleSN();
          Serial.println("breaked from swich");
          break;
      }
      Serial.println("Again breaked");
     }
     else if(isUpperCase(message)) {
      switch(message) {
        case HANDSHAKE:
          handshake();
          break;
        
        // ********************** GET
        case GET_DEVICE_INFO:
          get_device_info();
          break;
        case GET_DEVICE_ID:
          get_device_id();
          break;
        case GET_DEVICE_SECURITY:
          get_device_security();
          break;
        case GET_DUPLICATION_CHECK:
          get_duplication_check();
          break;
        case GET_BAUDRATE:
          get_baudRate();
          break;
        case GET_AUTOLEARN:
          get_autoLearn();
          break;
        case GET_EMPTY_ID:
          get_emptyID();
          break;
        case GET_STATUS:
          get_status();
          break;
        case GET_BROKEN_ID:
          get_brokenID();
          break;
        case GET_MODULE_SN:
          get_moduleSN(); 
          break;
        case GET_ENROLL_COUNT:
          get_enrollCount();
          break;
        // ---------------------------------

        // ********************** SET
        /*case SET_DEVICE_ID:
          fingerprint.setDeviceID(5); 
          //get_enrollCount();
          break;
        */
        // ---------------------------------
        case REGISTER:
          fp_register();
          break;
        case MATCH:
          fp_match();
          break;
        case DELFP:
          fp_delete();
          break;
        case DELALLFP: 
          delallfp();
          break;
        case TEMP_DATA:
          temp_data();
          break;
        case FP_IMG:
          fingerImage();
          break; 
       }      
     }
   }
   delay(100);
}


//*************************************** GUI App-Stylus Communication Handshake
void handshake() { 
  
  while(true) {
    if (Serial.available()>0) {
      message = Serial.read();
      if(message==CONNECT) {
        break;
      }
    }
    Serial.println(HANDSHAKE);
  }
}
//-------------------------------------------------------


//*************************************** Fingerprint GET Functions
void get_device_info() {
  
  get_process();
  String ret;
  if((ret = fingerprint.getDeviceInfo()) == NULL) {
    func_fail();
  }
  else {
    ret.replace("_", "");
    Serial.print(ret);
    delay(1000);
    func_sucx();
  }       
}

void get_device_id() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getDeviceID()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

void get_device_security() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getSecurityLevel()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  } 
}

void get_duplication_check() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getDuplicationCheck()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

void get_baudRate() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getBaudrate()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

void get_autoLearn() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getSelfLearn()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

void get_emptyID() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getEmptyID()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

void get_status() {
  
  get_process();
  for(int i=1; i<=80; i++) {
    IDStatus.concat(i);
    IDStatus.concat(": ");
    if(fingerprint.getStatusID(i)) {
      IDStatus.concat("REGISTERED");
    }
    else {
      IDStatus.concat("NOT REGISTERED");
    }
    delay(100);
    IDStatus.concat(", ");
  }
  Serial.print(IDStatus);
  func_sucx();
  
}

void get_brokenID() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getBrokenQuantity()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

void get_moduleSN() {
  
  get_process();
  String ret;
  if((ret = fingerprint.getModuleSN()) == NULL) {
    func_fail();
  }
  else {
    Serial.print(ret);
    delay(1000);
    func_sucx();
  }    
}

void get_enrollCount() {
  
  get_process();
  uint8_t ret;
  if((ret = fingerprint.getEnrollCount()) == ERR_ID809) {
    func_fail();
  }
  else {
    Serial.print(String(ret));
    delay(1000);
    func_sucx();
  }
}

//-------------------------------------------------------

//*************************************** Fingerprint SET Functions
void set_device_id() {
  
  set_process();
  //
  //String strmes;
  //char setval[15];

  
  while(true) {
    if (Serial.available()>0) {
       message = Serial.read();
      
      /*int str_len = strmes.length() + 1;
      char strmes_array[str_len];
      strmes.toCharArray(strmes_array, str_len);
      for(int i =0;i<str_len;i++) {
        Serial.println(strmes_array[i]);
      }*/
 
      if(isDigit(message)) {
        String setval = String(message);
        Serial.println(setval);
        if(setval.toInt()< 1 || setval.toInt()> 255) {
          func_fail();
          break; 
        }
        else {
          fingerprint.setDeviceID(setval.toInt());
          func_sucx();
          break; 
        }
      }
    }
    Serial.println(OK);
  }
}

void set_device_security() {
  
}

void set_duplication_check() {
  
}

void set_baudRate() {
  
}

void set_autoLearn() {
  
}

void set_moduleSN() {
  set_process();
  
  char sn[] = "";
  String recv; 

  delay(2000);
  while(true) {
    if (Serial.available()>0) {
        recv = Serial.readString();
        recv.remove(0,0);
        for(int i=0;i<recv.length();i++) {
          if(!isAlphaNumeric(recv[i])) {
            break;
          }
        }
        
        recv.toCharArray(sn, recv.length()+1);
        if(strlen(sn) < 15) {
          fingerprint.setModuleSN(sn);
          func_sucx();
          break;
        }
        else{
          func_fail();
          break;
        }
     }
  }
  
}
//-------------------------------------------------------


//*************************************** Fingerprint Module Functions
void fp_register() {

  #define COLLECT_NUMBER 3
  uint8_t ID,i;

  if((ID = fingerprint.getEmptyID()) == ERR_ID809) { 
    func_fail();
  }
  else {
    i = 0; 
    while(i < COLLECT_NUMBER) {
      // Press Finger
      fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);

      if((fingerprint.collectionFingerprint(10)) != ERR_ID809) {
        collec_sucx();
        i++;  
      }
      else {
        collec_fail();
      }
    
      while(fingerprint.detectFinger()) {
        release_f();
      }
    
      delay(1000);
    }
  

    if(fingerprint.storeFingerprint(ID) != ERR_ID809) {
      func_sucx();
    } 
    else {
      func_fail();
    }
  }  
}

void fp_match() {
  uint8_t ret;
  
  fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);

  if((fingerprint.collectionFingerprint(/*timeout=*/0)) != ERR_ID809) {
    collec_sucx();

    while(fingerprint.detectFinger()) {
        release_f();
    }

    ret = fingerprint.search();

    if(ret != 0){
      func_sucx();
    }else{
      func_fail();
    }
    
  }
  else {
    collec_fail();
  }
}

void fp_delete() {
  uint8_t ret;
  
  fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);

  if((fingerprint.collectionFingerprint(/*timeout=*/10)) != ERR_ID809) {
    collec_sucx();

    while(fingerprint.detectFinger()) {
        release_f();
    }
    
    ret = fingerprint.search();

    if(ret != 0){
      fingerprint.delFingerprint(ret);
      func_sucx();
    }
    else {
      func_fail();
    }
  }
  else {
    collec_fail();
  }
}

void delallfp() {
  if(fingerprint.delFingerprint(DELALL)!= ERR_ID809) {
    func_sucx();      
  } 
  else {
    func_fail();
  }
}

void temp_data() {
  
  #define COLLECT_NUMBER 3
  uint8_t ID, i, temp[1008];
  char comma = ','; 

  if((ID = fingerprint.getEmptyID()) == ERR_ID809) { 
    func_fail();
  }
  else {
    i = 0; 
    while(i < COLLECT_NUMBER) {
      // Press Finger
      fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);

      if((fingerprint.collectionFingerprint(10)) != ERR_ID809) {
        collec_sucx();
        i++;  
      }
      else {
        collec_fail();
      }
    
      while(fingerprint.detectFinger()) {
        release_f();
      }
    
      delay(1000);
    }
  

    if(fingerprint.storeFingerprint(ID) != ERR_ID809) {
      fingerprint.getTemplate(ID, temp);
      delay(2000);
      if(temp!=NULL) {
        for(int j = 0; j<1008; j++) {
          if(j<1007) {
            tempData.concat(temp[j]);
            tempData.concat(comma);
          }
          else if(j==1007) {
            tempData.concat(temp[j]);
          }
        }
        Serial.print(tempData);
        func_sucx();
        Serial.print(DONE);
        fingerprint.delFingerprint(ID);
      }
      else {
        Serial.println("Temp NULL...");
        fingerprint.delFingerprint(ID);
        func_fail();
      }
    } 
    else {
      func_fail();
    }
  }
}

void fingerImage() {
  uint8_t data[25600];
  char comma = ','; 
  String fingerImg;


  while(true) {
    
    fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);

    if(fingerprint.detectFinger()) {
      fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDYellow, 0);
      fingerprint.getFingerImage(data);
      delay(3000);
      fingerprint.ctrlLED(fingerprint.eNormalClose, fingerprint.eLEDYellow, 0);
      break;
    }

    delay(100);
    
  }

  for(int i=0;i<25600;i++) {
    fingerImg.concat(data[i]);
    if(i<25599) {
      fingerImg.concat(comma);
    }
    if(i==10000) {
      Serial.println(fingerImg);
      fingerImg = "";
      delay(2000);
    }
    else if(i==20000) {
      Serial.println(fingerImg);
      fingerImg = "";
      delay(2000);
    }
    else if(i==25599) {
      Serial.println(fingerImg);
      fingerImg = "";
      delay(2000);
    }
  }
  //Serial.println(DONE);

  for(int i = 0; i < 25600; i++) {
    data[i] = 0;
  }
  /*
  for(int i=0;i<25600;i++) {
    if(i<25599) {
      Serial.print(data[i]);
      Serial.print(',');
    }
    else {
      Serial.println(data[i]);
    }
  }
  */
  /*
    
  while(fingerprint.detectFinger()) {
    release_f();
    }

  fingerprint.getFingerImage(data);
  delay(3000);

  if(data!=NULL) {
    for(int j = 0; j<25600; j++) {
      if(j<25599) {
        fingerImgData.concat(data[j]);
        fingerImgData.concat(comma);
        }
      else if(j==25599) {
        fingerImgData.concat(data[j]);
        }
       }
      Serial.print(fingerImgData);
      func_sucx();
  }
  else {
        Serial.println("Temp NULL...");
        func_fail();
    }
    */
  
}
//-------------------------------------------------------


//*************************************** LED UX Respone
void get_process() {
  fingerprint.ctrlLED(fingerprint.eFadeIn, fingerprint.eLEDMagenta, 1);
  delay(1500);
  fingerprint.ctrlLED(fingerprint.eFadeOut, fingerprint.eLEDMagenta, 1);
  delay(1500);
}

void set_process() {
  fingerprint.ctrlLED(fingerprint.eFadeIn, fingerprint.eLEDCyan, 1);
  delay(1500);
  fingerprint.ctrlLED(fingerprint.eFadeOut, fingerprint.eLEDCyan, 1);
  delay(1500);
}

void release_f() {
  // Release Finger
  fingerprint.ctrlLED(fingerprint.eSlowBlink, fingerprint.eLEDWhite, 2);
  delay(300);
}

void collec_sucx() {
  // Fingerprint Collection Success
  fingerprint.ctrlLED(fingerprint.eFastBlink, fingerprint.eLEDYellow, 3);
  delay(1250);
}

void collec_fail() {
  // Fingerprint Collection Failed
  fingerprint.ctrlLED(fingerprint.eFastBlink, fingerprint.eLEDRed, 3);
  delay(1250);
}

void func_sucx() {
  // Function Success
  fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDGreen, 0);
  delay(1000); 
  fingerprint.ctrlLED(fingerprint.eNormalClose, fingerprint.eLEDGreen, 0);
  delay(1000); 
}

void func_fail() {
  // Function Failed
  fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDRed, 0);
  delay(1000); 
  fingerprint.ctrlLED(fingerprint.eNormalClose, fingerprint.eLEDRed, 0);
  delay(1000);
}
//-------------------------------------------------------
