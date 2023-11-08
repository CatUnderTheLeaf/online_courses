from styx_msgs.msg import TrafficLight
import cv2
import tensorflow as tf
import numpy as np
from PIL import Image
from PIL import ImageDraw
from PIL import ImageColor

class TLClassifier(object):
    def __init__(self):
#         SSD_GRAPH_FILE = 'light_classification/rfcn_resnet101_coco_11_06_2017/frozen_inference_graph.pb'
        SSD_GRAPH_FILE = 'light_classification/ssd_mobilenet_v1_coco_11_06_2017/frozen_inference_graph.pb'
        self.detection_graph = tf.Graph()
        with self.detection_graph.as_default():
            od_graph_def = tf.GraphDef()
            with tf.gfile.GFile(SSD_GRAPH_FILE, 'rb') as fid:
                serialized_graph = fid.read()
                od_graph_def.ParseFromString(serialized_graph)
                tf.import_graph_def(od_graph_def, name='')

        # The input placeholder for the image.
        # `get_tensor_by_name` returns the Tensor with the associated name in the Graph.
        self.image_tensor = self.detection_graph.get_tensor_by_name('image_tensor:0')

        # Each box represents a part of the image where a particular object was detected.
        self.detection_boxes = self.detection_graph.get_tensor_by_name('detection_boxes:0')

        # Each score represent how level of confidence for each of the objects.
        # Score is shown on the result image, together with the class label.
        self.detection_scores = self.detection_graph.get_tensor_by_name('detection_scores:0')

        # The classification of the object (integer id).
        self.detection_classes = self.detection_graph.get_tensor_by_name('detection_classes:0')

    def get_classification(self, image):
        """Determines the color of the traffic light in the image

        Args:
            image (cv::Mat): image containing the traffic light

        Returns:
            int: ID of traffic light color (specified in styx_msgs/TrafficLight)

        """
        with tf.Session(graph=self.detection_graph) as sess:    
    
            image_np = np.expand_dims(np.asarray(image, dtype=np.uint8), 0)
            # Actual detection.
            (boxes, scores, classes) = sess.run([self.detection_boxes, self.detection_scores, self.detection_classes], 
                                                feed_dict={self.image_tensor: image_np})

            # Remove unnecessary dimensions
            boxes = np.squeeze(boxes)
            scores = np.squeeze(scores)
            classes = np.squeeze(classes)

            confidence_cutoff = 0.6
            # Filter boxes with a confidence score less than `confidence_cutoff`
            boxes, scores, classes = self.filter_boxes(confidence_cutoff, boxes, scores, classes)

            # The current box coordinates are normalized to a range between 0 and 1.
            # This converts the coordinates actual location on the image.
            width, height = image.shape[1], image.shape[0]
            box_coords = self.to_image_coords(boxes, height, width)

            # Each class will be represented by a differently colored box
#             self.draw_boxes(image, box_coords, classes)
            
            return self.classify(image_np, box_coords)
    #
    # Utility funcs
    #

    def classify(self, img, boxes):
        red = 0
        for i in range(len(boxes)):
            bot, left, top, right = boxes[i, ...]
            image_box = img[0]
    #         crop only traffic light image
            image_box = image_box[int(bot):int(top), int(left):int(right)]
    #         invert image
            inv_img = cv2.bitwise_not(image_box)
    #     transform to HSV
            hsv_img = cv2.cvtColor(inv_img, cv2.COLOR_BGR2HSV)
    #     select cyan color to avoid two ranges for red color in RGB
            mask = cv2.inRange(hsv_img, np.array([90 - 10, 70, 50]), np.array([90 + 10, 255, 255]))
            red = max(red, np.count_nonzero(mask))
        time = str(np.random.randint(0, 100))
        
        
        if (red > 0):
            print("RED")
#             cv2.imwrite('test/RED'+str(time)+'.jpeg', img)
            return TrafficLight.RED
        else:
            print("GREEN")
#             cv2.imwrite('test/GREEN'+str(time)+'.jpeg', img)
            return TrafficLight.GREEN

    def filter_boxes(self, min_score, boxes, scores, classes):
        """Return boxes with a confidence >= `min_score`"""
        n = len(classes)
        idxs = []
        for i in range(n):
            if scores[i] >= min_score:
                idxs.append(i)

        filtered_boxes = boxes[idxs, ...]
        filtered_scores = scores[idxs, ...]
        filtered_classes = classes[idxs, ...]
        return filtered_boxes, filtered_scores, filtered_classes

    def to_image_coords(self, boxes, height, width):
        """
        The original box coordinate output is normalized, i.e [0, 1].

        This converts it back to the original coordinate based on the image
        size.
        """
        box_coords = np.zeros_like(boxes)
        box_coords[:, 0] = boxes[:, 0] * height
        box_coords[:, 1] = boxes[:, 1] * width
        box_coords[:, 2] = boxes[:, 2] * height
        box_coords[:, 3] = boxes[:, 3] * width

        return box_coords

    def draw_boxes(self, image, boxes, classes, thickness=4):
        """Draw bounding boxes on the image"""
        draw = ImageDraw.Draw(image)
        for i in range(len(boxes)):
            bot, left, top, right = boxes[i, ...]
            class_id = int(classes[i])
            color = (255, 0, 0)
            draw.line([(left, top), (left, bot), (right, bot), (right, top), (left, top)], width=thickness, fill=color)