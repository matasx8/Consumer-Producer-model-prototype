# Consumer-Producer model prototype
Universal Producer-Consumer model implementation. Synchronization of shared memory usage is left to the user of this. 
<br><br>
Using run-time polymorphism and smart pointers this example uses a fake "Mock Engine" to show how to use this to record commands for the Consumer thread to execute in parallel 
or to execute immediatelly on the Producer thread for easier debugging.
<br><br>
* WorkQ.h - template Work Queue for threaded Producer-Consumer
* WorkQ_ST.h - template fake Work Queue for single-threaded debugging
* ConsumerThread.h - template Consumer Thread implementation
* MockEngine.cpp - usage example of run-time polymorphism to use both single-threaded work queue and multi-threaded
