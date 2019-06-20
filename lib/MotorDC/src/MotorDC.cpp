#include <MotorDC.h>
#include <Arduino.h>
#include <SoftPWM.h>

#define PWM_WRITE(pin, value) analogWrite(pin, value)
#define SOFTPWM_WRITE(pin, value) SoftPWMSet(pin, value)

MotorDC::MotorDC(int pinA, int pinB, bool use_softpwm)
    : m_pinA(pinA), m_pinB(pinB), m_softpwm(use_softpwm)
{
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);

    if (use_softpwm) {
        SoftPWMSet(pinA, 0);
        SoftPWMSet(pinB, 0);
    }
}

void MotorDC::drive(int speed)
{
    if (speed >= 0) {
        if (m_softpwm) {
            SOFTPWM_WRITE(m_pinA, speed);
            SOFTPWM_WRITE(m_pinB, 0);
        }
        else {
            PWM_WRITE(m_pinA, speed);
            PWM_WRITE(m_pinB, 0);
        }
    }
    else if (speed < 0) {
        if (m_softpwm) {
            SOFTPWM_WRITE(m_pinA, 0);
            SOFTPWM_WRITE(m_pinB, -speed);
        }
        else {
            PWM_WRITE(m_pinA, 0);
            PWM_WRITE(m_pinB, -speed);
        }
    }
}
