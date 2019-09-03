# RACE CAR TRAJECTORY GENERATIONAND TRACKING WITH FEEDBACKLINEARIZATION

## Introduction
Local trajectory generation and tracking is one of the fundamental problems in robot navigation. A typical navigation task with given map can be divided to global planning, local planning and control. First, using given map with obstacles, global planner can generate a global path with obstacle avoidance, then local planner will generate local smooth trajectories along the global path and control robot to track smooth trajectories.

In this project, we focus on designing local planner for race car robot that dynamically generate local smooth trajectories along the global path with replanning functionality, and use feedback linearization method to control robot tracking the dynamically generated trajectory. We implemented our local planner in C++ and tested in Gazebo simulation environment. 
## Theory
### Dynamic model of the robot car

where the controls are acceleration and steering angle.
### Differential flatness
Consider the problem of generating a trajectory between two given states

The boundary conditions of a differentially flat systems are expressed as

## Control law
The feedback linearization method is applied to design a control law for
generated trajectory $(x(t), y(t))$ let us set the states to be the
form below:

Tracking with feedback is much more desirable in order to have
robustness.Assume that we can measure the position (x1, x2) and we would
like to track it. We specify that by the output

We differentiate the output $y$ till obtain the controls
