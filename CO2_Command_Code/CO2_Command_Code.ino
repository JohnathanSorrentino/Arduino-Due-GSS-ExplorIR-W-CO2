void readGSS( char* );     // reads from Serial1 until a '/r/n' is reached. Result is placed in char*
void readComputer(char* ); // reads from Serial until a '/r/n' is reached. Result is placed in char*

char co2_data_string[1000] = "";    // String to hold incoming data from GSS CO2 Sensor
char com_serial_input[1000] = "";   // String to hold incoming data from the computer
boolean co2_data_received = false;  // Flag that identifies when data has been received by GSS sensor

void serialEvent1() 
///
//  Function is automatically called when hardware serial port_1 receives a char
{         
  readGSS(co2_data_string); // stores received string into co2_data_string
  co2_data_received = true; // sets the flag used to say that a completed string has been received
}

void serialEvent()
///
// Function automatically called when hardware serial port_0 receives a char
{
  readComputer(com_serial_input);     // Read in data from the computer
  Serial1.println(com_serial_input);  // Send data to GSS Sensor
}

void setup() {
  /// put your setup code here, to run once:
  Serial.begin(112500);   // communication with the computer
  Serial1.begin(9600);    // Serial communication to the GSS CO2 sensor 
  delay(1000);
  
  Serial.println("CO2 Command Code Version 0.1c");
  Serial.println("GSS_Temp  Humidity  Filtered_CO2  Raw_CO2");
  delay(4000);
  
  Serial1.println("K 2"); // Put CO2 sensor into polling mode
}

void loop() {
  /// put your main code here, to run repeatedly:
  delay(2000);  // 2 second delay between readings, can be adjusted to any value
  char string[1000] = ""; // string array used to print output to Serial
  
  if (co2_data_received == true) {    // check string received flag 
    /// Print all recevied data to Serial
    Serial.print(co2_data_string);
    Serial.println("");
    
    co2_data_received = false;    // reset string received flag
  }
}

void readGSS(char* stringArray)
///
// Reads from Serial1 until a '/r/n' is reached. Result is placed in char* stringArray
// The '/r/n' character is discarded
{
  int i = 0;    // counter variable
  char rxByte;  // temporary byte to read data 
  while (Serial1.available() > 0)
  {
    rxByte = Serial1.read();
    if (rxByte != '\r') {
      // as long as byte is not '/r' record data to passed in array
      stringArray[i] = rxByte;
    }
    else if (Serial1.available() > 0) { // check to make sure that the '/n' character is next
      Serial1.read();                   // dispose of '/n' character so that it won't be read next cycle
    }
    i++;  // increment counter
  } 
}

void readComputer(char* stringArray)
///
// Reads from Serial until a '/r/n' is reached. Result is place in char* string Array
{
  int i = 0;    // counter variable
  char rxByte;  // temporary byte to read data 
  while (Serial.available() > 0)
  {
    rxByte = Serial.read();
    if (rxByte != '\r') {
      // as long as byte is not '/r' record data to passed in array
      stringArray[i] = rxByte;
    }
    else if (Serial.available() > 0) { // check to make sure that the '/n' character is next
      Serial.read();                   // dispose of '/n' character so that it won't be read next cycle
    }
    i++;  // increment counter
  } 
}
