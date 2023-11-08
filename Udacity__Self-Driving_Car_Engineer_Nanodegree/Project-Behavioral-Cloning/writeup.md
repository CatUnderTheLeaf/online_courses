# **Behavioral Cloning** 

## Writeup

---

**Behavioral Cloning Project**

The goals / steps of this project are the following:
* Use the simulator to collect data of good driving behavior
* Build, a convolution neural network in Keras that predicts steering angles from images
* Train and validate the model with a training and validation set
* Test that the model successfully drives around track one without leaving the road
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/normal.jpg "Normal Image"
[image2]: ./examples/flipped.jpg "Flipped Image"
[image3]: ./examples/plot.jpg "Loss plot"
[video1]: ./video.mp4 "Video"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/432/view) individually and describe how I addressed each point in my implementation.  

---
### Files Submitted & Code Quality

#### 1. Submission includes all required files and can be used to run the simulator in autonomous mode

My project includes the following files:
* model.py containing the script to create and train the model
* drive.py for driving the car in autonomous mode
* model.h5 containing a trained convolution neural network 
* writeup.md summarizing the results
* video.mp4 (a video recording of your vehicle driving autonomously around the track for at least one full lap)

#### 2. Submission includes functional code
Using the Udacity provided simulator and my drive.py file, the car can be driven autonomously around the track by executing 
```sh
python drive.py model.h5
```

#### 3. Submission code is usable and readable

The model.py file contains the code for training and saving the convolution neural network. The file shows the pipeline I used for training and validating the model, and it contains comments to explain how the code works.

### Model Architecture and Training Strategy

#### 1. An appropriate model architecture has been employed

My model consists of an architecture published by the autonomous vehicle team at NVIDIA with 5 Convolutional Layers and 4 Fully-connected Layers (model.py lines 76-93) 

The model includes RELU layers to introduce nonlinearity (code lines 82-86), the data is normalized in the model using a Keras lambda layer (code line 78) and cropped with Keras Cropping Layer (code line 80).

#### 2. Attempts to reduce overfitting in the model

The model contains dropout layers in order to reduce overfitting (model.py lines 89, 91). 

The model was trained and validated to ensure that the model was not overfitting (code line 108). The model was tested by running it through the simulator and ensuring that the vehicle could stay on the track.

#### 3. Model parameter tuning

The model used an adam optimizer, so the learning rate was not tuned manually (model.py line 105).

#### 4. Appropriate training data

Training data was chosen to keep the vehicle driving on the road. I used a combination of center lane driving, driving in the opposite direction and using images from multiple cameras.

For details about how I created the training data, see the next section. 

### Model Architecture and Training Strategy

#### 1. Solution Design Approach

The overall strategy for deriving a model architecture was to adapt and retrain already existing neural network model

My first step was to use a convolution neural network model similar to the LeNet. I thought it would be a good start to play with simulator.

It showed not bad results, but I needed better solution. So I decided to use an architecture published by the autonomous vehicle team at NVIDIA.

In order to gauge how well the model was working, I split my image and steering angle data into a training and validation set. I trained model for 5 epochs and ran the simulator to see how well the car was driving around track one. There were a few spots where the vehicle fell off the track. To improve the driving behavior in these cases, I added fliped images and steering values, cropped not important parts of the images and added images from left and right cameras and steering values with correction. Here I needed to use data generators because of memory error.

Then I found that my model had a low mean squared error on the training set but a high mean squared error on the validation set. This implied that the model was overfitting. 

To combat the overfitting, I modified the model so that it had two Dropout Layers and enlarged number of epochs to 7.

At the end of the process, the vehicle is able to drive autonomously around the track without leaving the road.

#### 2. Final Model Architecture

Here is a visualization of the final model architecture (note: visualizing the architecture is optional according to the project rubric)

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 160x320x3 RGB image  							| 
| Lambda         		| Normalize images  							|  
| Cropping         		| 90x320x3 RGB image  							|  
| Convolution 5x5     	| 24 filters, 2x2 stride, valid padding 	 	|
| RELU					|												|
| Convolution 5x5     	| 36 filters, 2x2 stride, valid padding 	 	|
| RELU					|												|
| Convolution 5x5     	| 48 filters, 2x2 stride, valid padding 	 	|
| RELU					|												|
| Convolution 3x3     	| 64 filters, 1x1 stride, valid padding 	 	|
| RELU					|												|
| Convolution 3x3     	| 64 filters, 1x1 stride, valid padding 	 	|
| RELU					|												|
| Flatten 				| 			 									|
| Fully connected		| outputs 100									|
| DROPOUT 				|  												|
| Fully connected		| outputs 50									|
| DROPOUT 				|  												|
| Fully connected		| outputs 10									|
| Fully connected		| outputs 1										|


#### 3. Creation of the Training Set & Training Process

I used sample driving data which was already included in my files, because I had problems in driving a car in simulator.

To augment the data sat, I also flipped images and angles to add training data for opposite direction. For example, here is an image that has then been flipped:

![alt text][image1]
![alt text][image2]

After the collection process, I had 48.216 number of data points. I then preprocessed this data by normalizing and cropping it.

I finally randomly shuffled the data set and put 20% of the data into a validation set. 

I used this training data for training the model. The validation set helped determine if the model was over or under fitting. The ideal number of epochs was 7 as evidenced by autonomous driving in simulator. I used an adam optimizer so that manually training the learning rate wasn't necessary.

The model is still slightly overfitting, but the performance in simulator is good. Here's a [link to my video result](./video.mp4)
![alt text][image3]
