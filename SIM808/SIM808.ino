/* Tested by: Shaifur Rahman
 * web: http://shaifur.com
 * Last Update: 21-Oct-2018
 */

 int value_1 = 0;
 int value_2 = 0;
 int value_3 = 0;
 void setup() {
  Serial.println("Starting SIM808 Module...");
  delay(10000);
  while (sendATcommand("AT+CREG?", "+CREG: 0,1", 2000) == 0); // code will stuck here and won't pass until get network connectivity.
  sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
  sendATcommand("AT+SAPBR=3,1,\"APN\",\"internet\"", "OK", 2000);
  sendATcommand("AT+SAPBR=3,1,\"USER\",\"\"", "OK", 2000);
  sendATcommand("AT+SAPBR=3,1,\"PWD\",\"\"", "OK", 2000);
  sendATcommand("AT+SAPBR=1,1", "OK", 20000);
}
void loop() {
  sendHTTP_REQ(1,2,3);
  delay(1000); 
}
