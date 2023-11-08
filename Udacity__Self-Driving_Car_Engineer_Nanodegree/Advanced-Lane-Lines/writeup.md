## Writeup

**Advanced Lane Finding Project**

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.
* Use color transforms, gradients, etc., to create a thresholded binary image.
* Apply a perspective transform to rectify binary image ("birds-eye view").
* Detect lane pixels and fit to find the lane boundary.
* Determine the curvature of the lane and vehicle position with respect to center.
* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

[//]: # (Image References)

[image1]: ./output_images/Undistorted_image.jpg "Undistorted"
[image2]: ./output_images/Road_Undistorted_image.jpg "Road Transformed"
[image3]: ./output_images/Treshold_image.jpg "Binary Example"
[image4]: ./output_images/Warped_image_with_straight_lane_lines.jpg "Warp Example with straigh lane lines"
[image5]: ./output_images/Warped_image_with_curved_lines.jpg "Tresholded Warp Example with curved lane lines"
[image6]: ./output_images/Treshold_image_with_windows_and_lane_lines.jpg "Treshold image with windows and lane lines.jpg"
[image7]: ./output_images/Treshold_image_with_polygon_and_lane_lines.jpg "Treshold image with polygon and lane lines.jpg"
[image8]: ./output_images/Image_with_detected_lane_boundaries.jpg "Image with detected lane boundaries.jpg"
[video1]: ./output_images/project_video_output.mp4 "Video"

## [Rubric](https://review.udacity.com/#!/rubrics/571/view) Points

### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. 

You're reading it!

### Camera Calibration

#### 1. Briefly state how you computed the camera matrix and distortion coefficients. Provide an example of a distortion corrected calibration image.

The code for this step is contained in the second code cell of the IPython notebook located in `P2.ipynb`.  

I start by preparing "object points" in function `chessboard_corners()`, which will be the (x, y, z) coordinates of the chessboard corners in the world. Here I am assuming the chessboard is fixed on the (x, y) plane at z=0, such that the object points are the same for each calibration image.  Thus, `objp` is just a replicated array of coordinates, and `objpoints` will be appended with a copy of it every time I successfully detect all chessboard corners in a test image.  `imgpoints` will be appended with the (x, y) pixel position of each of the corners in the image plane with each successful chessboard detection.  

I then used the output `objpoints` and `imgpoints` to compute the camera calibration and distortion coefficients using the `cv2.calibrateCamera()` function.  I applied this distortion correction to the test image using the `cv2.undistort()` function and obtained this result: 

![alt text][image1]

### Pipeline (single images)

#### 1. Provide an example of a distortion-corrected image.

To demonstrate this step, I will describe how I apply the distortion correction to one of the test images like this one:
![alt text][image2]

#### 2. Describe how (and identify where in your code) you used color transforms, gradients or other methods to create a thresholded binary image.  Provide an example of a binary image result.

I used a combination of color and gradient thresholds to generate a binary image (thresholding steps in the forth code cell of the IPython notebook located in `P2.ipynb`).  Here's an example of my output for this step.

![alt text][image3]

#### 3. Describe how (and identify where in your code) you performed a perspective transform and provide an example of a transformed image.

The code for my perspective transform includes two functions called `unwarp_m()` and `unwarp()`, which appears in the 6th code cell of the IPython notebook.  The `unwarp_m()` function takes as inputs source (`src`) and destination (`dst`) points. I chose the hardcode the source and destination points in the following manner:

```python
    src = np.float32([[200, shape[0]],[593, 450],[shape[1]-590, 450],[shape[1]-160, shape[0]]])
    dst = np.float32([[300, shape[0]],[300, 0],[shape[1]-300, 0],[shape[1]-300, shape[0]]])
```

This resulted in the following source and destination points:

| Source        | Destination   | 
|:-------------:|:-------------:| 
| 200.   720.   | 300.  720.    | 
| 593.   450.   | 300.    0.    |
| 690.   450.   | 980.    0.    |
| 1120.   720.  | 980.  720.    |

The `unwarp()` function takes as inputs an image (`img`) and Matrix (`M`). I can use this function also for inverted transformation.
I verified that my perspective transform was working as expected by drawing the `src` and `dst` points onto a test image and its warped counterpart to verify that the lines appear parallel in the warped image.

![alt text][image4]

Then I applied this transformation to tresholded road image and got this.

![alt text][image5]

#### 4. Describe how (and identify where in your code) you identified lane-line pixels and fit their positions with a polynomial?

In the 8th code cell of the IPython notebook I took a hystogram of the bottom half of the image and found the peak of the left and right halves of the histogram. These would be the starting point for the left and right lines. I used a sliding window, placed around the line centers, to find and follow the lines up to the top of the frame. I saved all pixels which belonged to each line and then fit a 2nd order polynomial for each lane line. 

![alt text][image6]

Also I drew green polygon between lane lines defined by polynomials

![alt text][image7]

#### 5. Describe how (and identify where in your code) you calculated the radius of curvature of the lane and the position of the vehicle with respect to center.

I did this in the 10th code cell of the IPython notebook with the function `measure_curvature_real()` where `left_fit` and `right_fit` polinomial coefficients and image `shape` are inputs. I assumed that if normal parabola is `x= a*(y**2) +b*y+c` then the scaled parabola is `x= mx / (my ** 2) *a*(y**2)+(mx/my)*b*y+c`, where `mx` and `my` are the scale for the x and y axis, respectively (in meters/pixel). Curvature can be calculated with formula `curvature = (1 + (2* mx / (my ** 2) *a*y + (mx/my)*b)**2)**1.5 / (|(2*mx / (my ** 2) *a)|)`.
The position of the vehicle is a difference between x values of the bottom center of the image and center between left and right lanes scaled by `mx`.
     

#### 6. Provide an example image of your result plotted back down onto the road such that the lane area is identified clearly.

I implemented this step in the 10th code cell of the IPython notebook with the function `unwarp()`, which was described in 3rd Pipeline step, just used the Inversed Matrix.  Here is an example of my result on a test image:

![alt text][image8]

---

### Pipeline (video)

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (wobbly lines are ok but no catastrophic failures that would cause the car to drive off the road!).

Here's a [link to my video result](./output_images/project_video_output.mp4)

---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Here I'll talk about the approach I took, what techniques I used, what worked and why, where the pipeline might fail and how I might improve it if I were going to pursue this project further.  

* The main issue was creation of a thresholded binary image. I used a combination of color threshold in S-chanel from HSV color space and gradient threshold in `x` direction. It works only with good light conditions. In challenging videos it worked badly, it couldn't find clearly where are lane boundaries. This can be improved by combining tresholds from other image channels.
* Also pipeline failed in hard_challenge_video with lots of sharp curves. My pipeline has implementation of using previous polynomials to search lanes in specified area, but it should also be tuned to adequatly cope with curves.