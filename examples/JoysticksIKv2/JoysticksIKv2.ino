/* meArm IK joysticks - York Hackspace May 2014
 * Using inverse kinematics with joysticks
 * Uses two analogue joystcks (two pots each)
 * First stick moves gripper forwards, backwards, left and right
 * Second stick moves gripper up, down, and closes and opens.
 * 
 * I used Sparkfun thumbstick breakout boards, oriented 'upside down'.
 * 
 * Pins:
 * Arduino    Stick1    Stick2    Base   Shoulder  Elbow    Gripper
 *    GND       GND       GND    Brown     Brown   Brown     Brown
 *     5V       VCC       VCC      Red       Red     Red       Red
 *     A0       HOR
 *     A1       VER
 *     A2                 HOR
 *     A3                 VER
 *     11                       Yellow
 *     10                                 Yellow
 *      9                                         Yellow
 *      6                                                   Yellow
 */
#include "meArm.h"
#include <Servo.h>

int basePin = 11;
int shoulderPin = 10;
int elbowPin = 9;
int gripperPin = 6;

int xdirPin = 0;
int ydirPin = 1;
int zdirPin = 3;
int gdirPin = 2;

const int asweepMinBase = 145;
const int asweepMaxBase = 49;
const int asweepMinShoulder=118;
const int asweepMaxShoulder=22;
const int asweepMinElbow=144;
const int asweepMaxElbow=36;
const int asweepMinGripper=75;
const int asweepMaxGripper=115;

meArm arm(asweepMinBase, asweepMaxBase, -pi/4, pi/4,
      asweepMinShoulder, asweepMaxShoulder, pi/4, 3*pi/4,
      asweepMinElbow, asweepMaxElbow, pi/4, -pi/4,
      asweepMinGripper, asweepMaxGripper, pi/2, 0);

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
}

void loop() {
  float dx = map(analogRead(xdirPin), 0, 1023, -5.0, 5.0);
  float dy = map(analogRead(ydirPin), 0, 1023, 5.0, -5.0);
  float dz = map(analogRead(zdirPin), 0, 1023, 5.0, -5.0);
  float dg = map(analogRead(gdirPin), 0, 1023, 5.0, -5.0);
  if (abs(dx) < 1.5) dx = 0;
  if (abs(dy) < 1.5) dy = 0;
  if (abs(dz) < 1.5) dz = 0;
  
  if (!(dx == 0 && dy == 0 && dz == 0))
    arm.goDirectlyTo(arm.getX() + dx, arm.getY() + dy, arm.getZ() + dz);
  
  if (dg < -3.0)
    arm.closeGripper();
  else if (dg > 3.0)
    arm.openGripper();  
  delay(50);
}
