#define USE_USBCON

#include <Arduino.h>
#include <SoftPWM.h>
#include <ros.h>

#include <std_msgs/Int16.h>

#include <MotorDC.h>

#define MOTOR_A1 11 // D11
#define MOTOR_A2 10 // D10

#define MOTOR_B1 9  // D9
#define MOTOR_B2 3  // SCL

#define MOTOR_C1 A0 // A0
#define MOTOR_C2 A1 // A1

void motorSpeedCallback(MotorDC *motor, const std_msgs::Int16 &speed);

MotorDC motorA(MOTOR_A1, MOTOR_A2);
MotorDC motorB(MOTOR_B1, MOTOR_B2);
MotorDC motorC(MOTOR_C1, MOTOR_C2, true);

ros::NodeHandle  nh;

ros::Subscriber<std_msgs::Int16> motorASpeedSub("motor_a/motor_speed",
    [](const std_msgs::Int16 &speed) {
        motorSpeedCallback(&motorA, speed);
    });

ros::Subscriber<std_msgs::Int16> motorBSpeedSub("motor_b/motor_speed",
    [](const std_msgs::Int16 &speed) {
        motorSpeedCallback(&motorB, speed);
    });

ros::Subscriber<std_msgs::Int16> motorCSpeedSub("motor_c/motor_speed",
    [](const std_msgs::Int16 &speed) {
        motorSpeedCallback(&motorC, speed);
    });

void setup()
{
    pinMode(13, OUTPUT);

    SoftPWMBegin();

    nh.initNode();
    nh.subscribe(motorASpeedSub);
    nh.subscribe(motorBSpeedSub);
    nh.subscribe(motorCSpeedSub);
}

void loop()
{
    nh.spinOnce();
}

void motorSpeedCallback(MotorDC *motor, const std_msgs::Int16 &speed)
{
    motor->drive(speed.data);
}