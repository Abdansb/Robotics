void demoMundur(long s) {
  if (directionSt != 2) {
    moveToCalculation(1);
    directionSt = 2;
  }
  if (langkah > 1) {
    numberStep -= 1;
    langkah--;
    Serial.print("Langkah, ");
    Serial.println(langkah);
  } else {
    langkah = addStep;
    Serial.print("addStep, ");
    Serial.println(addStep);
  }
  
  if (s != 0) {
    if (jumlahLangkah < s) moveTo(langkah);
    else {
      jumlahLangkah = 0;
      runDemoSt = 9;
    }
  }  else moveTo(langkah);
}

void demoMaju(long x) {
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
      runDemoSt = 6;
    }
  } else moveTo(langkah);
}

void demoPutarKanan(long s) {
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
      jumlahLangkah = 0;
      runDemoSt = 7;
    }
  } else moveTo(langkah);
}



void demoPutarKiri(long s) {
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
      jumlahLangkah = 0;
      runDemoSt = 8;
    }
  } else moveTo(langkah);
}

void demoBelokKanan(float d) {
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

void demoBelokKiri(float d) {
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







void demoTarok() {
  if (UDSt == 0) {
    for (posUd = 150; posUd >= 1; posUd -= 1) {
      srv_UP.write(posUd);
      delay(15);
    }
    UDSt = 1;
    runDemoSt = 2;
  }
}
void demoGripperOpen() {
  if (gripperSt == 0) {
    for (posGp = 28; posGp <= 90; posGp += 1) {
      srv_GR.write(posGp);
      delay(20);
    }
    gripperSt = 1;
    runDemoSt = 3;
  }
}
void demoGripperClose() {
  if (gripperSt == 1) {
    for (posGp = 90; posGp >= 28; posGp -= 1) {
      srv_GR.write(posGp);
      delay(15);
    }
    gripperSt = 0;
    runDemoSt = 4;
  }

}
void demoAngkat() {
  if (UDSt == 1) {
    for (posUd = 1; posUd <= 150; posUd += 1) {
      srv_UP.write(posUd);
      delay(15);
    }
    UDSt = 0;
    runDemoSt = 5;
  }
}
