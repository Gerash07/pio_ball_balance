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

float step(uint32_t time, uint32_t period, float min_out, float max_out)
{
  if(time/period % 2)
  {
    return min_out;
  }
  return max_out;
}

void controllerTick (Overlord &over)
{
    float setPoint = -over.getSetpoint ();
    // float carX = -over.getCarX ();
    // float carVel = -over.getCarVel ();
    float motorAngle = over.getMotorTheta ();
    float motorVel = over.getMotorVel ();

    bool button = !digitalRead(13);
    float fi0 = button * over.getSlider(SliderEnum::prog1)* 1.0 / 1000 ;

    float w, err1, u, w0, err0;

    


    static float constexpr Ts = 0.006;

    static float constexpr Kp = 0.51;
    static float constexpr Ki = 100;
    static float constexpr Kpf = 5;
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
    err0 = fi0 - motorAngle;
    float eKpf = err0 * Kpf;
    err1 = eKpf - motorVel;
    float eKpw = err1 * Kp;
    u = eKpw + I;

    if( u == constrain(u, -12, 12) || I*err1*Ki < 0)
    {
        I += eKpw*Ki*Ts;
    }



    // uint32_t time = millis();
    // w = over.getMotorVel();

    // u = step(time, 2000, 0, 10); // 0 если время не пришло, 10 если время пришло


    // Serial.print(time);
    Serial.print(w0);
    Serial.print(" ");
    Serial.print(u);
    Serial.print(" ");
    Serial.println(motorVel);


    // Serial.print(' ');
    
    over.setMotorU (u);
}
