




class SerialConnector{
  
  boolean isConnected;
  String connectionPort;
  
  PApplet sketchRef;
  Serial portRef;
  
  SerialConnector(PApplet skRef, Serial pRef){
    sketchRef = skRef;
    portRef = pRef;
  }
  
    void listPorts(){
      if (Serial.list().length > 0){
        for(int i = 0; i < Serial.list().length;i++){
          print(Serial.list()[i]);
          println("  <-- Press " + str(i) + " to connect.");
        }     
        println("Press x to disconnect");
        println("Press r to relist ports");
      } else {
        println("No COM Ports open"); 
      }
    }
    
    void drawToScreen(){
        fill(255);
        if (sc.isConnected) {
          text("Connected to " + sc.connectionPort,5,height-14);
        } else {
          text("Not connected. see console for connection instructions",5,height-14);
        }
        ConnectionStillValid();
    }



   boolean ConnectionStillValid(){
     if(isConnected){
     for (String aPortName : Serial.list()) {
       if (aPortName.equals(connectionPort)) return true;
     }
     isConnected = false;
     connectionPort = "";
     }
     return false;
   }

   void makeConnection(int portIndex){
       println(Serial.list().length + "   " + str(portIndex));
       
     if (Serial.list().length <= portIndex) {
         println("No such port");
         return;
     }
     if(isConnected) {
         println("Already Connected");
         return;
     }
       
      try{
        portRef = new Serial(sketchRef,Serial.list()[portIndex], 9600);  //Set up serial 
        isConnected = true;
        connectionPort = Serial.list()[portIndex];
      }catch(Exception e){
      System.err.println("counldn't connect");
      }    

   }
  
  
   void disconnect(){
        portRef.stop(); 
        isConnected = false;
        connectionPort  = null;
   }
  
  
    void KeyInputforConnection(char aKey){
        if (aKey == '0') makeConnection(0);
        if (aKey == '1') makeConnection(1);
        if (aKey == '2') makeConnection(2);
        if (aKey == '3') makeConnection(3);
        if (aKey == '4') makeConnection(4);
        if (aKey == '5') makeConnection(5);
        if (aKey == 'x') disconnect();
        if (aKey == 'r') listPorts();
    }

  
}