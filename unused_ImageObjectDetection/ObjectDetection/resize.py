import os
from PIL import Image


BASE_DIR = "/home/elrondhubbard/Documents/ObjectDetection"
DATA_DIR = BASE_DIR + "/data"
RAW_DATA_DIR = DATA_DIR + "/raw"
RESIZED_DATA_DIR = DATA_DIR + "/resized"

height = 224
width = 224

# For each type of object for which there
for objectDir in os.listdir(RAW_DATA_DIR):

# And for each subdirectory, Positive, negative, and Test
# Create a new directory in 
  for folder in os.listdir(RAW_DATA_DIR +"/"+ objectDir):

    RAW_FOLDER_DIR = RAW_DATA_DIR +"/"+ objectDir +"/"+ folder
    RESIZED_FOLDER_DIR = RESIZED_DATA_DIR +"/"+ objectDir +"/"+ folder

    print("\nGetting images from", RAW_FOLDER_DIR)
    print("Writing resized images to", RESIZED_FOLDER_DIR, "\n")


    if not os.path.exists(RESIZED_FOLDER_DIR):
      os.makedirs(RESIZED_FOLDER_DIR)

    for img in os.listdir(RAW_FOLDER_DIR):
      RAW_IMG_DIR = RAW_FOLDER_DIR +"/"+ img

      if os.path.isfile(RAW_IMG_DIR):
        
        try:
          im = Image.open(RAW_IMG_DIR)

          if folder != "test":
            resized = im.resize((height, width))
          else:
            resized = im
            
          resized.save(RESIZED_FOLDER_DIR +"/"+ img)
          print("Writing", img)

        except IOError:
          print(RAW_IMG_DIR, "Not opened, IOError.")
