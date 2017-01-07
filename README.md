## This Project
The project studys how robot assistants perceive and handle human participants' engagement dynamics during conversation services. We propose a novel engagement sensing model and two different handling stragtegies. Details can be found in our paper *Sensing and Handling Engagement Dynamics in Human-Robot Interaction Involving Peripheral Computing Devices*. And a quick preview can be found in the project [homepage](https://hcihkust.github.io/EngageDynamics/) .

All the system codes can be found in /humanSensing folder, which includes:

* humanSensing/main.cpp shows the system flow
* humanSensing/humanSensing.cpp contains the algorithm to detect human participants' gaze, head movement and voice information
* humanSensing/naosensors.cpp is used to control the embedded sensors, including LED, chest button. We use the eye LEDs to make the Nao robot blink its eyes, and use the chest button to change the strategies
* humanSensing/newauto.cpp is the initializing code for the Nao robot to return to the default posture
* humanSensing/sharedvar.cpp contains common global variables
* humanSensing/NaoAction3 is in charge of controlling the Nao robot to exercise state-sensitive behaviors

## How to use?

## Codebook & Annotations
To design our handling strategies, we collect and compile a behavior codebook based on our observations of Human-Human Interaction video recordings with similar settings. The codebook can be found in /codebook/Codebook-Meeting.xlsx. Some example annotations are listed in the /codebook/Codebook-MultipartyMeeting-MHCI-plot.xlsx. Different sheets in this file correspond to different meeting videos.  

## Citations
Please cite our paper if you use the code/codebook:

~~~~
@INPROCEEDINGS{Sun2017,
title = {{Sensing and Handling Engagement Dynamics in Human-Robot Interaction Involving Peripheral Computing Devices}},
year = {2017},
journal = {Proceedings of the SIGCHI Conference on Human Factors in Computing Systems - CHI '17},
author = {Sun, Mingfei and Zhao, Zhenjie and Ma, Xiaojuan},
isbn = {978-1-4503-4655-9/17/05},
doi = {http://dx.doi.org/10.1145/3025453.3025469},
keywords = {Human-Robot Interaction; Engagement Awareness; Peripheral Computing Devices; Robot Behaviors.}
}
~~~~


##  Acknowledgement
We thank the WeChat-HKUST Joint Laboratory on Artificial Intelligence Technology (WHAT LAB) grant#1516144-0, and NSF CIFellows grant#1019343, for sponsoring this research.

-------------------------------

BSD License
