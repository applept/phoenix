/**********************************************************
*   Phoenix FSW - Controls
*
*   25 Jan 2016
*
*   Joe Gibson 						(joseph.gibson@nasa.gov)
*	Jordi Vila Hernandez de Lorenzo	(jordi.vila.hdl@gmail.com)
*
*   License: MIT (http://gibsjose.mit-license.org)
*
*   https://github.com/gibsjose/phoenix
**********************************************************/

#include "phoenix-controls.h"

//Initialize variables
PID_Settings_t pid_settings_roll = {
    P_ROLL,               // Gain setting for the roll P-controller
    I_ROLL,              // Gain setting for the roll I-controller
    D_ROLL,                // Gain setting for the roll D-controller
    UPPER_LIMIT,               // Maximum output of the PID-controller
    LOWER_LIMIT,              // Minimum output of the PID-controller
};

PID_Settings_t *pid_settings_pitch = pid_settings_roll ;

PID_Settings_t pid_settings_yaw = {
    P_YAW,                 // Gain setting for the yaw P-controller
    I_YAW,              // Gain setting for the yaw I-controller
    D_YAW,                 // Gain setting for the yaw D-controller
    UPPER_LIMIT,               // Maximum output of the PID-controller
    LOWER_LIMIT,              // Minimum output of the PID-controller
};


//JVila: This should actually be on a interrput subroutine retrieving the length of the PWM pulses on the receiver pins...
void receiver_read(receiver_inputs_t * receiver){
 /*receiver->roll = ...
 receiver->pitch = ...
 receiver->gas = ...
 receiver->yaw = ...
 receiver_scale(receiver)*/
}

void receiver_scale(receiver_inputs_t * receiver){

//Scale ROLL
if(receiver->roll < SCALE_CENTER_ROLL){                 //The actual receiver value is lower than the center value
  if(receiver->roll < SCALE_MIN_ROLL){                  //The actual receiver value is lower than the minimum value
    receiver->roll_scaled = SCALE_MIN_ROLL;             //Limit the lowest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((SCALE_CENTER_ROLL - receiver->roll) * 500) / (SCALE_CENTER_ROLL - SCALE_MIN_ROLL);
      receiver->roll_scaled = 1500 - difference * REVERSE_ROLL;
  }
}
else if(receiver->roll > SCALE_CENTER_ROLL){            //The actual receiver value is higher than the center value
  if(receiver->roll > SCALE_MAX_ROLL){                  //The actual receiver value is higher than the maximum value
    receiver->roll_scaled = SCALE_MAX_ROLL;             //Limit the highest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((receiver->roll - SCALE_CENTER_ROLL) * 500) / (SCALE_MAX_ROLL - SCALE_CENTER_ROLL);
      receiver->roll_scaled = 1500 + difference * REVERSE_ROLL;
  }
}
else{
  receiver->roll_scaled = 1500;
}

//Scale PITCH
if(receiver->pitch < SCALE_CENTER_PITCH){                //The actual receiver value is lower than the center value
  if(receiver->pitch < SCALE_MIN_PITCH){                  //The actual receiver value is lower than the minimum value
    receiver->pitch_scaled = SCALE_MIN_PITCH;             //Limit the lowest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((SCALE_CENTER_PITCH - receiver->pitch) * 500) / (SCALE_CENTER_PITCH - SCALE_MIN_PITCH);
      receiver->pitch_scaled = 1500 - difference * REVERSE_PITCH;
  }
}
else if(receiver->pitch > SCALE_CENTER_PITCH){            //The actual receiver value is higher than the center value
  if(receiver->pitch > SCALE_MAX_PITCH){                  //The actual receiver value is higher than the maximum value
    receiver->pitch_scaled = SCALE_MAX_PITCH;             //Limit the highest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((receiver->pitch - SCALE_CENTER_PITCH) * 500) / (SCALE_MAX_PITCH - SCALE_CENTER_PITCH);
      receiver->pitch_scaled = 1500 + difference * REVERSE_PITCH;
  }
}
else{
  receiver->pitch_scaled = 1500;
}

//Scale GAS
if(receiver->gas < SCALE_CENTER_GAS){                 //The actual receiver value is lower than the center value
  if(receiver->gas < SCALE_MIN_GAS){                  //The actual receiver value is lower than the minimum value
    receiver->gas_scaled = SCALE_MIN_GAS;             //Limit the lowest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((SCALE_CENTER_GAS - receiver->gas) * 500) / (SCALE_CENTER_GAS - SCALE_MIN_GAS);
      receiver->gas_scaled = 1500 - difference * REVERSE_GAS;
  }
}
else if(receiver->gas > SCALE_CENTER_GAS){            //The actual receiver value is higher than the center value
  if(receiver->gas > SCALE_MAX_GAS){                  //The actual receiver value is higher than the maximum value
    receiver->gas_scaled = SCALE_MAX_GAS;             //Limit the highest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((receiver->gas - SCALE_CENTER_GAS) * 500) / (SCALE_MAX_GAS - SCALE_CENTER_GAS);
      receiver->gas_scaled = 1500 + difference * REVERSE_GAS;
  }
}
else{
  receiver->gas_scaled = 1500;
}

//Scale YAW
if(receiver->yaw < SCALE_CENTER_YAW){                 //The actual receiver value is lower than the center value
  if(receiver->yaw < SCALE_MIN_YAW){                  //The actual receiver value is lower than the minimum value
    receiver->yaw_scaled = SCALE_MIN_YAW;             //Limit the lowest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((SCALE_CENTER_YAW - receiver->yaw) * 500) / (SCALE_CENTER_YAW - SCALE_MIN_YAW);
      receiver->yaw_scaled = 1500 - difference * REVERSE_YAW;
  }
}
else if(receiver->yaw > SCALE_CENTER_YAW){            //The actual receiver value is higher than the center value
  if(receiver->yaw > SCALE_MAX_YAW){                  //The actual receiver value is higher than the maximum value
    receiver->yaw_scaled = SCALE_MAX_YAW;             //Limit the highest value to the value that was detected during setup
  }
  else{                                                 //Calculate and scale the actual value to a 1000 - 2000us value
      double difference = ((receiver->yaw - SCALE_CENTER_YAW) * 500) / (SCALE_MAX_YAW - SCALE_CENTER_YAW);
      receiver->yaw_scaled = 1500 + difference * REVERSE_YAW;
  }
}
else{
  receiver->yaw_scaled = 1500;
}

}

void calculate_setpoints(receiver_inputs_t * receiver, setpoints_t * setpoints){
  //Roll Setpoints
  //We need a little dead band of 16us for better results.
  if(receiver->roll > 1508){
      setpoints->roll = (receiver->roll - 1508)/MODE;
  }
  else if(receiver->roll < 1492){
      setpoints->roll = (receiver->roll - 1492)/MODE;
  }
  else{
    setpoints->roll = 0;
  }

  //Pitch Setpoints
  //We need a little dead band of 16us for better results.
  if(receiver->pitch > 1508){
      setpoints->pitch = (receiver->pitch - 1508)/MODE;
  }
  else if(receiver->roll < 1492){
      setpoints->pitch = (receiver->pitch - 1492)/MODE;
  }
  else{
    setpoints->pitch = 0;
  }

  //Yaw Setpoints
  //We need a little dead band of 16us for better results.
  if(receiver->yaw > 1508){
      setpoints->yaw = (receiver->yaw - 1508)/MODE;
  }
  else if(receiver->yaw < 1492){
      setpoints->yaw = (receiver->yaw - 1492)/MODE;
  }
  else{
    setpoints->yaw = 0;
  }
}

void pid_controller(PID_input_t * PID_input, PID_Settings_t * PID_settings, PID_output_t * PID_output){


  PID_output->error = PID_input->target - PID_input->measurement;               //Calculate error signal

  // Proportional contribution
  PID_output->P_contribution = PID_settings->KP * PID_output->error;

  // Integral contribution
  PID_output->I_contribution = PID_input->accomulated_error;                    //Dumb but clearer
  PID_output->I_contribution = PID_output->I_contribution  + PID_settings->KI * PID_output->error;

  if(PID_output->I_contribution > PID_settings->upper_limit){ // Do not let the Integral gain build up too much
    PID_output->I_contribution = PID_settings->upper_limit;
  }
  if(PID_output->I_contribution < PID_settings->lower_limit){
    PID_output->I_contribution = PID_settings->lower_limit;
  }
  PID_input->accomulated_error = PID_output->I_contribution; //To be used next time we compte the contribution

  // Derivative contribution
  PID_output->D_contribution = PID_settings->KD * (PID_output->error - PID_input->last_error);
  PID_input->last_error = PID_output->error;

  // Add up all the contributions to form the command signal
  PID_output->ut = PID_output->P_contribution + PID_output->I_contribution + PID_output->D_contribution;

  // Make sure we are not over the limits, coerce output
  if(PID_output->ut > PID_settings->upper_limit){
    PID_output->ut = PID_settings->upper_limit;
  }
  if(PID_output->ut < PID_settings->lower_limit){
    PID_output->ut = PID_settings->lower_limit;
  }
}


void calculate_pids(setpoints_t * setpoints, gyro_t * gyro ){

// malloc PID_input, PID_output_t OUTSIDE the function
  PID_input_t * pid_input_roll = (PID_input_t *)malloc(sizeof(PID_input_t));
  PID_output_t * pid_output_roll = (PID_output_t *)malloc(sizeof(PID_output_t));

  PID_input_t * pid_input_pitch = (PID_input_t *)malloc(sizeof(PID_input_t));
  PID_output_t * pid_output_pitch = (PID_output_t *)malloc(sizeof(PID_output_t));

  PID_input_t * pid_input_yaw = (PID_input_t *)malloc(sizeof(PID_input_t));
  PID_output_t * pid_output_yaw = (PID_output_t *)malloc(sizeof(PID_output_t));

// ROLL Set inputs
  pid_input_roll->target = setpoints->roll_setpoint;
  pid_input_roll->measurement = gyro->roll_filtered;
//Populate the PID output for the ROLL axis
  pid_controller(pid_input_roll, pid_settings_roll, pid_output_roll);

// PITCH set inputs
  pid_input_pitch->target = setpoints->pitch_setpoint;
  pid_input_pitch->measurement = gyro->pitch_filtered;
//Populate the PID output for the PITCH axis
    pid_controller(pid_input_pitch, pid_settings_pitch, pid_output_pitch);

// YAW set inputs
    pid_input_yaw->target = setpoints->yaw_setpoint;
    pid_input_yaw->measurement = gyro->yaw_filtered;
//Populate the PID output for the YAW axis
    pid_controller(pid_input_yaw, pid_settings_yaw, pid_output_yaw);
}

//Print something
//  uart_puts("something");

//Control loop sequence
void control_loop(receiver_inputs_t * receiver, setpoints_t * setpoints) {
    //Wait 250ms
    delay_us(250000);
    receiver_read(receiver); //Interrput subroutine
    receiver_scale(receiver);
    //malloc setpoints
    calculate_setpoints(receiver, setpoints);
    //malloc pid_input_roll,  pid_input_pitch, pid_input_yaw and pid_output_roll, pid_output_pitch and pid_output_yaw
    calculate_pids(setpoints, gyro);

    //Take a reading
    gyro_read(gyro);

    //Print gyro data
    gyro_print(gyro);
}
