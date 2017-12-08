import os
import imghdr
from PIL import Image

BASE_DIR = "/home/elrondhubbard/Documents/ImageNetScrape"
DIRTY_DIR = BASE_DIR + "/images/stairs/negative_images/"

for file in os.listdir( DIRTY_DIR ):
  if os.path.isfile(DIRTY_DIR + file):
    
    if (os.path.getsize(DIRTY_DIR + file) == 0):
      os.remove(DIRTY_DIR + file)
      print("Deleting ", file, "-- Empty file")

    elif file.split(".")[-1] == "jpg":
      if imghdr.what(DIRTY_DIR+file) != "jpeg":
        print(imghdr.what(DIRTY_DIR+file))
        print("Deleting:", file, "-- Is not JPG")
        os.remove(DIRTY_DIR+file)
      
      else:
        try:
          img = Image.open(DIRTY_DIR + file)
          # print(imghdr.what(DIRTY_DIR + file))
          # print(file)
        except IOError:
          print("Deleting:", file,"-- Could not open")
          os.remove(DIRTY_DIR+file)
      


