byte a1, a2, a3, a4, a5, a6, b1, b2, b3, b4, b5, b6, c1, c2, c3, c4, c5, c6, g1, g2, g3;
byte tunda = 100;

byte calibStA = 1;
byte calibStB = 1;
byte calibStC = 1;

byte posGp = 28;//80 28
byte posUd = 150;//0=bawah 150 atas
byte gripperSt = 0;
byte UDSt = 0;

void activeServo(byte x) {
  switch  (x) {
    case 1:
      a1 = 38, b1 = 39, c1 = 40;
      a2 = 18, b2 = 19, c2 = 22;
      a3 = 35, b3 = 33, c3 = 37;
      a4 = 6,  b4 = 8,  c4 = 9;
      a5 = 32, b5 = 34, c5 = 36;
      a6 = 2,  b6 = 3,  c6 = 4;
      g1 = 45, g2 = 46, g3 = 47;
      break;
  }
  OPEN_SERVO_CALIBRATION_VALUE(1);
  activeGriper();
  delay(500);
  activeLeg1(); delay(tunda);// kaki 1
  activeLeg2(); delay(tunda);// kaki 2
  activeLeg3(); delay(tunda);// kaki 3
  activeLeg4(); delay(tunda);// kaki 4
  activeLeg5(); delay(tunda);// kaki 5
  activeLeg6(); delay(tunda);// kaki 6

  //UDSt = 0;
  //tarok();
  //delay(1000);
  //UDSt = 1;
  //angkat();
  //gripperOpen();
  //gripperClose();
}


void setupServo(byte x) {
  Serial.print ("Test Value AdL[1] ");
  Serial.println (Adl1);
  if ((Adl1 > 0) and (Adl1 < 180)) {
    activeServo(x);
    readySt = 1;
    testSt = 0;
    Serial.println ("READY TO RUN");
  } else {
    readySt = 0;
    testSt = 0;
    Serial.println ("NOT READY ");
    beep();
  }
  Serial.println();
  printOut = 0;
}

void activeLeg1() {
  if (calibStA == 1)srv_1A.attach(a1, 745, 2800); srv_1A.write(pos_1A); delay(tunda);
  if (calibStB == 1)srv_1B.attach(b1, 745, 2800); srv_1B.write(pos_1B); delay(tunda);
  if (calibStC == 1)srv_1C.attach(c1, 745, 2800); srv_1C.write(pos_1C);//delay(tunda);
}

void activeLeg2() {
  if (calibStA == 1)srv_2A.attach(a2, 745, 2800); srv_2A.write(pos_2A); delay(tunda);
  if (calibStB == 1)srv_2B.attach(b2, 745, 2800); srv_2B.write(pos_2B); delay(tunda);
  if (calibStC == 1)srv_2C.attach(c2, 745, 2800); srv_2C.write(pos_2C);//delay(tunda);
}

void activeLeg3() {
  if (calibStA == 1)srv_3A.attach(a3, 745, 2800); srv_3A.write(pos_3A); delay(tunda);
  if (calibStB == 1)srv_3B.attach(b3, 745, 2800); srv_3B.write(pos_3B); delay(tunda);
  if (calibStC == 1)srv_3C.attach(c3, 745, 2800); srv_3C.write(pos_3C);//delay(tunda);
}

void activeLeg4() {
  if (calibStA == 1)srv_4A.attach(a4, 745, 2800); srv_4A.write(pos_4A); delay(tunda);
  if (calibStB == 1)srv_4B.attach(b4, 745, 2800); srv_4B.write(pos_4B); delay(tunda);
  if (calibStC == 1)srv_4C.attach(c4, 745, 2800); srv_4C.write(pos_4C);//delay(tunda);
}

void activeLeg5() {
  if (calibStA == 1)srv_5A.attach(a5, 745, 2800); srv_5A.write(pos_5A); delay(tunda);
  if (calibStB == 1)srv_5B.attach(b5, 745, 2800); srv_5B.write(pos_5B); delay(tunda);
  if (calibStC == 1)srv_5C.attach(c5, 745, 2800); srv_5C.write(pos_5C);//delay(tunda);
}

void activeLeg6() {
  if (calibStA == 1)srv_6A.attach(a6, 745, 2800); srv_6A.write(pos_6A); delay(tunda);
  if (calibStB == 1)srv_6B.attach(b6, 745, 2800); srv_6B.write(pos_6B); delay(tunda);
  if (calibStC == 1)srv_6C.attach(c6, 745, 2800); srv_6C.write(pos_6C);//delay(tunda);
}

void servoRun() {
  srv_1A.write(pos_1A);    srv_1B.write(pos_1B);    srv_1C.write(pos_1C);
  srv_2A.write(pos_2A);    srv_2B.write(pos_2B);    srv_2C.write(pos_2C);
  srv_3A.write(pos_3A);    srv_3B.write(pos_3B);    srv_3C.write(pos_3C);
  srv_4A.write(pos_4A);    srv_4B.write(pos_4B);    srv_4C.write(pos_4C);
  srv_5A.write(pos_5A);    srv_5B.write(pos_5B);    srv_5C.write(pos_5C);
  srv_6A.write(pos_6A);    srv_6B.write(pos_6B);    srv_6C.write(pos_6C);
}

void step0() {
  srv_1A.write(pos_1A); delay(tunda);  srv_1B.write(pos_1B); delay(tunda);  srv_1C.write(pos_1C); delay(tunda);
  srv_2A.write(pos_2A); delay(tunda);  srv_2B.write(pos_2B); delay(tunda);  srv_2C.write(pos_2C); delay(tunda);
  srv_3A.write(pos_3A); delay(tunda);  srv_3B.write(pos_3B); delay(tunda);  srv_3C.write(pos_3C); delay(tunda);
  srv_4A.write(pos_4A); delay(tunda);  srv_4B.write(pos_4B); delay(tunda);  srv_4C.write(pos_4C); delay(tunda);
  srv_5A.write(pos_5A); delay(tunda);  srv_5B.write(pos_5B); delay(tunda);  srv_5C.write(pos_5C); delay(tunda);
  srv_6A.write(pos_6A); delay(tunda);  srv_6B.write(pos_6B); delay(tunda);  srv_6C.write(pos_6C); delay(tunda);
}

void setServoA(int x, int p) {
  myservoA.attach(x);
  myservoA.write(p);
}

void setServoB(int x, int p) {
  myservoB.attach(x);
  myservoB.write(p);
}

void setServoC(int x, int p) {
  myservoC.attach(x);
  myservoC.write(p);
}

int pos = 0;
void testServo(int x) {
  myservoC.attach(x);
  for (pos = 60; pos <= 60; pos += 1) {
    myservoC.write(pos);
    delay(25);
  }

  for (pos = 60; pos >= 60; pos -= 1) {
    myservoC.write(pos);
    delay(25);
  }
}
