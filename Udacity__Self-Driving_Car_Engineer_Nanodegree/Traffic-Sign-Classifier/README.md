# **Traffic Sign Recognition** 

## Writeup

**Build a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set (see below for links to the project data set)
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/histogram.jpg "Histogram"
[image2]: ./examples/samples.jpg "Samples for each label"
[image3]: ./examples/grayscale.jpg "Grayscale"
[image4]: ./examples/test_images.jpg "Test images"
[image5]: ./examples/predictions.jpg "Predictions for test images"
[image6]: ./examples/top5_0.jpg "Top 5"
[image7]: ./examples/top5_1.jpg "Top 5"
[image8]: ./examples/top5_2.jpg "Top 5"
[image9]: ./examples/top5_3.jpg "Top 5"
[image10]: ./examples/top5_4.jpg "Top 5"
[image11]: ./examples/top5_5.jpg "Top 5"
[image12]: ./examples/top5_6.jpg "Top 5"
[image13]: ./examples/top5_7.jpg "Top 5"
[image14]: ./examples/top5_8.jpg "Top 5"

---

### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.

I used the numpy library to calculate summary statistics of the traffic
signs data set:

* The size of training set is 34799
* The size of the validation set is 4410
* The size of test set is 12630
* The shape of a traffic sign image is (32, 32)
* The number of unique classes/labels in the data set is 43

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set. It is a bar chart showing the count of samples for each label.

![alt text][image1]

And here are random samples for each label.

![alt text][image2]

### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data. What techniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc. (OPTIONAL: As described in the "Stand Out Suggestions" part of the rubric, if you generated additional data for training, describe why you decided to generate additional data, how you generated the data, and provide example images of the additional data. Then describe the characteristics of the augmented training set like number of images in the set, number of images for each class, etc.)

As a first step, I decided to convert the images to grayscale because grayscaling reduces number of features and execution time.  

Here is an example of a traffic sign image before and after grayscaling.

![alt text][image3]

As a last step, I normalized the image data because it makes the cost function much easier to train and to converge faster and effectively.
I have tried several approaches to normalization:

- Normalization: scale pixel values to the range 0-1.
- Global and Local Centering: scale pixel values to have a zero mean.
- Global and Local Standardization: scale pixel values to have a zero mean and unit variance.

Global Standardization showed best results.




#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

I used LeNet model architecture, just added dropout before Fully connected layers. My final model consisted of the following layers:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x1 Grayscale image  						| 
| Convolution 5x5     	| 1x1 stride, valid padding, outputs 28x28x6 	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 14x14x6  				|
| Convolution 5x5	    | 1x1 stride, valid padding, outputs 10x10x16	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 5x5x16   				|
| Flatten 				| outputs 400 									|
| DROPOUT 				|  												|
| Fully connected		| outputs 120									|
| RELU					|												|
| DROPOUT 				|  												|
| Fully connected		| outputs 84									|
| RELU					|												|
| DROPOUT 				|  												|
| Fully connected		| outputs 10									|
| Softmax				| 												|
|						|												|
|						|												|
 


#### 3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

To train the model, I used an AdamOptimizer. Hyperparametres I used are the following:

- number of epochs: 100
- batch size: 128
- keep probability of the dropout layer in training set: 0.5
- learning rate: 0.001



#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

My final model results were:
* training set accuracy of 0.994
* validation set accuracy of  0.967 
* test set accuracy of 0.949

I chose an iterative approach:

* As the first architecture was chosen LeNet model architecture. It was already used in the course and showed good results. 

* Setup was easy, just changed initial input for 3-channeled RGB images and output for 43 label classes. Validation set accuracy was low, only 83-86%. So I understood that I need to preprocess images and adjust hyperparametres.
* Images were grayscaled and normalized. In my case Local Standardization showed the best results and it boosted Validation set accuracy up to 90-91%.
* Then I played with hyperparametres, number of epochs, batch size and learning rate. Validation set accuracy raised to 93%.
* I checked if my model has overfitting or underfitting. Training set accuracy was 99% and validation set accuracy was just 93%. It indicated that my model has light overfitting. I added DROPOUT layers before fully connected layers and ajusted keep probability of it to 60%. Validation set accuracy became 96%


 

### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are Images of German traffic signs that I took by myself:

![alt text][image4]

The "Speed limit (50km/h)" image might be difficult to classify because it has some sticker on it. "General caution" sign might be difficult to classify because its shape is a little bit squeezed. "Go straight or left" sign has shadows and light on the sign surface. "Children crossing" sign is bent and black figures on it can be misclassified.

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

![alt text][image5]


The model was able to correctly guess 5 of the 9 traffic signs, which gives an accuracy of 55-66%. It is not as high as I expected, but not bad.

#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability. (OPTIONAL: as described in the "Stand Out Suggestions" part of the rubric, visualizations can also be provided such as bar charts)

The code for making predictions on my final model is located in the 9-10th cell of the Ipython notebook.

![alt text][image6]
![alt text][image7]
![alt text][image8]
![alt text][image9]
![alt text][image10]
![alt text][image11]
![alt text][image12]
![alt text][image13]
![alt text][image14]
