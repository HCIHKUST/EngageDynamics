## This Project
The project aims to study human participants' engagement dynamics when they are interacting with a robot.

![](demo.gif)

More about this project can be found in this paper, Sensing and Handling Engagement Dynamics in Human-Robot Interaction Involving Peripheral Computing Devices, which will soon be published in the proceedings of [ACM SIGCHI 2017](https://chi2017.acm.org/). 
The video showcase of this project can be found [here](https://www.youtube.com/watch?v=ay_ak9ejMro).

## Code framework
All the system codes can be found in /humanSensing folder. Information about our system can be found in our [project homepage](https://hcihkust.github.io/EngageDynamics/).

* humanSensing/main.cpp shows the system flow.
* humanSensing/humanSensing.cpp contains the algorithms to detect participants' gaze, head movement and voice information
* humanSensing/naosensors.cpp contains the code snippets to control the embedded sensors, including LED, chest button. We use the eye LEDs to make nao blink its eyes, and use the chest button to change the strategies.
* humanSensing/newauto.cpp is the initializing code segment for nao to return to default posture.
* humanSensing/sharedvar.cpp contains all the constant defintions.
* humanSensing/NaoAction3 is in charge of controlling nao robot to exercise state-sensitive behaviors. 

## Codebook & Annotations
The codebook (/codebook/Codebook-Meeting.xlsx) contains all the codes we have used as reference to annotate the video corpus. More details on this codebook can be found in the [project paper](SensingAndHandling.pdf). 

Some example annotations of our video corpus are listed in the /codebook/Codebook-MultipartyMeeting-MHCI-plot.xlsx. Different sheets in this file correspond to different meeting video. 

## Citations
Please cite this project if you use any codes here:

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