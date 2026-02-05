# ⚡ Energy Monitoring Controller

Contrôleur d’énergie basé sur Arduino permettant la mesure en temps réel de la tension, du courant, de la puissance et de l’énergie consommée.

Ce projet a été conçu comme une brique matérielle simple, fiable et réutilisable pour des systèmes énergétiques (batteries, panneaux solaires, bancs de test, micro-réseaux, etc.).

---

## 🚀 Fonctionnalités

- 📏 Mesure de la tension (V)
- 🔌 Mesure du courant (mA)
- ⚡ Calcul de la puissance (W)
- 🔋 Calcul de l’**énergie consommée (Wh)**
- 📦 Calcul de la charge (mAh)
- ⏱️ Échantillonnage périodique configurable
- 🔄 Remise à zéro des compteurs via commande série
- 🔌 Transmission des données via Serial (USB)

---

## 🧠 Principe de fonctionnement

Le microcontrôleur (Arduino) lit les données d’un capteur INA219 via le bus I2C.  
À chaque période d’échantillonnage :

1. La tension et le courant sont mesurés
2. La puissance instantanée est calculée
3. L’énergie (Wh) et la charge (mAh) sont intégrées dans le temps
4. Les données sont envoyées au format CSV ou JSON via la liaison série

Ces données peuvent ensuite être :
- affichées en temps réel
- stockées dans une base de données
- exploitées par un Raspberry Pi (InfluxDB, Grafana, Python, etc.)

---

## 🧰 Matériel utilisé

- Arduino (UNO / Nano / ESP32 compatible)
- Capteur de courant INA219
- Câbles I2C (SDA / SCL)
- Source d’alimentation + charge à mesurer
- (Optionnel) Raspberry Pi pour visualisation et stockage

---

## 🔌 Connexions (Arduino UNO)

| INA219 | Arduino |
|------|---------|
| VCC  | 5V      |
| GND  | GND     |
| SDA  | A4      |
| SCL  | A5      |

> ⚠️ Le shunt du INA219 doit être placé en série avec la charge.

---

## 📦 Dépendances logicielles

- Arduino IDE
- Librairie :
  - Adafruit INA219

Installation :
```txt
Arduino IDE → Library Manager → Search "Adafruit INA219" → Install
