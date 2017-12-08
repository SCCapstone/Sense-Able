This Folder includes positive images of Stairs and negative images, without stairs, as well as python functions that will Download and save images of a given description from ImageNet in a structured way.

Required Python 3 Packages:
  
  beautifulsoup4
  opencv

scrape.py:

Brief description of each function:

populate_imagedict(file): 
  Reads sysnet_file.txt or any file structured "WNID Description\n" and stores 
  line in dictionary as "wnid" : "description". where WNID is a WordNet Id


get_name_link(wnid, dest):
  For a given wnid, retrieve the file containing the mapping of image id to 
  image url. Store in file dest


download_all_sysnet_link(sysnet_file, destfolder):
  Downloads the mapping of image to id for all wnids in the sysnet file.


download_image(name, url, destfolder): 
  Where name is wnid-id for an image in a sysnet. Attempts to download 
  url to destfolder with formatted filename


download_images(filename, destfolder):
  Given a sysnet id-url mapping file, attempt to download all images to q 
  destfolder


download_random_images(urlmap_folder, destfolder, count):
  Spawns 20 threads, attempts to download count-many random images selected 
  from a randomly selected sysnet.


crop_bounded(box_folder, img_folder, dest_folder):
  Where box folder is the folder containing xml formatted descriptions
  of bounding boxes of a sysnet and img_folder is the folder containg all images
  of the sysnet, Crop all images to the bounding box, resize to mean height and 
  width unless size is too different. Save cropped image to dest_folder 

delete.py:
  deletes images from a folder if they are empty or if they are not jpeg. 
  The second condition is kindof hacky but useful for bulk imagenet images.
  While valid PNGs are downloaded, None-existant images on flickr are   
  downloaded as pngs.

