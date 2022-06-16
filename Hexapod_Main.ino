#include "1_Variable.h"

byte printOut = 0;
int P36 = 6;

byte smothtly = 3; //1, 2, 3, 4
int JS = 18; //6, 12, 18, 24 smoothly
byte calSt = 1;
byte dir = 1;
byte pushSt = 1;//BT
byte btSt = 0;
byte clrSt = 0;
byte oledSt = 0;
byte kipasSt = 0;
byte apiSt = 0;
byte buzzerApiSt = 0;
int menuSt = 0;
byte activeSt = 0;
byte runSt = 0;
byte runDemoSt = 0;
//EEPROM.writeInt(405, fireLimit);

void setup() {
  Serial.begin(9600);//
  Serial.println();
  testOledSt();
  testBTSt();
  //EEPROM_ARR(3);

  if (calSt == 1) {
    gaitsTrajectoryCalculation(smothtly);
    moveToCalculation(dir);
    calSt = 0;
  }
  setupServo(1);
  kipasOn();
  //beep1();
  //beep();
  delay(500);
  pushSt = 0;
  kipasOff();
  Serial.print("yAxis ");
  Serial.println(yAxis);
}

void loop() { // pilih salah satu voidyg akan dijalankan
  //kalibrasi();
  //oledNavigator();
  //timer();
  //action();
  //setServoA(45, 90); // Gripper 100 tutup, 30 buka | 90 coxa
  //gripperOpen();
  //gripperClose();
  //setServoB(46);  //0 UP  150 Down | 10 femur tibia
  //testServo(47); // kipas | muter
  //teganganBaterai();
  //bacaApi();
  //ukurJarak();
  mainProgram();
}

void mainProgram() {
  oledNavigator();
  //bluetoothControl();
  if (calSt == 1) {
    gaitsTrajectoryCalculation(smothtly);
    moveToCalculation(dir);
    calSt = 0;
  } else {
    runningDemo();
    demoPutarKanan(50);
    //demoPutarKiri(5);
    //demoMaju(6);
    //runningMainProgram();
    //runningMainProgram1();
  }
  timer();
}

void runningDemo() {
  switch (runDemoSt) {
    case 0:
      break;
    case 1:
      demoTarok();

      //demoMundur(5);
      break;
    case 2:
      demoGripperOpen();
      //demoMundur(5);
      break;
    case 3:
      demoGripperClose();
      //demoPutarKiri(4);
      break;
    case 4:
      demoAngkat();
      //demoPutarKanan(5);
      break;
    case 5:
      // stop();
      demoMaju(5);
      //action();
      //runDemoSt = 6;
      break;
    case 6:
      demoPutarKanan(5);
      //stop();
      //action();
      break;
    case 7:
      demoPutarKiri(5);
      //stop();
      //action();
      break;
      case 8:
      demoMundur(5);
      //stop();
      //action();
      break;
      case 9:
      //demoMundur(5);
      stop();
      //action();
      break;
  }
}

void runningMainProgram() {
  switch (runSt) {
    case 0:
      break;
    case 1:
      maju(4);
      break;
    case 60:
      mundur(2);
      break;
  }
}

void runningMainProgram1() {
  if (activeSt == 1) {
    switch (runSt) {
      case 0:
        break;
      case 1:
        maju(0);
        //majuAction(0, 70, 50, 10, 99);
        //majuAction(0, 80, 30, 0, 99);
        break;
      case 2:
        belokKanan(0.5);
        break;
      case 3:
        putarKanan(0);
        break;
      case 5:
        mundur(0);
        break;
      case 7:
        putarKiri(0);
        break;
      case 8:
        belokKiri(0.5);
        break;
      case 9:
        //action();
        break;
      case 10:
        stanBy();
        break;
      case 11:
        geserKiri(2);
        break;
      case 12:
        geserKanan(2);
        break;
      case 13:
        setupServo(1);
        runSt = 0;
        break;
      case 60:
        //mundur1(3);
        break;
      case 61:
        //putarKanan1(6);
        break;
      case 20: // lilin
        bacaApi();
        break;
      case 21:
        padamkanLilin();
        break;
      case 22:
        putarKiriAction(2, 80, 50, 10, 15, 23);
        break;
      case 23:
        putarKananAction(3, 80, 50, 10, 15, 24);
        break;
      case 24:
        kipasOff();
        break;
      case 30:
        //        mundurAction(2, 80, 40, 10, 20, 31);
        break;
      case 31:
        putarKananAction(6, 80, 50, 10, 15, 32);
        break;
      case 32:
        //        mundurAction(2, 80, 40, 10, 20, 33);
        break;
      case 33:
        gripperClose();
        angkat();
        runSt = 34;
        break;
      case 34:
        putarKiriAction(6, 80, 50, 10, 15, 35);
        break;
      case 35:

        break;
    }


  }
}


void action() {
  if (langkah < addStep)
    langkah++;
  action_1(langkah);
}

void stanBy() {
  if (directionSt != 1) {
    moveToCalculation(2);
    directionSt = 1;
  }
  if (langkah >= addStep / 2) {
    if (langkah < addStep) {
      langkah++;
      moveTo(langkah);
    }
  } else if (langkah > 1) {
    numberStep -= 1;
    langkah--;
    moveTo(langkah);
  }
}
