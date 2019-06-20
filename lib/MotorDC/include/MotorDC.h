#ifndef _MOTORDC_H
#define _MOTORDC_H


class MotorDC {
public:
    MotorDC(int pinA, int pinB, bool use_softpwm = false);

    void drive(int speed);

private:
    int m_pinA;
    int m_pinB;
    bool m_softpwm;
};


#endif // _MOTORDC_H
