# RACE CAR TRAJECTORY GENERATIONAND TRACKING WITH FEEDBACKLINEARIZATION

## Introduction
Local trajectory generation and tracking is one of the fundamental problems in robot navigation. A typical navigation task with given map can be divided to global planning, local planning and control. First, using given map with obstacles, global planner can generate a global path with obstacle avoidance, then local planner will generate local smooth trajectories along the global path and control robot to track smooth trajectories.

In this project, we focus on designing local planner for race car robot that dynamically generate local smooth trajectories along the global path with replanning functionality, and use feedback linearization method to control robot tracking the dynamically generated trajectory. We implemented our local planner in C++ and tested in Gazebo simulation environment. 
## Theory
### Dynamic model of the robot car}
The simplified dynamics of the car is given by

        x = [x, y, \theta, v]
        
        \dot{x} = f(x,u) = [v \cos(\theta), v \sin(\theta), v \tan(u_2)/L, u_1]

where the controls are acceleration and steering angle.
### Differential flatness
Consider the problem of generating a trajectory between two given states
$$
\dot{x}=f(x, u), \quad x(0)=x_{0}, x(T)=x_{f}
$$
The boundary conditions of a differentially flat systems are expressed as
$$
