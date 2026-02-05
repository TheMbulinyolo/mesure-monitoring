#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

// ---- Réglages ----
const unsigned long SAMPLE_PERIOD_MS = 500;
const bool OUTPUT_JSON = false;   

// ---- Accumulateurs énergie ----
double energy_Wh = 0.0; 
double charge_mAh = 0.0; 
unsigned long lastSampleMs = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Wire.begin();

  if (!ina219.begin()) {
    Serial.println("ERR: INA219 not detected");
    while (1) { delay(1000); }
  }

  ina219.setCalibration_32V_2A(); 

  Serial.println("OK: INA219 ready");
  lastSampleMs = millis();
}

void loop() {
  unsigned long now = millis();
  if (now - lastSampleMs < SAMPLE_PERIOD_MS) return;

  double dt_s = (now - lastSampleMs) / 1000.0; 
  lastSampleMs = now;

  // ---- Mesures INA219 ----
  float busVoltage_V = ina219.getBusVoltage_V();        
  float shuntVoltage_mV = ina219.getShuntVoltage_mV();   
  float current_mA = ina219.getCurrent_mA();             
  float power_mW = ina219.getPower_mW();                 

  float loadVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000.0);

  // ---- Calcul énergie ----
  double power_W = power_mW / 1000.0;

  energy_Wh += power_W * (dt_s / 3600.0);

  charge_mAh += current_mA * (dt_s / 3600.0);

  // ---- Sortie ----
  if (OUTPUT_JSON) {
    Serial.print("{\"t_ms\":");
    Serial.print(now);
    Serial.print(",\"V\":");
    Serial.print(loadVoltage_V, 3);
    Serial.print(",\"I_mA\":");
    Serial.print(current_mA, 2);
    Serial.print(",\"P_W\":");
    Serial.print(power_W, 3);
    Serial.print(",\"E_Wh\":");
    Serial.print(energy_Wh, 5);
    Serial.print(",\"Q_mAh\":");
    Serial.print(charge_mAh, 5);
    Serial.println("}");
  } else {
    Serial.print(now);
    Serial.print(",");
    Serial.print(loadVoltage_V, 3);
    Serial.print(",");
    Serial.print(current_mA, 2);
    Serial.print(",");
    Serial.print(power_W, 3);
    Serial.print(",");
    Serial.print(energy_Wh, 5);
    Serial.print(",");
    Serial.println(charge_mAh, 5);
  }

  // ---- Commandes série simples ----
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toUpperCase();

    if (cmd == "RESET") {
      energy_Wh = 0.0;
      charge_mAh = 0.0;
      Serial.println("OK: counters reset");
    }
  }
}