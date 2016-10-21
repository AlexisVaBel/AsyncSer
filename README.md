# AsyncSer
QModBuser child project, desided to use modules interaction with serial port with async processing.
Just expirements with std::promise and std::future;
   - made non blocking (at current time) opening port, sending pack to it
   - reading is made in Thread using promise ))
