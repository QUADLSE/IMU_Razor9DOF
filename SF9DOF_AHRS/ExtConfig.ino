boolean external_config(void){
  
  int read_var;
  boolean config =false;
  
  if(Serial.available()>4){
    
        if((read_var=Serial.read())==0xFF){
          config_param[0]=(int)Serial.read();
          config_param[1]=(int)Serial.read();
          config_param[2]=(int)Serial.read();
          //TODO: VALIDAR VALIDAR VALIDAR
          if((read_var=Serial.read())==0xF1){
            config = true;
            Serial.write(0xAA);
          }
        }
  }
  return config;
}
