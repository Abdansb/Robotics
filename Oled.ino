/*

*/
//#include <Adafruit_SSD1306.h>
//Adafruit_SSD1306 Oled(128, 64, &Wire, 4);
//#include <TimerThree.h>

#define btn1 1
#define btn2 2
#define btn3 3
#define NONE 8



#define hitam SSD1306_BLACK
#define putih SSD1306_WHITE

#define LOGO_HEIGHT   11
#define LOGO_WIDTH    8
static const unsigned char PROGMEM logo_bt[] =
{ B00011000,
  B00010100,
  B10010010,
  B01010100,
  B00111000,
  B00010000,
  B00111000,
  B01010100,
  B10010010,
  B00010100,
  B00011000
};

int btnValue;
int key = 0;
byte tekanSt = 0;
int counterTombol = 0;
//int menuSt = 0;
byte goSt = 0;

byte counterGo = 0;
byte serialSt = 1;
byte tundaMenu = 5;
volatile long blinkCount = 0;
int ledState = LOW;
int buzzerState = LOW;

#define value1 800
#define value2 600
#define value3 5
#define value4 1000

int read_buttons() {
  btnValue = analogRead(btnOledPin);
  //Serial.println(btnValue);
  if (btnValue > value4) return NONE;     //#define value1 800
  if (btnValue < value3)  return btn3;    //#define value2 600
  if (btnValue < value2)  return btn2;    //#define value3 5
  if (btnValue < value1)  return btn1;    //#define value4 1000
}

void setupOled() {
  Wire.begin();
  pinMode(btnOledPin, INPUT);
  if (!Oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  } else  Serial.println(F("SSD1306 Done"));
  Oled.clearDisplay();
  Oled.display();
  //pinMode(btnOledPin, OUTPUT);
  
  //digitalWrite(ledOledPin, HIGH);
  //  Timer3.initialize(50000);
  //  Timer3.attachInterrupt(blinkLED);
  frame0();
  Oled.clearDisplay();
}

unsigned long oldt, counter;
void timerOled() {
  unsigned long t_tunda = millis();
  if (t_tunda - oldt > 100) {
    oldt = t_tunda;
    if (counter < 1000) counter++;
    else counter = 0;
    if (counter % 10 == 0) {
      //Serial.print("menuSt ");
      //Serial.println(menuSt);
      //Serial.print("runSt ");
      //Serial.println(runSt);
    }
    if (menuSt == 0) {
      //if (counter % 5 == 0) framePitStop();
    } else {
      if (tundaMenu > 0) {
        if (counter % 10 == 0) tundaMenu--;
        //Serial.print("tundaMenu ");
        //Serial.println(tundaMenu);
      } else {
        if (runSt == 0) {
          menuSt = 0;
          runSt = 0;
          Oled.clearDisplay();
          framePitStop();
          beep();
        }
      }
    }
    //=============READY TO GO==================
    if (menuSt == 1000) {
      if (counter % 10 == 0) {
        if (counterGo > 0) {
          counterGo--;
          //beepOled();
          beep();
        } else {
          counterGo = 0;
          goSt = startPoint;
          menuSt = 1001;
          //================
          runSt = 1;
          runDemoSt = 1;
          //================
        }
        Oled.clearDisplay();
        tulisT (32, 0, 2, "ACTION");
        if (counterGo > 0) {
          tulisI (51, 30, 4, counterGo);
        }
        else {
          tulisT (41, 30, 4, "GO");
          activeSt = 1;
        }
      }
    }

    //==========================================
    if (tekanSt == 1) {
      counterTombol++;
      //Serial.println(counterTombol);
    }
  }
}

void testOledSt() {
  pinMode(btnOledPin, INPUT);
  if (analogRead(btnOledPin) > 1000) {

    oledSt = 1;
    setupOled();
    Serial.print("Oled Installed ");

  } else {
    oledSt = 0;
    Serial.print("Oled NA ");
  }
  Serial.println(analogRead(btnOledPin));
  
  delay(1000);
  
}

byte beepSt = 0;
long goStTemp;
void oledNavigator() {
  if (runSt == 0) {
    if (clrSt == 0) {
      Oled.clearDisplay();
      clrSt = 1;
    }
  } else {
    clrSt = 0;
  }

  //if (menuSt == 4)
  timerOled();
  key = read_buttons();
  //Serial.print("Button ");
  //Serial.println(key);
  switch (key) {
    case btn1:
      //Serial.print("SATU");
      //Serial.println(key);
      if (menuSt == 1001) {
        //runSt = 0;
        beep();

        stop();
      } else {
        tekanSt = 1;
        tundaMenu = 10;
        if (counterTombol >= 6) {
          Oled.clearDisplay();
          framePitStop();
          beep();
          menuSt = 0;
        }
      }
      //delay(200);
      break;
    case btn2: {
        //Serial.print("DUA");
        //Serial.println(key);
        tundaMenu = 10;
        if (menuSt == 0) {
          menuSt = 1000;
          counterGo = 4;
        } else if (menuSt == 1001) {
          stop();
          beep();
        } else {
          tambah();
          if (menuSt == 10) {
            menuSt = 100;
            frameRunning("Step Number : ", JS);
          } else if (menuSt == 11) {
            menuSt = 20;
            framePID("Kp :", Kp);
          } else if (menuSt == 12) {
            menuSt = 30;
            frameBody("Coxa :", cx);
          } else if (menuSt == 13) {
            menuSt = 40;
            frameKalibrasi("Coxa (A" + String(1) + ")", calA[1]);
          }
        }
        break;
      }
    case btn3: {
        //Serial.print("TIGA");
        //Serial.println(key);
        tundaMenu = 10;
        //Serial.println("Botton3");
        if (menuSt == 1001) {
          stop();
          beep();
        } else if ((menuSt >= 10) and (menuSt <= 13)) {
          Oled.clearDisplay();
          framePitStop();
          //beepOled();
          beep();
          menuSt = 0;
        } else {
          kurang();
        }
        beepOled();
        break;
      }
    case NONE: {
        if (serialSt == 1) {
          serialSt = 0;
        }
        if ((counterTombol > 0) and (counterTombol <= 5))  mainMenu();
        tekanSt = 0;
        counterTombol = 0;
        beepSt = 0;
        break;
      }
  }
}

void stop() {
  runSt = 0;
  runDemoSt = 0;
  Oled.clearDisplay();
  tulisT (32, 0, 2, "ACTION");
  tulisT (21, 30, 4, "STOP");
  delay(2000);
  Oled.clearDisplay();
  framePitStop();
  menuSt = 0;
  beepOled();
  // jumlahLangkah = 0;
}

void mainMenu() {
  if (menuSt == 108) {
    menuSt = 10;
  }
  if (menuSt == 107) {
    menuSt = 108;
    frameRunning("Z Axis :", zAxis);
  }
  if (menuSt == 106) {
    menuSt = 107;
    frameRunning("Y Axis :", yAxis);
  }

  if (menuSt == 105) {
    menuSt = 106;
    frameRunning("X Axis :", xAxis);
  }
  if (menuSt == 104) {
    menuSt = 105;
    frameRunning("Lift :", lift);
  }

  if (menuSt == 103) {
    menuSt = 104;
    frameRunning("Wide :", wide);
  }
  if (menuSt == 102) {
    menuSt = 103;
    frameRunning("Delay :", dly);

  }
  if (menuSt == 101) {
    menuSt = 102;
    frameRunning("Speed :", xspd);
  }
  if (menuSt == 100) {
    menuSt = 101;
    frameRunning("Gaits :", gaitsMode);
  }

  //=======================
  if (menuSt == 64) {
    menuSt = 65;
    int x = menuSt - 59;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);

  }
  if (menuSt == 63) {
    menuSt = 64;
    int x = menuSt - 59;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);

  }
  if (menuSt == 62) {
    menuSt = 63;
    int x = menuSt - 59;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
  }

  if (menuSt == 61) {
    menuSt = 62;
    int x = menuSt - 59;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
  }

  if (menuSt == 60) {
    menuSt = 61;
    int x = menuSt - 59;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
  }

  if (menuSt == 55) {
    menuSt = 60;
    int x = menuSt - 59;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);

  }
  //=====================
  if (menuSt == 54) {
    menuSt = 55;
    int x = menuSt - 49;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);

  }
  if (menuSt == 53) {
    menuSt = 54;
    int x = menuSt - 49;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);

  }
  if (menuSt == 52) {
    menuSt = 53;
    int x = menuSt - 49;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);

  }
  if (menuSt == 51) {
    menuSt = 52;
    int x = menuSt - 49;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);

  }

  if (menuSt == 50) {
    menuSt = 51;
    int x = menuSt - 49;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);

  }
  if (menuSt == 45) {
    menuSt = 50;
    int x = menuSt - 49;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);

  }
  //=====================
  if (menuSt == 45) {
    menuSt = 46;
    int x = menuSt - 39;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);

  }

  if (menuSt == 44) {
    menuSt = 45;
    int x = menuSt - 39;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);

  }
  if (menuSt == 43) {
    menuSt = 44;
    int x = menuSt - 39;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);

  }
  if (menuSt == 42) {
    menuSt = 43;
    int x = menuSt - 39;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);

  }
  if (menuSt == 41) {
    menuSt = 42;
    int x = menuSt - 39;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);

  }
  if (menuSt == 40) {
    menuSt = 41;
    int x = menuSt - 39;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);

  }

  //=====================
  if (menuSt == 33) {
    menuSt = 12; //kalibrasi
  }

  if (menuSt == 32) {
    menuSt = 33;
    frameBody("Zo :", Zo);

  }

  if (menuSt == 31) {
    menuSt = 32;
    frameBody("Tibia :", tb);
  }

  if (menuSt == 30) {
    menuSt = 31;
    frameBody("Femur :", fm);
  }

  if (menuSt == 22) {
    menuSt = 11;
    //  frameBody("Coxa :", cx);
  }

  if (menuSt == 21) {
    menuSt = 22;
    framePID("Kd :", Kd);
  }

  if (menuSt == 20) {
    menuSt = 21;
    framePID("Ki :", Ki);
  }

  if (menuSt == 12) {
    menuSt = 13;
    Oled.clearDisplay();
    tulisT (0, 0, 2, "CALBRTION?");
    frameFootNoteMode();
  }

  if (menuSt == 11) {
    menuSt = 12;
    Oled.clearDisplay();
    tulisT (0, 0, 2, "BODY");
    tulisT (60, 8, 1, "VARIABLE ?");
    frameFootNoteMode();
  }

  if (menuSt == 10) {
    menuSt = 11;
    Oled.clearDisplay();
    tulisT (0, 0, 2, "PID");
    tulisT (50, 8, 1, "VARIABLE ?");
    frameFootNoteMode();
  }

  if (menuSt == 5) {
    menuSt = 10;
    Oled.clearDisplay();
    tulisT (0, 0, 2, "RUN");
    tulisT (50, 8, 1, "VARIABLE ?");
    frameFootNoteMode();
  }
  //Front Distance
  if (menuSt == 4) {
    menuSt = 5;
    frameGoPoint("Fire Limit", fireLimit);
  }

  if (menuSt == 3) {
    menuSt = 4;
    frameGoPoint("Front Distance", frontDistance);
  }
  if (menuSt == 2) {
    menuSt = 3;
    frameGoPoint("Wall Distance", wallDistance);

  }
  if (menuSt == 1) {
    menuSt = 2;
    frameGoPoint("Stop Point", stopPoint);

  }
  if (menuSt == 0) {
    menuSt = 1;
    frameGoPoint("Start Point", startPoint);
    //beep();
  }
}

void frameKalibrasi() {
  tulisT (0, 0, 2, "CAL. ");
}

void frame0() {
  Oled.clearDisplay();
  tulisT (15, 0, 2, "KALACAKRA");

  Oled.display();
}

void frameRunning() {
  Oled.clearDisplay();
  tulisT (15, 0, 2, " RUNNING");
  tulisI (60, 30, 2, runSt);
  Oled.display();
}

void framePitStop() {
  Oled.fillRect(0, 0, 127, 14, 0);
  tulisT (40, 0, 2, "HOME");
  Oled.drawLine(0, 15, 128, 15, 1);
  Oled.drawRect(0, 16, 128, 25, 1);

  //teganganBaterai();
  tulisT (98, 3, 1, String(batPct, 0));
  tulisT (120, 3, 1, "%");
  bacaApi();
  ukurJarak();
  for (int x = 0; x < 5; x++) {
    Oled.fillRect(x * 25 + 5, 20, 20, 8, 0);
    tulisI (x * 25 + 5, 20, 1, api[x + 1]);
    Oled.fillRect(x * 25 + 5, 30, 20, 8, 0);
    tulisI (x * 25 + 5, 30, 1, jarak[x]);
  }

  tulisT (0, 45, 1, "GAITS"); tulisI (35, 45, 1, gaitsMode);
  tulisT (80, 45, 1, "STEPS"); tulisI (115, 45, 1, JS);

  tulisT (0, 57, 1, "STR"); tulisI (23, 57, 1, startPoint);
  tulisT (48, 57, 1, "STP"); tulisI (70, 57, 1, stopPoint);
  tulisT (92, 57, 1, "SPD"); tulisI (115, 57, 1, xspd);

  if (digitalRead(bluetoothStatusPin) == HIGH) Oled.drawBitmap(5, 0, logo_bt, LOGO_WIDTH, LOGO_HEIGHT, 1); Oled.display();
}

void frameFootNote() {
  tulisT (0, 38, 1, "1 >>    2 ++     3 --");
  tulisT (0, 50, 1, "Hold 1 to HOME");
  tulisI (110, 57, 1, menuSt);
}

void frameFootNoteMode() {
  tulisT (0, 25, 2, "1>  2Y  3N");
  tulisT (0, 47, 1, "Hold 1 to HOME");
  tulisI (110, 57, 1, menuSt);
}

void frameFootNoteRunMode1() {
  tulisT (0, 38, 1, "1 >>    2 ++     3 --");
  tulisT (0, 47, 1, "Hold 1 to HOME");
  tulisI (110, 57, 1, menuSt);
}

void frameKalibrasi(String t, int v) {
  Oled.clearDisplay();
  tulisT (0, 0, 2, "CALIBRTION");
  tulisT (0, 20, 1, t);
  tulisI (90, 17, 2, v);
  frameFootNote();
}

void frameRunning(String t, int v) {
  Oled.clearDisplay();
  tulisT (0, 0, 2, "RUN");
  tulisT (60, 8, 1, "VARIABLE:");
  frameFootNote();
  tulisT (0, 20, 1, t);
  tulisI (90, 17, 2, v);
}

void frameBody(String t, int v) {
  Oled.clearDisplay();
  tulisT (0, 0, 2, "BODY");
  tulisT (60, 8, 1, "VARIABLE:");
  tulisT (0, 20, 1, t);
  tulisI (70, 17, 2, v);
  frameFootNote();
}

void framePID(String t, float v) {
  Oled.clearDisplay();
  tulisT (0, 0, 2, "PID");
  tulisT (60, 8, 1, "VARIABLE:");
  tulisT (0, 20, 1, t);
  tulisF (60, 17, 2, v);
  frameFootNote();
}

void frameGoPoint(String t, float v) {
  Oled.clearDisplay();
  tulisT (0, 0, 2, "HOME");
  tulisT (60, 8, 1, "VARIABLE:");
  tulisT (0, 20, 1, t);
  tulisI (90, 17, 2, v);
  frameFootNote();
}

void tambah() {
  if (menuSt == 1) {
    if (startPoint < stopPoint - 1) startPoint++;
    frameGoPoint("Start Point", startPoint);
    saveRunningVariable();
  }

  if (menuSt == 2) {
    if (stopPoint < 99)
      stopPoint++;
    frameGoPoint("Stop Point", stopPoint);
    saveRunningVariable();
  }
  if (menuSt == 3) {
    if (wallDistance < 99)
      wallDistance++;
    frameGoPoint("Wall Distance", wallDistance);
    saveRunningVariable();
  }
  if (menuSt == 4) {
    if (frontDistance < 99)
      frontDistance++;
    frameGoPoint("Front Distance", frontDistance);
    saveRunningVariable();
  }
  if (menuSt == 5) {
    if (fireLimit < 5000) fireLimit += 5;
    frameGoPoint("Front Distance", fireLimit);
    saveRunningVariable();
  }
  //=============================
  if (menuSt == 100) {
    JS = 6;
    frameRunning("Step Number : ", JS);
    saveRunningVariable();
  }
  if (menuSt == 101) {
    if (gaitsMode < 3) gaitsMode++; else gaitsMode = 1;
    frameRunning("Gaits Mode : ", gaitsMode);
    saveRunningVariable();
  }
  if (menuSt == 102) {
    if (xspd < 20) xspd++;
    spd = 23 - xspd;
    frameRunning("Speed :", xspd);
    saveRunningVariable();
  }
  if (menuSt == 103) {
    if (dly < 500) dly += 10;
    frameRunning("Delay :", dly);
    saveRunningVariable();
  }

  if (menuSt == 104) {
    if (wide < 30) wide++;
    frameRunning("Wide :", wide);
    saveRunningVariable();
  }
  if (menuSt == 105) {
    if (lift < 30) lift++;
    frameRunning("Lift :", lift);
    saveRunningVariable();
  }

  if (menuSt == 106) {
    if (xAxis < 120) xAxis++;
    frameRunning("X Axis :", xAxis);
    saveRunningVariable();
  }
  if (menuSt == 107) {
    if (yAxis < 120)yAxis++;
    frameRunning("Y Axis :", yAxis);
    saveRunningVariable();
  }

  if (menuSt == 108) {
    if (zAxis < 60)zAxis++;
    frameRunning("Z Axis :", zAxis);
    saveRunningVariable();
  }

  if (menuSt == 20) {
    Kp++;
    framePID("Kp :", Kp);
    savePIDvariable();
  }
  if (menuSt == 21) {
    Ki += 0.1;
    framePID("Ki :", Ki);
    savePIDvariable();
  }
  if (menuSt == 22) {
    Kd += 0.1;
    framePID("Kd :", Kd);
    savePIDvariable();
  }
  //=====================

  if (menuSt == 33) {
    if (Zo < 80) Zo++;
    frameBody("Zo :", Zo);
    saveBodyVariable();
  }

  if (menuSt == 32) {
    if (tb < 150) tb++;
    frameBody("Tibia :", tb);
    saveBodyVariable();
  }

  if (menuSt == 31) {
    if (fm < 150) fm++;
    frameBody("Femur :", fm);
    saveBodyVariable();
  }

  if (menuSt == 30) {
    if (cx < 50) cx++;
    frameBody("Coxsa :", cx);
    saveBodyVariable();
  }

  //=====================
  if (menuSt == 45) {
    //menuSt = 45;
    int x = menuSt - 39;
    if (calA[x] < 20) calA[x] ++;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 44) {
    //menuSt = 45;
    int x = menuSt - 39;
    if (calA[x] < 20) calA[x] ++;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 43) {
    //menuSt = 44;
    int x = menuSt - 39;
    if (calA[x] < 20) calA[x] ++;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 42) {
    //menuSt = 43;
    int x = menuSt - 39;
    if (calA[x] < 20) calA[x] ++;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 41) {
    //menuSt = 42;
    int x = menuSt - 39;
    if (calA[x] < 20) calA[x] ++;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 40) {
    //menuSt = 41;
    int x = menuSt - 39;
    if (calA[x] < 20) calA[x] ++;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  //=====================
  if (menuSt == 55) {
    //menuSt = 50;
    int x = menuSt - 49;
    if (calB[x] < 20) calB[x] ++;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 54) {
    //menuSt = 55;
    int x = menuSt - 49;
    if (calB[x] < 20) calB[x] ++;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 53) {
    // menuSt = 54;
    int x = menuSt - 49;
    if (calB[x] < 20) calB[x] ++;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 52) {
    //menuSt = 53;
    int x = menuSt - 49;
    if (calB[x] < 20) calB[x] ++;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 51) {
    // menuSt = 52;
    int x = menuSt - 49;
    if (calB[x] < 20) calB[x] ++;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 50) {
    //menuSt = 51;
    int x = menuSt - 49;
    if (calB[x] < 20) calB[x] ++;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }

  //=======================
  if (menuSt == 65) {
    //menuSt = 60;
    int x = menuSt - 59;
    if (calC[x] < 20) calC[x] ++;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 64) {
    //menuSt = 65;
    int x = menuSt - 59;
    if (calC[x] < 20) calC[x] ++;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 63) {
    // menuSt = 64;
    int x = menuSt - 59;
    if (calC[x] < 20) calC[x] ++;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 62) {
    //menuSt = 63;
    int x = menuSt - 59;
    if (calC[x] < 20) calC[x] ++;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }


  if (menuSt == 61) {
    //menuSt = 62;
    int x = menuSt - 59;
    if (calC[x] < 20) calC[x] ++;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 60) {
    // menuSt = 61;
    int x = menuSt - 59;
    if (calC[x] < 20) calC[x] ++;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }

}

void kurang() {
  if (menuSt == 1) {
    if (startPoint > 0) startPoint--;
    frameGoPoint("Start Point", startPoint);
    saveRunningVariable();
  }

  if (menuSt == 2) {
    if (stopPoint > startPoint + 1) stopPoint--;
    frameGoPoint("Stop Point", stopPoint);
    saveRunningVariable();
  }
  if (menuSt == 3) {
    if (wallDistance > 2) wallDistance--;
    frameGoPoint("Wall Distance", wallDistance);
    saveRunningVariable();
  }
  if (menuSt == 4) {
    if (frontDistance > 5) frontDistance--;
    frameGoPoint("Front Distance", frontDistance);
    saveRunningVariable();
  }
  if (menuSt == 5) {
    if (fireLimit > 100) fireLimit -= 5;
    frameGoPoint("Front Distance", fireLimit);
    saveRunningVariable();
  }
  if (menuSt == 100) {
    //JS = 3;
    frameRunning("Step Number : ", JS);
    saveRunningVariable();
  }
  if (menuSt == 101) {
    //if (gaitsMode < 3) gaitsMode++; else gaitsMode = 1;
    if (gaitsMode > 1) gaitsMode--; else gaitsMode = 3;
    if (gaitsMode == 1) {
      //JS = 6;
    }
    frameRunning("Gaits Mode : ", gaitsMode);
    saveRunningVariable();
  }

  if (menuSt == 102) {
    if (xspd > 1) xspd--;
    spd = 23 - xspd;
    frameRunning("Speed :", xspd);
    saveRunningVariable();
  }

  if (menuSt == 103) {
    if (dly > 0) dly -= 10;
    frameRunning("Delay :", dly);
    saveRunningVariable();
  }
  if (menuSt == 104) {
    if (wide > 0) wide--;
    frameRunning("Wide :", wide);
    saveRunningVariable();
  }
  if (menuSt == 105) {
    if (lift > 5) lift--;
    frameRunning("Lift :", lift);
    saveRunningVariable();
  }
  if (menuSt == 106) {
    if (xAxis > cx + 10) xAxis--;
    frameRunning("X Axis :", xAxis);
    saveRunningVariable();
  }

  if (menuSt == 107) {
    if (yAxis > 0) yAxis--;
    frameRunning("Y Axis :", yAxis);
    saveRunningVariable();
  }
  if (menuSt == 108) {
    if (zAxis > 0) zAxis--;
    frameRunning("Z Axis :", zAxis);
    saveRunningVariable();
  }

  if (menuSt == 20) {
    //menuSt = 20;
    if (Kp > 3) Kp--;
    framePID("Kp :", Kp);
    savePIDvariable();
  }
  if (menuSt == 21) {
    if (Ki > 0) Ki -= 0.1;
    framePID("Ki :", Ki);
    savePIDvariable();
  }
  if (menuSt == 22) {
    if (Kd > 0) Kd -= 0.1;
    framePID("Kd :", Kd);
    savePIDvariable();
  }


  //=====================

  if (menuSt == 33) {
    if (Zo > 0) tb--;
    frameBody("Zo :", Zo);
    saveBodyVariable();
  }

  if (menuSt == 32) {
    if (tb > 50) tb--;
    frameBody("Tibia :", tb);
    saveBodyVariable();
  }

  if (menuSt == 31) {
    if (fm > 50) fm--;
    frameBody("Femur :", fm);
    saveBodyVariable();
  }

  if (menuSt == 30) {
    if (cx > 20) cx--;
    frameBody("Coxsa :", cx);
    saveBodyVariable();
  }

  //=====================
  if (menuSt == 45) {
    //menuSt = 45;
    int x = menuSt - 39;
    if (calA[x] > -20) calA[x] --;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 44) {
    //menuSt = 45;
    int x = menuSt - 39;
    if (calA[x] > -20) calA[x] --;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 43) {
    //menuSt = 44;
    int x = menuSt - 39;
    if (calA[x] > -20) calA[x] --;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 42) {
    //menuSt = 43;
    int x = menuSt - 39;
    if (calA[x] > -20) calA[x] --;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 41) {
    //menuSt = 42;
    int x = menuSt - 39;
    if (calA[x] > -20) calA[x] --;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 40) {
    //menuSt = 41;
    int x = menuSt - 39;
    if (calA[x] > -20) calA[x] --;
    frameKalibrasi("Coxa (A" + String(x) + ")", calA[x]);
    saveCalibrationVariable();
  }
  //=====================
  if (menuSt == 55) {
    //menuSt = 50;
    int x = menuSt - 49;
    if (calB[x] > -20) calB[x] --;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 54) {
    //menuSt = 55;
    int x = menuSt - 49;
    if (calB[x] > -20) calB[x] --;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 53) {
    // menuSt = 54;
    int x = menuSt - 49;
    if (calB[x] > -20) calB[x] --;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 52) {
    //menuSt = 53;
    int x = menuSt - 49;
    if (calB[x] > -20) calB[x] --;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 51) {
    // menuSt = 52;
    int x = menuSt - 49;
    if (calB[x] > -20) calB[x] --;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 50) {
    //menuSt = 51;
    int x = menuSt - 49;
    if (calB[x] > -20) calB[x] --;
    frameKalibrasi("Femur (B" + String(x) + ")", calB[x]);
    saveCalibrationVariable();
  }


  //=======================
  if (menuSt == 65) {
    //menuSt = 60;
    int x = menuSt - 59;
    if (calC[x] > -20) calC[x] --;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 64) {
    //menuSt = 65;
    int x = menuSt - 59;
    if (calC[x] > -20) calC[x] --;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 63) {
    // menuSt = 64;
    int x = menuSt - 59;
    if (calC[x] > -20) calC[x] --;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
  if (menuSt == 62) {
    //menuSt = 63;
    int x = menuSt - 59;
    if (calC[x] > -20) calC[x] --;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }


  if (menuSt == 61) {
    //menuSt = 62;
    int x = menuSt - 59;
    if (calC[x] > -20) calC[x] --;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }

  if (menuSt == 60) {
    // menuSt = 61;
    int x = menuSt - 59;
    if (calC[x] > -20) calC[x] --;
    frameKalibrasi("Tibia (C" + String(x) + ")", calC[x]);
    saveCalibrationVariable();
  }
}

void blinkLED(void) {
  blinkCount = blinkCount + 1;  // increase when LED turns on
  if (menuSt == 0) {
    if (blinkCount % 50 == 0) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    if (blinkCount % 500 <= 1) {
      buzzerState = HIGH;
    } else {
      buzzerState = LOW;
    }
  }
  if (menuSt >= 1000) {
    if (blinkCount % 15 == 0) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    if (blinkCount % 200 <= 1) {
      buzzerState = HIGH;
    } else {
      buzzerState = LOW;
    }
  }
  digitalWrite(ledOledPin, ledState);
  //if (buzzerState == HIGH) tone(A1, 3136, 1); else noTone(A1);
  // digitalWrite(buzzerPin, buzzerState);
}

void beepOled() {
  blinkCount = -1;
}

void tulisI(int x, int y, int s, int t) {
  Oled.setTextColor(putih);
  Oled.setCursor(x, y);
  Oled.setTextSize(s);
  Oled.print(t);
  Oled.display();
}
void tulisT(int x, int y, int s, String t) {
  Oled.setTextColor(putih);
  Oled.setCursor(x, y);
  Oled.setTextSize(s);
  Oled.print(t);
  Oled.display();
}
void tulisF(int x, int y, int s, float t) {
  Oled.setTextColor(putih);
  Oled.setCursor(x, y);
  Oled.setTextSize(s);
  Oled.print(t, 1);
}

void tulis(int x, int y, int s, int t) {
  Oled.setTextColor(putih);
  Oled.setCursor(x, y);
  Oled.setTextSize(s);
  Oled.print(t);
}

void tulisTt(int x, int y, int s, String t) {
  Oled.setTextColor(hitam);
  Oled.setCursor(x, y);
  Oled.setTextSize(s);
  Oled.print(t);
  Oled.display();
}

/*

*/
