void teganganBaterai() {
  for (int i = 0; i < 5; i++) {
    voltageReading += analogRead(bat2sSensPin);
    voltageReading1 += analogRead(bat1sSensPin);
    delay(1);
  }
  //voltageReading = voltageReading / 5 * 0.0082;// * calibFacV;
  //voltageReading1 = voltageReading1 / 5 * 0.004857;// * calibFacV;
  voltageReading = voltageReading / 5 * 0.008365;// * calibFacV;
  //voltageReading1 = voltageReading1 / 5 * 0.0057;// * calibFacV;
  batVol = voltageReading;
  batVol1 = voltageReading1;
  //Serial.print("V ");
  //Serial.println(voltageReading, 2);
  //Serial.print("V1 ");
  //Serial.println(voltageReading1, 2);
  //batPct = mapFloat(batVol, 6.2, 8.4, 0, 100);
  //batPct = (153 * batVol - 540) / 10;
  batPct = (78.2 * batVol - 544) * 0.94;
  //Serial.print("pct ");
  //Serial.println(batPct, 1);

  if (batPct < 0) batPct = 0; if (batPct > 100) batPct = 100;
  if (voltageReading <= 7.2) batSt = 0;
  else if (voltageReading <= 7.5) batSt = 1;
  else batSt = 2;

  sendToAndroidDevice("B", String(batPct)); //delay(10);
  sendToAndroidDevice("z", String(batVol) + " v"); //delay(10);
  sendToAndroidDevice("Z", String(batPct) + " %"); //delay(10);
  byte G = batPct;
  Serial3.print("*LR" + String(250 - (G * 2.5)) + "G" + String(G * 2.5) + "B" + String(0) + "*");
}


int oldJR, oldJL;
void ukurJarak() {
  //int x = millis();
  float j;
  for (uint8_t i = 0; i < jumlahPing; i++) {
    //for (uint8_t i = 0; i < 1; i++) {
    delay(2);
    j = pinG[i].ping_cm();
    if (j == 0) j = jarakMak;
    j = j;// - 12;
    if (j < 0) j == 0;
    jarak[i] = j;
  }
  //Serial.print("Jarak 0 "); Serial.println(jarak[0]);
  //Serial.print("Jarak 1 "); Serial.println(jarak[1]); //Depan B
  //Serial.print("Jarak 2 "); Serial.println(jarak[2]); //Depan A
  //Serial.print("Jarak 3 "); Serial.println(jarak[3]); //Kiri
  //Serial.print("Jarak 4 "); Serial.println(jarak[4]); //Kanan
  //Serial.print("Jarak 5 "); Serial.println(jarak[5]); //Blkg / kipas
  //Serial.print("Jarak 6 "); Serial.println(jarak[6]);
  //Serial.println();
  //delay(500);
  //int xx = millis();
  //Serial.print("time jarak ");
  //Serial.println(xx - x);
}

void jarakDepan() {
  float j = pinG[0].ping_cm();
  int x = millis();
  if (j == 0) j = jarakMak;
  j = j - 12;
  if (j < 0) j == 0;
  jarak[0] = j;
  //int xx = millis();
  //Serial.print("time dpn ");
  //Serial.println(xx - x);
}

void jarakKiri() {
  float j = pinG[1].ping_cm();
  if (j == 0) j = jarakMak;
  j = j - 12;
  if (j < 0) j == 0;
  jarak[1] = j;
}

void jarakKanan() {
  //int x = millis();
  float j = pinG[2].ping_cm();
  if (j == 0) j = jarakMak;
  j = j - 12;
  if (j < 0) j == 0;
  jarak[2] = j;
  //jarakDepan();
  //int xx = millis();
  //Serial.print("time kanan ");
  //Serial.println(xx - x);
}

void hitungJarakLilin() {
  //int x = millis();
  float j = pinG[5].ping_cm();
  if (j == 0) j = jarakMak;
  j = j;
  if (j < 0) j == 0;
  jarak[5] = j;
  jarakLilin = j;
  //jarakDepan();
  //int xx = millis();
  Serial.print("jarakLilin ");
  Serial.println(jarakLilin);
  //Serial.println(xx - x);
}

void bacaApi() {
  //fireLimit = 100;
  int posApi = 0, nilaiApi = 0;
  api[1] = analogRead(sApi1Pin);
  api[2] = analogRead(sApi2Pin);
  api[3] = analogRead(sApi3Pin);
  api[4] = analogRead(sApi4Pin);
  api[5] = analogRead(sApi5Pin);

  if ((((api[1] > fireLimit) or (api[2] > fireLimit)) or ((api[3] > fireLimit) or (api[4] > fireLimit))) or (api[5] > fireLimit))  {
    apiSt = 1;
  }

  if (apiSt == 1) {
    for (byte i = 1; i < 6; i++) {
      if (api[i] > nilaiApi) {
        nilaiApi = api[i];
        posApi = i;
      }
    }
    nilaiApi = 0;

    if (posApi != 3) {
      if (posApi < 3) {
        Serial.println("putar kiri");
        //putarKiriAction(long s, float x, float y, float z, float n, int next)
        putarKiriAction(0, 80, 50, 10, 10, 99);
        //if (buzzerApiSt == 1) tone(buzzerPin, 3136, 100);
      } else {
        Serial.println("putar kanan");
        putarKananAction(0, 80, 50, 10, 10, 99);
        //putarKananAction(long s, float x, float y, float z, float n, int next);
        // putarKananCariLilin(0);
        //if (buzzerApiSt == 1)tone(buzzerPin, 4186, 100);
      }
    } else {
      Serial.println("posisi api oke");
      runSt = 21;
      frameRunning();
    }
  }

  //==========================
  if (printOut == 4) {
    Serial.print("api :");
    Serial.print("\t");
    Serial.print(api[1]);
    Serial.print("\t");
    Serial.print(api[2]);
    Serial.print("\t");
    Serial.print(api[3]);
    Serial.print("\t");
    Serial.print(api[4]);
    Serial.print("\t");
    Serial.println(api[5]);

    Serial.print("nilaiApi :");
    Serial.print(nilaiApi);
    Serial.print(", posApi :");
    Serial.println(posApi);
  }
}

void padamkanLilin() {
  hitungJarakLilin();
  if (jarakLilin > 20) {
//    mundurAction(0, 80, 50, 10, 15, 99);
  } else {
    kipasOn();
    delay(1000);
    jumlahLangkah = 0;
    runSt = 22;
    frameRunning();
    apiSt = 0;
  }
}
