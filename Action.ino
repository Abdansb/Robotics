void moveTo(int a) {
  long y = millis();
  
  runStep
  (AdL[s1[a]], AdR[s2[a]], AtL[s3[a]], AtR[s4[a]], AbL[s5[a]], AbR[s6[a]],

   BdL[s1[a]] - U1[a], BdR[s2[a]] - U2[a],
   BtL[s3[a]] - U2[a], BtR[s4[a]] - U1[a],
   BbL[s5[a]] - U1[a], BbR[s6[a]] - U2[a],

   CdL[s1[a]] + W1[a], CdR[s2[a]] + W2[a],
   CtL[s3[a]] + W2[a], CtR[s4[a]] + W1[a],
   CbL[s5[a]] + W1[a], CbR[s6[a]] + W2[a], sp);
  delay(dly);
  if (runSt == 1) numberStep += 1;
  if (runSt == 2) numberStep -= 1;
  runtStepNumber++;
  if (a == addStep) {//addStep
    jumlahLangkah++;
    //Serial.print("jumlahLangkah, ");
    //Serial.println(jumlahLangkah);
  }
}

void action_1(int a) {
  //spd = 12;
  directionSt = 9;
  runStep
  (110, 70,     130,    45,     AbL[1], AbR[1],
   15, 15,      45,     45, BbL[1], BbR[1],
   180,  180,   45,     45, CbL[1], CbR[1], sp);
  runStep
  (70, 110,     130,    45,     AbL[1], AbR[1],
   15, 15,      45,     45, BbL[1], BbR[1],
   180, 180,    45,     45, CbL[1], CbR[1], sp);
}

void stby0(int a) {
  //spd = 12;
  runStep
  (AdL[1], AdR[1], AtL[1], AtR[1], AbL[1], AbR[1],
   BdL[1], BdR[1], BtL[1], BtR[1], BbL[1], BbR[1],
   CdL[1], CdR[1], CtL[1], CtR[1], CbL[1], CbR[1], sp);
  runStep
  (70, 110, 90, AtR[1], AbL[1], AbR[1],
   15, 15, BtL[1], BtR[1], BbL[1], BbR[1],
   180, 180, CtL[1], CtR[1], CbL[1], CbR[1], sp);
}

void geserKiri(byte x) {
  left = 1;
  right = 1;
  if (directionSt != 11) {
    moveToCalculation(3);
    directionSt = 11;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }
  if (x != 0) {
    if (jumlahLangkah < x) moveTo(langkah);
    else {
      //jumlahLangkah = 0;
    }
  } else moveTo(langkah);
}

void geserKanan(byte x) {
  left = 1;
  right = 1;
  if (directionSt != 12) {
    moveToCalculation(4);
    directionSt = 12;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }
  if (x != 0) {
    if (jumlahLangkah < x) moveTo(langkah);
    else {
      //jumlahLangkah = 0;
    }
  } else moveTo(langkah);
}

void maju(long x) {
  left = 1;
  right = 1;
  if (directionSt != 1) {
    moveToCalculation(1);
    directionSt = 1;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }

  if (x != 0) {
    if (jumlahLangkah < x) moveTo(langkah);
    else {
      jumlahLangkah = 0;
    }
  } else moveTo(langkah);

}

void mundurAction(long s, float x, float y, float z, int n) {
  left = 1; right = 1; yAxis = y; xAxis = x; zAxis = z;
  if (directionSt != 11) {
    moveToCalculation(1);
    directionSt = 11;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }

  if (s != 0) {
    if (jumlahLangkah < s) moveTo(langkah);
    else {
      jumlahLangkah = 0;
      runSt = n;
    }
  } else moveTo(langkah);

}

void majuAction(long s, float x, float y, float z, int spid, byte nextSt) {
  left = 1; right = 1; yAxis = y; xAxis = x; zAxis = z;
  spd = spid;
  if (directionSt != 22) {
    moveToCalculation(1);
    directionSt = 22;
  }
  if (langkah > 1) {
    numberStep -= 1;
    langkah--;
  } else {
    langkah = addStep;
  }
  if (s != 0) {
    if (jumlahLangkah < s) moveTo(langkah);
    else {
      jumlahLangkah = 0;
      runSt = nextSt;
    }
  }  else moveTo(langkah);
}

void mundur1(long s) {//mundur setelah menarok korban
  if (directionSt != 2) {
    moveToCalculation(1);
    directionSt = 2;
  }
  if (langkah > 1) {
    numberStep -= 1;
    langkah--;
  } else {
    langkah = addStep;
  }
  if (s != 0) {
    if (jumlahLangkah < s) moveTo(langkah);
    else {
      jumlahLangkah = 0;
      //gripperClose();
      //angkat();
      //runSt = 61;
    }
  }  else moveTo(langkah);
}

void mundur(long s) {
  if (directionSt != 2) {
    moveToCalculation(1);
    directionSt = 2;
  }
  if (langkah > 1) {
    numberStep -= 1;
    langkah--;
  } else {
    langkah = addStep;
  }
  if (s != 0) {
    if (jumlahLangkah < s) moveTo(langkah);
    else {
      jumlahLangkah = 0;
      runSt = 99;
    }
  }  else moveTo(langkah);
}

void putarKiriAction(long s, float x, float y, float z, float n, int next) {
  left = 1; right = 1; yAxis = y; xAxis = x; zAxis = z;
  spd = n;
  if (directionSt != 33) {
    moveToCalculation(2);
    directionSt = 33;
  }
  if (langkah > 1) {
    numberStep -= 1;
    langkah--;
  } else {
    langkah = addStep;
  }
  
  if (s != 0) {
    if (jumlahLangkah < s) {
      moveTo(langkah);
    } else {
      jumlahLangkah = 0;
      runSt = next;
      frameRunning();
    }
  } else moveTo(langkah);
}

void putarKananAction(long s, float x, float y, float z, float n, int next) {
  left = 1; right = 1; yAxis = y; xAxis = x; zAxis = z;
  spd = n;
  if (directionSt != 44) {
    moveToCalculation(2);
    directionSt = 44;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }
  if (s != 0) {
    if (jumlahLangkah < s) {
      moveTo(langkah);
    } else {
      jumlahLangkah = 0;
      runSt = next;
      frameRunning();
    }
  } else moveTo(langkah);
}
void putarKanan(long s) {
  if (directionSt != 3) {
    moveToCalculation(2);
    directionSt = 3;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }
  if (s != 0) {
    if (jumlahLangkah < s) {
      moveTo(langkah);
    } else {

    }
  } else moveTo(langkah);
}



void putarKiri(long s) {
  if (directionSt != 4) {
    moveToCalculation(2);
    directionSt = 4;
  }
  if (langkah > 1) {
    numberStep -= 1;
    langkah--;
  } else {
    langkah = addStep;
  }
  if (s != 0) {
    if (jumlahLangkah < s) moveTo(langkah);
    else {

    }
  } else moveTo(langkah);
}

void belokKanan(float d) {
  left = d;
  right = 1;
  if (directionSt != 5) {
    moveToCalculation(1);
    directionSt = 5;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
  } else {
    langkah = 1;
  }
  moveTo(langkah);
}

void belokKiri(float d) {
  left = 1;
  right = d;
  if (directionSt != 6) {
    moveToCalculation(1);
    directionSt = 6;
  }
  if (langkah < addStep) {
    langkah++;
    numberStep += 1;
    moveTo(langkah);
  } else {
    langkah = 1;
  }
  moveTo(langkah);
}

void activeGriper() {
  pinMode(kipasPin, OUTPUT);
  digitalWrite(kipasPin, HIGH);
  srv_GR.attach(g1); srv_GR.write(posGp); delay(tunda);// Gripper 100 tutup, 30 buka
  srv_UP.attach(g2); srv_UP.write(posUd); delay(tunda);// 0 UP  180 Down
}

// gripper 95 tutup, 30 buka

void gripperOpen() {
  if (gripperSt == 0) {
    for (posGp = 28; posGp <= 90; posGp += 1) {
      srv_GR.write(posGp);
      delay(20);
    }
    gripperSt = 1;
  }
}

void gripperClose() {
  if (gripperSt == 1) {
    for (posGp = 90; posGp >= 28; posGp -= 1) {
      srv_GR.write(posGp);
      delay(15);
    }
    gripperSt = 0;
  }

}

void angkat() {
  if (UDSt == 1) {
    for (posUd = 1; posUd <= 150; posUd += 1) {
      srv_UP.write(posUd);
      delay(15);
    }
    UDSt = 0;
    gripperOpen();
  }
}

void tarok() {
  if (UDSt == 0) {
    for (posUd = 150; posUd >= 1; posUd -= 1) {
      srv_UP.write(posUd);
      delay(15);
    }
    UDSt = 1;
  }
}

void kipasOn() {
  digitalWrite(kipasPin, LOW);
}
void kipasOff() {
  digitalWrite(kipasPin, HIGH);
}
