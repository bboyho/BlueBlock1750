//STATE CONNECTED
char state_CONNECTED[]= "STATE CONNECTED";//15 char + 1 null char
//STATE CONNECTABLE
char state_CONN[] = "STATE CONNECTABLE";//17 char + 1 null
//STATE CONNECTABLE DISCOVERABLE
char state_CONN_DISC[] = "STATE CONNECTABLE DISCOVERABLE"; //30 char + 1 null char
char temp_buff[31]="";
char temp_c;
int check_counter = 0; //temp_buff does not equal to any of the other arrays 

// null = '\0'

void setup(){
  Serial.begin(9600);
  Serial.println("Begin Test Arrays");
}

void loop(){

  /*for(int k=0; k<sizeof(hi3);k++)
   {
   Serial.print(hi3[k]);    
   }
   Serial.println();*/

  temp_buff[check_counter] = temp_c;

  if(state_CONNECTED[check_counter] == temp_buff[check_counter]{
    check_counter++;
  }
  else if(state_CONN[check_counter] == temp_buff[check_counter]){
    check_counter++;
  }
  else{
    //nothing is equal, clear counter and start over
    check_counter=0;

    //clean arrays, for(int i=)....
  }

  //flag to check if still good 31 char
  //good? keep adding in array where left off
  //if doesn't match start over
  //state of bluetooth led will remain the same
  //temp buffer keep track when adding char from serial UART

  //3 variables keep track connected, discoverable, connectable
  //
}





