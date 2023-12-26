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

    float K = 0.68;
    float Kp = 8;

    float err = w0 - motorVel;

    float u = Kp * err;


    Serial.print(w0);
    Serial.print(' ');
    Serial.print(u);
    Serial.print(' ');
    Serial.println(motorVel);
    
    over.setMotorU (u);
}
