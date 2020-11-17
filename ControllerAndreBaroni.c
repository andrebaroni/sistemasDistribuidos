/*
 * Date:
 * Description:
 * Author: André Luiz Baroni
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <webots/accelerometer.h>

#define TIME_STEP 256
#define QtddSensoresProx 8
#define QtddLeds 10
#define aceleracaoVel 5



WbDeviceTag Leds[QtddLeds]; 
void ativaLeds(int xLeds, int valor);

int main(int argc, char **argv) {
  
  int i=0;
  int times = 0;
  char texto[256];
  bool caixaMovel = false;
  int caixasMoveis = 0;
  double aceleration[aceleracaoVel];
  double LeituraSensorProx[QtddSensoresProx];
  double AceleradorDireito=1.0, AceleradorEsquerdo=1.0;
  for(i=0;i<256;i++) texto[i]='0';
  for (i = 0; i < aceleracaoVel; i++) aceleration[i] = 0; 
  
  
  
  wb_robot_init();
  //configurei MOTORES
  WbDeviceTag MotorEsquerdo, MotorDireito, Acelerometro;
  Acelerometro = wb_robot_get_device("accelerometer");
  MotorEsquerdo = wb_robot_get_device("left wheel motor");
  MotorDireito = wb_robot_get_device("right wheel motor");
  wb_accelerometer_enable(Acelerometro, 10);
  const double* values = wb_accelerometer_get_values(Acelerometro); 

   wb_motor_set_position(MotorEsquerdo, INFINITY);
   wb_motor_set_position(MotorDireito, INFINITY);
   wb_motor_set_velocity(MotorEsquerdo,0);
   wb_motor_set_velocity(MotorDireito,0);
   //configurei Sensores de Proximidade
   WbDeviceTag SensorProx[QtddSensoresProx];
   
   
   SensorProx[0] = wb_robot_get_device("ps0");
   SensorProx[1] = wb_robot_get_device("ps1");
   SensorProx[2] = wb_robot_get_device("ps2");
   SensorProx[3] = wb_robot_get_device("ps3");
   SensorProx[4] = wb_robot_get_device("ps4");
   SensorProx[5] = wb_robot_get_device("ps5");
   SensorProx[6] = wb_robot_get_device("ps6");
   SensorProx[7] = wb_robot_get_device("ps7");
   wb_distance_sensor_enable(SensorProx[0],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[1],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[2],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[3],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[4],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[5],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[6],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[7],TIME_STEP);
   
    Leds[0] = wb_robot_get_device("led0");
    Leds[1] = wb_robot_get_device("led1");
    Leds[2] = wb_robot_get_device("led2");
    Leds[3] = wb_robot_get_device("led3");
    Leds[4] = wb_robot_get_device("led4");
    Leds[5] = wb_robot_get_device("led5");
    Leds[6] = wb_robot_get_device("led6");
    Leds[7] = wb_robot_get_device("led7");
    Leds[8] = wb_robot_get_device("led8");
    Leds[9] = wb_robot_get_device("led9");
    wb_led_set(Leds[0], 0);
    wb_led_set(Leds[1], 0);
    wb_led_set(Leds[2], 0);
    wb_led_set(Leds[3], 0);
    wb_led_set(Leds[4], 0);
    wb_led_set(Leds[5], 0);
    wb_led_set(Leds[6], 0);
    wb_led_set(Leds[7], 0);
    wb_led_set(Leds[8], 0);
    wb_led_set(Leds[9], 0);
   
    //config leds
    Leds[0] = wb_robot_get_device("led0");
    //wb_led_set(Leds[0],-1); //antigo, com -1
    wb_led_set(Leds[0], 0); //novo
  
  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  
  while (wb_robot_step(TIME_STEP) != -1) {
    for(i=0;i<256;i++) texto[i]=0;
    //memcpy(texto,0,10);
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
    /* Process sensor data here */
    for(i=0;i<QtddSensoresProx;i++){
       LeituraSensorProx[i]= wb_distance_sensor_get_value(SensorProx[i]); //sem 60
       sprintf(texto,"%s|%d: %5.2f  ",texto,i,LeituraSensorProx[i]);
    }
    aceleration[times % aceleracaoVel] = values[0] - values[1]; 
    double aclrMed = 0; 
    for (i = 0; i<aceleracaoVel;i++){ 
      aclrMed = aclrMed + aceleration[i]; 
      //aclrMed = aclrMed + aceleration[i+1]; 
    }
    aclrMed = aclrMed / aceleracaoVel; 
    
    //isso serve para trocar a direcao caso bata em alguma coisa (parede, por exemplo)
    if (aclrMed > 0.035 || aclrMed < -0.035){
        
        printf("if %s\n", texto);
        
        if (LeituraSensorProx[0] > 420){
            AceleradorDireito = 1;
            AceleradorEsquerdo = -0.1;
            //AceleradorDireito = 2;
            //AceleradorEsquerdo = -0.4;
        }else if (LeituraSensorProx[6] > 420){
            AceleradorDireito = -0.2;
            AceleradorEsquerdo = 1;
        }else if (LeituraSensorProx[2] > 420){
            AceleradorDireito = 1;
            AceleradorEsquerdo = -0.3;
        }else if (LeituraSensorProx[5] > 420){
            AceleradorDireito = -0.3;
            AceleradorEsquerdo = 1;
            //AceleradorDireito = 0;
            //AceleradorEsquerdo = -0.7;
        }else if (LeituraSensorProx[1] > 420){
            AceleradorDireito = 1;
            AceleradorEsquerdo = -0.2;
        }else if (LeituraSensorProx[7] > 420){
            AceleradorDireito = -0.1;
            AceleradorEsquerdo = 1;
        }else{
            AceleradorDireito = 1;
            AceleradorEsquerdo = 1;
        }
    }else{
    
        AceleradorEsquerdo = 1;
        AceleradorDireito = 1;
       
        if (!caixaMovel && ( LeituraSensorProx[1] > 1000 || LeituraSensorProx[0] > 1000 || LeituraSensorProx[6] > 1000 || LeituraSensorProx[7] > 1000)){
        	
        	for(i = 0; i < 3; i++){
                ativaLeds(10, 1);
                //ativa os leds necessarios
                wb_robot_step(100);
                //.
                ativaLeds(10, 0);
                //ativaLeds(10, 3);
                wb_robot_step(100);
	}
	//seta pra true ***
	caixaMovel = true;
	caixasMoveis++; //
	//times++;
	printf("Vezes que detectou uma caixa movel: %d;\n", caixasMoveis);
	//caixaMovel = false;
	}
	caixaMovel = false;
    }
    
    
    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
    /*
    if(LeituraSensorProx[0]>100){
      AceleradorDireito = -1;
      AceleradorEsquerdo = 1;}
    else {
      AceleradorDireito = 1;
      AceleradorEsquerdo = 1;}
 	*/
    
    wb_motor_set_velocity(MotorEsquerdo,6.28*AceleradorEsquerdo);
    wb_motor_set_velocity(MotorDireito, 6.28*AceleradorDireito);
    
    times++;

  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}

void ativaLeds(int xLeds, int valor){
    for(int i = 0; i < xLeds; i++){
       wb_led_set(Leds[i], valor);
    }
}