/*
 * Date: 10/11/2020
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
#include <webots/supervisor.h>

#define TIME_STEP 256
#define QtddSensoresProx 8
#define QtddLeds 10



WbDeviceTag Leds[QtddLeds]; 

int main(int argc, char **argv) {
  
  int i=0;
  int times = 0;
  char texto[256];
  bool caixaMovel = false;
  int caixasMoveis = 0;
  double LeituraSensorProx[QtddSensoresProx];
  double AceleradorDireito=1.0, AceleradorEsquerdo=1.0;
  for(i=0;i<256;i++) texto[i]='0';
  
  
  wb_robot_init();
  //configurei MOTORES
  WbDeviceTag MotorEsquerdo, MotorDireito;
  MotorEsquerdo = wb_robot_get_device("left wheel motor");
  MotorDireito = wb_robot_get_device("right wheel motor");
  WbNodeRef robot_node = wb_supervisor_node_get_from_def("ePuck"); //captura o supervisor
  WbFieldRef trans_field = wb_supervisor_node_get_field(robot_node, "translation"); //identifica o campo de posição
  const double *posicao; //variáel que vai receber a posição do robo
     

   wb_motor_set_position(MotorEsquerdo, INFINITY);
   wb_motor_set_position(MotorDireito, INFINITY);
   wb_motor_set_velocity(MotorEsquerdo,0);
   wb_motor_set_velocity(MotorDireito,0);
   //configurei Sensores de Proximidade
   WbDeviceTag SensorProx[QtddSensoresProx];
   
   //config leds e sensores
   SensorProx[0] = wb_robot_get_device("ps0");
   wb_distance_sensor_enable(SensorProx[0],TIME_STEP);
   Leds[0] = wb_robot_get_device("led0");
   wb_led_set(Leds[0], 0);
   SensorProx[1] = wb_robot_get_device("ps1");
   wb_distance_sensor_enable(SensorProx[1],TIME_STEP);
   Leds[1] = wb_robot_get_device("led1");
   wb_led_set(Leds[1], 0);
   SensorProx[2] = wb_robot_get_device("ps2");
   wb_distance_sensor_enable(SensorProx[2],TIME_STEP);
   Leds[2] = wb_robot_get_device("led2");
   wb_led_set(Leds[2], 0);
   SensorProx[3] = wb_robot_get_device("ps3");
   wb_distance_sensor_enable(SensorProx[3],TIME_STEP);
   Leds[3] = wb_robot_get_device("led3");
   wb_led_set(Leds[3], 0);
   SensorProx[4] = wb_robot_get_device("ps4");
   wb_distance_sensor_enable(SensorProx[4],TIME_STEP);
   Leds[4] = wb_robot_get_device("led4");
   wb_led_set(Leds[4], 0);
   SensorProx[5] = wb_robot_get_device("ps5");
   wb_distance_sensor_enable(SensorProx[5],TIME_STEP);
   Leds[5] = wb_robot_get_device("led5");
   wb_led_set(Leds[5], 0);
   SensorProx[6] = wb_robot_get_device("ps6");
   wb_distance_sensor_enable(SensorProx[6],TIME_STEP);
   Leds[6] = wb_robot_get_device("led6");
   wb_led_set(Leds[6], 0);
   SensorProx[7] = wb_robot_get_device("ps7");
   wb_distance_sensor_enable(SensorProx[7],TIME_STEP);
   Leds[7] = wb_robot_get_device("led7");
   wb_led_set(Leds[7], 0);
   
 
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
    posicao = wb_supervisor_field_get_sf_vec3f(trans_field);
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
    
    //if(posicao[0] > -0.15 && posicao[0] < -0.15){
    if(posicao[0] > -0.64 && posicao[0] < -0.32 && posicao[2] > -0.64 && posicao[2] < -0.32){
    
        printf("if %s\n", texto);
        AceleradorEsquerdo = 1;
        AceleradorDireito = 1;
       
        //if ( LeituraSensorProx[1] > 950 || LeituraSensorProx[6] > 950){
        //|| LeituraSensorProx[2] > 1000 || LeituraSensorProx[5] > 1000){	
        if ( LeituraSensorProx[1] > 1000 || LeituraSensorProx[0] > 1000 || LeituraSensorProx[6] > 1000 || LeituraSensorProx[7] > 1000){	
            //ativa os leds necessarios
            wb_led_set(Leds[0], 1);
            wb_robot_step(165);
            wb_led_set(Leds[0], 0);
            wb_robot_step(165);
                
            wb_led_set(Leds[1], 1);
            wb_robot_step(165);
            wb_led_set(Leds[1], 0);
            wb_robot_step(165);
                
            wb_led_set(Leds[2], 1);
            wb_robot_step(165);
            wb_led_set(Leds[2], 0);
            wb_robot_step(165);
	//seta pra true ***
      	caixaMovel = true;
	caixasMoveis++; //
	//times++;
	printf("Vezes que detectou uma caixa movel: %d;\n", caixasMoveis);
	
  	for(i = 0; i < caixasMoveis; i++){
                 wb_led_set(Leds[i], 1);
  	}
	//caixaMovel = false;
        }
	//caixaMovel = false;
	//isso serve para trocar a direcao caso bata em alguma coisa (parede, por exemplo)
    }else if (LeituraSensorProx[7] > 390){
            AceleradorDireito = -0.17;
            AceleradorEsquerdo = 1.1;
    }else if (LeituraSensorProx[0] > 390){
            AceleradorDireito = 1.1;
            AceleradorEsquerdo = -0.17;
            //AceleradorDireito = 2;
            //AceleradorEsquerdo = -0.4;
    }else if (LeituraSensorProx[1] > 390){
            AceleradorDireito = 1;
            AceleradorEsquerdo = -0.18;
    }else if (LeituraSensorProx[6] > 390){
            AceleradorDireito = -0.18;
            AceleradorEsquerdo = 1;
    }else if (LeituraSensorProx[5] > 390){
            AceleradorDireito = -0.23;
            AceleradorEsquerdo = 1.1;
            //AceleradorDireito = 0;
            //AceleradorEsquerdo = -0.7;
    }else if (LeituraSensorProx[2] > 390){
            AceleradorDireito = 1.1;
            AceleradorEsquerdo = -0.23;
    }else{
            AceleradorDireito = 1;
            AceleradorEsquerdo = 1;
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
    
    wb_motor_set_velocity(MotorEsquerdo,4.85*AceleradorEsquerdo);
    wb_motor_set_velocity(MotorDireito, 4.85*AceleradorDireito);
    
    times++;

  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
