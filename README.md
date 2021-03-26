# CreativeEmbeddedSystemsHW4

This project is a kinetic sculpture that moves when the endpoint at http://165.227.76.232:3000/lbw2149/running returns true. 
**Hardware Used**
-Stepper motor and driver
-Servo motor 
-ESP32
-Breadboard
-Battery (9V or Lipo)
-Laptop
-Several male to male wires

**Other Materials**
-Box large enough to hold all of the hardware
-Decorating supplies (tape, glue, stickers, etc)
-Paper
-Markers
-Blue cloth/fabric

In order to create the enclosure, begin by drawing and cutting out animals of your choosing. I went with a bunny and a swan. Tape them to thin strips of cardboard and attach one to the servo motor and the other to the stepper motor. Cut holes in your box so that when the motors are activated the animals have space to move. Cut a larger hole around where the swan (or other aquatic animal) will be and fill it with blue cloth to replicate water. Place all of your hardware inside the box and make sure there are holes for ventilation. Decorate as desired. 

The Arduino code establishes a wifi connection in order to communicate with the Python code running laptop. Run the Python code on your and the API will be queried every 5 seconds if the last value returned was false. It will wait 30 seconds to query again if the endpoint returns true in order to allow time for the motors to operate. The Python code tells the Arduino code when the endpoint returns true and the motors are activated at that point.
