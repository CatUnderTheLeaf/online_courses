# **Finding Lane Lines on the Road** 

---

**Finding Lane Lines on the Road**

The goals / steps of this project are the following:
* Make a pipeline that finds lane lines on the road
* Reflect on your work in a written report


[//]: # (Image References)

[image1]: ./test_images_output/gray.jpg "Grayscale"
[image2]: ./test_images_output/blur_gray.jpg "Gaussian Blur Grayscale"
[image3]: ./test_images_output/edges.jpg "Canny Edge Detection"
[image4]: ./test_images_output/edged_with_mask.jpg "Canny Edge with polygon mask"
[image5]: ./test_images_output/lines.jpg "Hough Transform line detection"
[image6]: ./test_images_output/lines_edges.jpg "Lane lines on the original image"

---

### Reflection

### 1. Describe your pipeline. As part of the description, explain how you modified the draw_lines() function.

My pipeline consisted of 6 steps:
1) To prepare image for edge detection I converted the images to grayscale.
![alt text][image1]
2) I applied Gaussian smoothing with kernel size of 15 to lessen the noise.
![alt text][image2]
3) I used Canny Edge Detection to detect edges of the lanes.
![alt text][image3]
4) Then applied to the image a polygon mask, so we can focus only on region where lanes are usually located.
![alt text][image4]
5) To find lines in a region of interest I used Hough Line Transform.
![alt text][image5]
6) To draw lines for the left and right lanes I averaged and extrapolated line segments. Then I combined lines with original image.
![alt text][image6]


In order to draw a single line on the left and right lanes, I modified the draw_lines() function with computing slopes and intercepts for each line returned by Hough Transform. Slopes with negative value are for right lane, and slopes with positive value are for left lane. Also I dismissed all lines with almost zero slope. Then I found average values for slopes and intercepts. Knowing y-values for the top and bottom of the lanes I computed x-values and drew red lines.


### 2. Identify potential shortcomings with your current pipeline

1. The pipeline doesn't properly detect lanes when there are shadows and different colors in the pavement.
2. It handles only with straight lines.
3. Applyed polygon mask is static, so sometimes region of interest can be higher or lower as expected.


### 3. Suggest possible improvements to your pipeline

1. A possible improvement would be to play with color and light tresholds for better detection of road lanes in shadows or on different colors in the pavement.
2. Another potential improvement could be to dynamically calculate sizes of a mask.
