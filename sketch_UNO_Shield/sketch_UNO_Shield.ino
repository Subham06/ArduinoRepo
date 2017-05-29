
#define FILTERSETTLETIME 5000                                           //  Time (ms) to allow the filters to settle before sending data

const int CT1 = 1; 
const int CT2 = 0;                                                      // Set to 0 to disable CT channel 2
const int CT3 = 0;                                                      // Set to 0 to disable CT channel 3
const int CT4 = 0; 
                                              // Frequency of RF12B module can be RF12_433MHZ, RF12_868MHZ or RF12_915MHZ. You should use the one matching the module you have.
                                          // emonTx RFM12B wireless network group - needs to be same as emonBase and emonGLCD

const int UNO = 0;                                                      // Set to 0 if your not using the UNO bootloader (i.e using Duemilanove) - All Atmega's shipped from OpenEnergyMonitor come with Arduino Uno bootloader
#include <avr/wdt.h>                                                     

#include <JeeLib.h>   // make sure V12 (latest) is used if using RFM69CW
ISR(WDT_vect) { Sleepy::watchdogEvent(); }                              // Attached JeeLib sleep function to Atmega328 watchdog -enables MCU to be put into sleep mode inbetween readings to reduce power consumption 

#include "EmonLib.h"
EnergyMonitor ct1,ct2,ct3,ct4;                                              // Create  instances for each CT channel

//typedef struct { int power1, power2, power3, power4, battery; } PayloadTX;      // create structure - a neat way of packaging data for RF comms
//PayloadTX emontx;                                                       

const int LEDpin = 9;                                                   // On-board emonTx LED 

boolean settled = false;

void setup() 
{
  Serial.begin(9600);
  Serial.println("emonTX CT1234 example"); 
  Serial.println("OpenEnergyMonitor.org");
             
  if (CT1) ct1.currentTX(1, 111.1);                                     // Setup emonTX CT channel (ADC input, calibration)
  if (CT2) ct2.currentTX(2, 111.1);                                     // Calibration factor = CT ratio / burden resistance
  if (CT3) ct3.currentTX(3, 111.1);                                     // Calibration factor = (100A / 0.05A) / 33 Ohms
  if (CT4) ct3.currentTX(4, 111.1);                                     // Calibration factor = (100A / 0.05A) / 33 Ohms
  
  


  pinMode(LEDpin, OUTPUT);                                              // Setup indicator LED
  digitalWrite(LEDpin, HIGH);
  
  //if (UNO) wdt_enable(WDTO_8S);                                         // Enable anti crash (restart) watchdog if UNO bootloader is selected. Watchdog does not work with duemilanove bootloader                                                             // Restarts emonTx if sketch hangs for more than 8s
}

void loop() 
{ 
  if (CT1) {
    double power1;
   
    power1 = ct1.calcIrms(1480) * 240.0;                         //ct.calcIrms(number of wavelengths sample)*AC RMS voltage
    Serial.println(power1);        
     Serial.print("  ");
      Serial.println(ct1.calcIrms(1480));
       Serial.print("  ");

                                             
  }
  
//  if (CT2) {
//    emontx.power2 = ct2.calcIrms(1480) * 240.0;
//    Serial.print(" "); Serial.print(emontx.power2);
//  } 
//
//  if (CT3) {
//    emontx.power3 = ct3.calcIrms(1480) * 240.0;
//    Serial.print(" "); Serial.print(emontx.power3);
//  } 
//
//   if (CT4) {
//    emontx.power4 = ct4.calcIrms(1480) * 240.0;
//    Serial.print(" "); Serial.print(emontx.power4);
//  } 
  
//  emontx.battery = ct1.readVcc();                                      //read emonTx battey (supply voltage)
  
//  Serial.print(" "); Serial.print(emontx.battery);
//  Serial.println(); 
delay(3000);

  // because millis() returns to zero after 50 days ! 
 
}

