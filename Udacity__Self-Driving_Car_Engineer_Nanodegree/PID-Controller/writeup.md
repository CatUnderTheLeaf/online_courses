# **PID Controller** 

## Writeup

---

[//]: # (Image References)

[image1]: ./pic/Kp.png "Proportional gain"
[image2]: ./pic/Kd.png "Differential gain"
[image3]: ./pic/Ki.png "Integral gain"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/1972/view) individually and describe how I addressed each point in my implementation.  

---
### Compilation

#### Your code should compile. Code must compile without errors with cmake and make.

Yes, my code compiles without errors with cmake and make.

### Implementation

#### The PID procedure follows what was taught in the lessons. It's encouraged to be creative, particularly around hyperparameter tuning/optimization. However, the base algorithm should follow what's presented in the lessons.

The PID procedure follows what was taught in the lessons.

### Reflection

#### 1. Describe the effect each of the P, I, D components had in your implementation. Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?

P - proportional component is used to steer a car in proportion with CTE. With only P component a car overshoots and moves with oscillations. With small proportional gain a car will fail to react on sharp turns. With large proportional gain oscillations are increasing in time.
![alt text][image1]
I - integral component sums all the previous CTEs. This component works to cancel out steering drift.
![alt text][image3]
D - derivative component cancels oscillations. With small gain a car stops oscillating slow .
![alt text][image2]


#### 2. Describe how the final hyperparameters were chosen. Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

I have tried both manual tuning and twiddle. It was faster to manually tune parameters than to code Twiddle. First I tuned Kp, so that car oscillates round the center of the road. Then I tuned Kd to cancel those oscillations. And in the end I tuned Ki.

### Simulation

#### The vehicle must successfully drive a lap around the track. No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle).

Yes, the car drives a lap around the track successfully.
