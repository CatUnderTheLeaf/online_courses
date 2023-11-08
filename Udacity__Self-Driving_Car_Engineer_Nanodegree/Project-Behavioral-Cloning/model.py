import csv
from scipy import ndimage
import numpy as np
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split

import cv2

# read lines from csv-file
lines = []
with open('data/driving_log.csv') as csvfile:
    reader = csv.reader(csvfile)
    next(reader, None)
    for line in reader:
        lines.append(line)
#      split images in train and validation sets
train_set, validation_set = train_test_split(lines, test_size=0.2)

# generator of batches for memory efficiency
def generator(rows, BATCH_SIZE=32):
    num_lines = len(rows)
    while 1:
#         schuffle all image paths      
        shuffle(rows)
        for offset in range(0, num_lines, BATCH_SIZE):
#             select paths of one batch
            lines = rows[offset:offset+BATCH_SIZE]
            multiple_images = [] 
            multiple_measurements = [] 
            for line in lines:
                path = 'data/IMG/'                
#                 read central image
                img_center = ndimage.imread(path + line[0].split('/')[-1])  
#                 steering value
                m_center = float(line[3])
#                 append image and steering value to batch set    
                multiple_images.append(img_center) 
                multiple_measurements.append(m_center)
#                 append flipped image and steering value to batch set 
                multiple_images.append(cv2.flip(img_center, 1))
                multiple_measurements.append(m_center*-1)
#                 correction for steeing value for left and right images
                correction = 0.2 
#                 same steps for left image
                img_left = ndimage.imread(path + line[1].split('/')[-1])
                m_left = m_center + correction 
                multiple_images.append(img_left) 
                multiple_images.append(cv2.flip(img_left, 1))
                multiple_measurements.append(m_left)
                multiple_measurements.append(m_left*-1)    
#                 same steps for right image
                img_right = ndimage.imread(path + line[2].split('/')[-1])
                m_right = m_center - correction
                multiple_images.append(img_right) 
                multiple_images.append(cv2.flip(img_right, 1))
                multiple_measurements.append(m_right)
                multiple_measurements.append(m_right*-1)           
        
            X_train = np.array(multiple_images) 
            y_train = np.array(multiple_measurements) 
            
            yield shuffle(X_train, y_train) 


BATCH_SIZE=32
# generators for training and validation sets
X_train_gen = generator(train_set, BATCH_SIZE)
X_val_gen = generator(validation_set, BATCH_SIZE)


from keras.models import Sequential
from keras.layers import Flatten, Dense, Lambda, Conv2D, AveragePooling2D, Cropping2D, Dropout


model = Sequential()
# normalize images
model.add(Lambda(lambda x: (x / 255.0) - 0.5, input_shape=(160,320,3)))
# crop images
model.add(Cropping2D(cropping=((50,20), (0,0))))
# Nvidia architecture
model.add(Conv2D(filters=24, kernel_size=(5, 5), strides=(2, 2), activation='relu'))
model.add(Conv2D(filters=36, kernel_size=(5, 5), strides=(2, 2), activation='relu'))
model.add(Conv2D(filters=48, kernel_size=(5, 5), strides=(2, 2), activation='relu'))
model.add(Conv2D(filters=64, kernel_size=(3, 3), activation='relu'))
model.add(Conv2D(filters=64, kernel_size=(3, 3), activation='relu'))
model.add(Flatten())
model.add(Dense(100))
model.add(Dropout(0.2))
model.add(Dense(50))
model.add(Dropout(0.2))
model.add(Dense(10))
model.add(Dense(1))

# LeNet
# model.add(Conv2D(filters=6, kernel_size=(3, 3), activation='relu'))
# model.add(AveragePooling2D())
# model.add(Conv2D(filters=16, kernel_size=(3, 3), activation='relu'))
# model.add(AveragePooling2D())
# model.add(Flatten())
# model.add(Dense(units=120, activation='relu'))
# model.add(Dense(units=84, activation='relu'))
# model.add(Dense(units=1))

model.compile(loss='mse', optimizer='adam')
# train and validate model
# model.fit(X_train, y_train, validation_split=0.2, shuffle=True, nb_epoch=3)
model.fit_generator(X_train_gen, steps_per_epoch= len(train_set)/BATCH_SIZE, epochs=7, validation_data=X_val_gen, validation_steps=len(validation_set)/BATCH_SIZE, verbose=1)
                    

model.save('model.h5')

# import matplotlib.pyplot as plt

### plot the training and validation loss for each epoch
# plt.plot(history_object.history['loss'])
# plt.plot(history_object.history['val_loss'])
# plt.title('model mean squared error loss')
# plt.ylabel('mean squared error loss')
# plt.xlabel('epoch')
# plt.legend(['training set', 'validation set'], loc='upper right')
# plt.savefig('examples/plot.jpg', bbox_inches=None)