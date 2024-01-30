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
float w = 0;
void controllerTick (Overlord &over)
{
    float setPoint = -over.getSetpoint ();
    // float carX = -over.getCarX ();
    // float carVel = -over.getCarVel ();
    float motorAngle = over.getMotorTheta ();
    float motorVel = over.getMotorVel ();

    bool button = !digitalRead(13);
    float w0 = button * over.getSlider(SliderEnum::prog1)* 1.0 / 1000 ;

    float w, fi, w0, err1, err2;

    static float constexpr T1 = 0,006;
    static float constexpr Tmu = 0,035;
    static float constexpr K = 0,68;


    static float constexpr Kk = T1/(2*K*Tmu);
    static float constexpr Kk2 = 8;


    // err1 = fi0 - motorAngle;
    // w0 = Kk2 * err;

    err2 = w0 - motorVel;
    P = err2*Kk

    static float I = 0;
    float Iin = err2 * Kk
    if( constrain(I, -12, 12) == I || Iin*I < 0)
    {
        float I += Iin * T1; 
    }

    float u0 = P+I



    Serial.print(w0);
    Serial.print(' ');
    Serial.print(u);
    Serial.print(' ');
    Serial.println(motorVel);
    
    over.setMotorU (u);
}
