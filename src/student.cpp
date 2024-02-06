#include "student.h"

/**
 * @brief Инициализировать систему управления
 * @details Вызывется один раз перед вызовом
 * функции \p controllerTick
 */
void controllerInit (Overlord &over)
{
    over.setSlider (SliderEnum::prog1, -12000, 12000);
    over.setSlider (SliderEnum::prog2, -10000, 10000);
}

/**
 * @brief Выполнить одну итерацию системы управления
 * @details Вызывается раз в 5мс
 */

void controllerTick (Overlord &over)
{
    float setPoint = -over.getSetpoint ();
    // float carX = -over.getCarX ();
    // float carVel = -over.getCarVel ();
    float motorAngle = over.getMotorTheta ();
    float motorVel = over.getMotorVel ();

    bool button = !digitalRead(13);
    float w0 = button * over.getSlider(SliderEnum::prog1)* 1.0 / 1000 ;

    float w, err1, u;

    


    static float constexpr Ts = 0.006;

    static float constexpr Kp = 2;
    static float constexpr Ki = 4;
    static float I = 0;
    static float P;


    // err1 = w0 - motorVel;
    // P = err1*Kp;

    // err1 = w0 - motorVel;
    // I += err1*Ki*Ts;
    // u = I;

    // err1 = w0 - motorVel;
    // u = I;
    // if( constrain(u, -12, 12) == I || I*err1*Ki < 0)
    // {
    //     I += err1*Ki*Ts;
    // }

    err1 = w0 - motorVel;
    float eKp = err1*Kp;
    u = eKp + I;

    if( u == constrain(u, -12, 12) || I*err1*Ki < 0)
    {
        I += eKp*Ki*Ts;
    }
    


    Serial.print(w0);
    Serial.print(' ');
    Serial.print(u);
    Serial.print(' ');
    Serial.println(motorVel);
    
    over.setMotorU (u);
}
