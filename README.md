# PRS-foot-throttle-adapter
This is a quick bit of code that takes input from a resistive foot throttle (spring-loaded pedal with a potientiometer on it) and outputs a PWM signal that can drive some of the cheap chinese brushed motor controllers that expect hall-effect throttle inputs. 

NB: simple "Analog Write" PWM control it turns out is not sufficent on all motor controllers, consider a low-pass filter on the output and/or a voltage follower to ensure the throttle signal is clean and no erratic behavior manifests before bringing this code to the racetrack. (Check your backup motor controllers too -- this snipped worked fine with the controller it was tested on, but then suddenly was erratic when the first controller let out the magic smoke and we had to drive with a backup)
