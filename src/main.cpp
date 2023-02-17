#include <mbed.h>

DigitalOut MS3(p25), MS2(p26), MS1(p27), EN(p28), DIREC(p29), STEP(p30);

AnalogIn Pot(p20);

Timeout t;
//constant int for speed
const int VITESSE_ANGULAIRE_MAX_DEG_SEC = 720;
int target = 360;
int ppr = 200; //point par tour 
float vitesse = 0;
float tpp; //time per point

float speed(int dps)
{
  
  float period;

  tpp = (dps/360.0) * ppr;
  period = (1.0 / tpp)/2.0;
  return period;
}
void fct_step(void)
{
  STEP = !STEP;
  // wait for target
  vitesse = speed(target);
  t.attach(&fct_step, vitesse);
}	
int main()
{
  t.attach(&fct_step, 1.0);
  
  // put your setup code here, to run once:
  // set value of MS3,MS2,MS1 to 0
  MS3 = 0;
  MS2 = 0;
  MS1 = 0;
  // set value of EN to 0
  EN = 0;
  // set value of DIR to 1
  DIREC = 1;
  while (1)
  {
    float adc = Pot.read_u16();
    float vitesse_angulaire = adc * VITESSE_ANGULAIRE_MAX_DEG_SEC / 65535.0;
    float test = tpp *2 * 3.14159265359;
    printf("vitesse = %f test = %fdegree/s\r\n", vitesse_angulaire, test);
    // convertir la vitesse angulaire en vitesse angulaire en deg/s
    target = vitesse_angulaire;
    
  }
}