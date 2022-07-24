 //////////////////////////////////////////////////////////////////////////////
//                                                                            //
//          .----.   @   @                    _ _   www.github.com/snailware  //
//         / .-"-.`.  \v/     ___ _ __   __ _(_) |_      ____ _ _ __ ___      //
//         | | '\ \ \_/ )    / __| '_ \ / _` | | \ \ /\ / / _` | '__/ _ \     //
//       ,-\ `-.' /.'  /     \__ \ | | | (_| | | |\ V  V / (_| | | |  __/     //
//      '---`----'----'      |___/_| |_|\__,_|_|_| \_/\_/ \__,_|_|  \___|     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                     //                                     //
//            Adam Lancaster           //           Humidity Probe            //
//            07 / 24 / 2022           //   monitor & log relative humidity   //
//                                     //                                     //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    This script uses an Arduino UNO & DHT11 humidity sensor to monitor &    //
//    log relative humidity. for more info, see README.md or:                 //
//                                                                            //
//                https://github.com/snailware/humidity_probe                 //
//                                                                            //
 //////////////////////////////////////////////////////////////////////////////

#include <DHT.h>

#define sensor 2
#define blueLed 9
#define greenLed 10
#define redLed 11
#define dhtType DHT11

const int startupDelay = 1200; // 20 minutes, represented in seconds.
const float greenThreshold = 0.00;
const float yellowThreshold = 60.00;
const float redThreshold = 80.00;

float peakHumidity = 0.00;
DHT dht(sensor, dhtType);

void setup() {
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  for (int elapsedSeconds = 0; elapsedSeconds < startupDelay; elapsedSeconds++) {
    analogWrite(blueLed, 100);
    delay(50);
    analogWrite(blueLed, 0);
    delay(950);
  }

  dht.begin();
}

void loop() {
  float currentHumidity = dht.readHumidity();
  if (currentHumidity > peakHumidity) {
    peakHumidity = currentHumidity;
  }

  if (peakHumidity > greenThreshold && peakHumidity <= yellowThreshold) {
    analogWrite(greenLed, 100);
  } else if (peakHumidity > yellowThreshold && peakHumidity <= redThreshold) {
    analogWrite(greenLed, 60);
    analogWrite(redLed, 110);
  } else if (peakHumidity > redThreshold) {
    analogWrite(redLed, 100);
  }
  delay(50);
  analogWrite(greenLed, 0);
  analogWrite(redLed, 0);
  analogWrite(blueLed, 0);
  delay(950);
}
