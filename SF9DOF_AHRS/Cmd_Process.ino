#define MAX_CMD 3

void (*command[MAX_CMD])(void)={print_data,external_config,reset};

void process_cmd(uint8_t cmd){
  (*command[cmd-'0'])();
}

void external_config(void){
  
  int read_var;
  boolean config =false;
  digitalWrite(STATUS_LED,HIGH);
  delay(500);
  digitalWrite(STATUS_LED,LOW);
  delay(500);
  while(config==false){
    if(Serial.available()>4){
    
      if((read_var=Serial.read())==HEADER){
          config_param[0]=(int)Serial.read();
          config_param[1]=(int)Serial.read();
          config_param[2]=(int)Serial.read();
          //TODO: VALIDAR VALIDAR VALIDAR
          if((read_var=Serial.read())==FOOTER){
            config = true;
            Serial.write(ACK);
          }
      }
    }
  
  }
 timer=millis();
 counter=0;
}

void reset(void){
  
  digitalWrite(STATUS_LED,HIGH);
  delay(500);
  digitalWrite(STATUS_LED,LOW);
  delay(500);
  timer=0;   //general purpuse timer
  timer_old=0;
  timer24=0;
  accel_x=0;
  accel_y=0;
  accel_z=0;
  magnetom_x=0;
  magnetom_y=0;
  magnetom_z=0;
  MAG_Heading=0;
  
  roll=0;
  pitch=0;
  yaw=0;
  
  gyro_sat=0;
  
  Vector_zero_int(AN_OFFSET,6);
  Vector_zero_int(AN,6);
  Vector_zero_int(ACC,3);
  Vector_zero_float(Accel_Vector,3);
  Vector_zero_float(Gyro_Vector,3);
  Vector_zero_float(Omega_Vector,3);
  Vector_zero_float(Omega_P,3);
  Vector_zero_float(Omega_I,3);
  Vector_zero_float(Omega,3);
  Vector_zero_float(errorRollPitch,3);
  Vector_zero_float(errorYaw,3);
  
  Matrix_Identity(DCM_Matrix);
  Matrix_Zero(Temporary_Matrix);
  Update_Matrix[0][0]=0;
  Update_Matrix[0][1]=1;
  Update_Matrix[0][2]=2;
  Update_Matrix[1][0]=3;
  Update_Matrix[1][1]=4;
  Update_Matrix[1][2]=5;
  Update_Matrix[2][0]=6;
  Update_Matrix[2][1]=7;
  Update_Matrix[2][2]=8;
  
  MuxSel=0;
  analog_reference=0;
  Vector_zero_uint16((uint16_t*)analog_buffer,8);
  Vector_zero_uint8((uint8_t*)analog_count,8);
  
  Analog_Reference(DEFAULT); 
  Analog_Init();
  I2C_Init();
  Accel_Init();
  Read_Accel();
  // Magnetometer initialization
  Compass_Init();
    
  // Initialze ADC readings and buffers
  Read_adc_raw();
  delay(20);
  
  for(int i=0;i<32;i++)    // We take some readings...
    {
    Read_adc_raw();
    Read_Accel();
    for(int y=0; y<6; y++)   // Cumulate values
      AN_OFFSET[y] += AN[y];
    delay(20);
    }
    
  for(int y=0; y<6; y++)
    AN_OFFSET[y] = AN_OFFSET[y]/32;
    
  AN_OFFSET[5]-=GRAVITY*SENSOR_SIGN[5];
 
  digitalWrite(STATUS_LED,HIGH);
  
  Read_adc_raw();     // ADC initialization
  timer=millis();
  counter=0;
  Serial.write(ACK); 
}
