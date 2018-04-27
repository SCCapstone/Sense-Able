from bs4 import BeautifulSoup
import urllib.request
import os
import string
import random
import concurrent.futures
import sys
import cv2

IMGNET_DICT = {
  'n04314914' : "stairs",
}

def populate_imagedict(file):
    with open(file, 'r') as f:
      lines = f.read().splitlines()

      for line in lines:
          s = line.split("\t")

          translator = str.maketrans('', '', string.punctuation)

          # Save key-val to IMGNET_DICT
          # NOTE: Val is only the first describing word with no punctuation
          IMGNET_DICT[s[0]] = s[1].split(",")[0].translate(translator)
          print("KEY:", s[0], " VAL:", IMGNET_DICT[s[0]])
    print(len(IMGNET_DICT))


# Gets the name - Link mapping file from the ImageNet API
def get_name_link(wnid, dest):
    name_link_url = "http://www.image-net.org/api/text/imagenet.synset.geturls.getmapping?wnid=" + wnid
    try:
        if ( not os.path.isfile(dest) ) or ( os.path.getsize(dest) == 0 ):
            response = urllib.request.urlopen(name_link_url)
            html = response.read()
            soup = BeautifulSoup(html, 'html.parser')
        
            print("Writing", wnid)
            with open(dest, 'w+') as f:
                f.write( str(soup.prettify()) )
        else:
          print("Skipping", wnid)
        # Only returns text
        # return( str(soup.prettify()) )

    except urllib.error.URLError as e:
        print("URL ", wnid, " was not succesfully retrieved")
        if hasattr(e, 'reason'):
            print('We failed to reach a server.')
            print('Reason: ', e.reason)
        elif hasattr(e, 'code'):
            print('The server couldn\'t fulfill the request.')
            print('Error code: ', e.code)
        else:
            print("UHH, no reason i guess")

        # Return empty string if unable to get sysnet urls
        return


# Downloads the URL Maps for all sysnets 
# TODO:: No gurantee that all will be downloaded, only attempted
def download_all_sysnet_link(sysnet_file, destfolder):
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=100)

    if len(IMGNET_DICT) < 2:
        populate_imagedict(sysnet_file)

    for key, val in IMGNET_DICT.items():
    # for i in range(0,1000):
        # key, val = random.choice(list(IMGNET_DICT.items()))
        dest = destfolder + key + "_" + val + ".txt"
        # pool.apply_async(get_name_link, (key, dest,))
        executor.submit(get_name_link, key, dest)

    executor.shutdown()
    return


# /Name is wnid + id for an image. Attempts to download url to destfolder with formatted filename
def download_image(name, url, destfolder):

    # Make destination folder if it doesnt exist
    if not os.path.exists(destfolder):
        os.makedirs(destfolder)
    dest = destfolder + name + "_" + IMGNET_DICT[name.split("_")[0]] + ".jpg"
    
    #  Skips file already downloaded
    try: 
        if not os.path.exists(dest):
            urllib.request.urlretrieve(url, dest)
            print(name, " Downloaded")
            return True
        else:
            print(name, " Skipped.")

    # Some Error Checking
    except urllib.error.URLError as e:
        print("URL ", name, " was not succesfully retrieved")
        if hasattr(e, 'reason'):
            print('We failed to reach a server.')
            print('Reason: ', e.reason)
        elif hasattr(e, 'code'):
            print('The server couldn\'t fulfill the request.')
            print('Error code: ', e.code)
    # except:
    #     e = sys.exc_info()[0]
    #     print("Error:", e)

    return False


# Download all images from a sysnet id-url mapping file
def download_images(filename, destfolder):
    with open(filename, 'r') as f:
        lines = f.readlines()

        for line in lines:
          img = line.split(" ")

          download_image(img[0], img[1], destfolder)

    return


# Downloads count-many random images from ImageNet and stores them to dest folder.
# TODO:: this function will not gurantee count-many images, it will only attempt to download count-many
def download_random_images(urlmap_folder, destfolder, count):
    img_count = 0
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=20)
    
    while img_count < count:

        wnid, description = random.choice(list(IMGNET_DICT.items()))
        file = urlmap_folder + wnid + "_" + description + ".txt"

        # try:
        if os.path.isfile(file) and (os.path.getsize(file) > 0):
            with open(file, "r") as f:
              lines = f.read().splitlines()
              # print(line)
              if len(lines) > 1 :
                  line = lines[random.randint(0, len(line))-1 ].split(" ")
                  # print(line[0], line[1])

                  # Recommended to use threads if you want to download a lot of images: > ~100
                  executor.submit(download_image, line[0], line[1], destfolder)
                  # download_image(line[0], line[1], destfolder)
                  img_count += 1
        # except:
            # print("oops something went wrong",file,"not opened")
    executor.shutdown()

    return


def crop_bounded(box_folder, img_folder, dest_folder):
  box_files = os.listdir(box_folder)

  images = []
  hmean = 0
  wmean = 0

  for file in os.listdir(box_folder):
    print(file)

    with open(box_folder+file, 'r') as f:
      soup = BeautifulSoup(f.read(), 'lxml')
      name = soup.filename.string
      h = int(soup.size.height.string)
      w = int(soup.size.width.string)
      xmin = int(soup.object.bndbox.xmin.string)
      ymin = int(soup.object.bndbox.ymin.string)
      xmax = int(soup.object.bndbox.xmax.string)
      ymax = int(soup.object.bndbox.ymax.string)

      print("NAME: ",name)
      print("H x W:",h,w)
      print(xmin, ymin)
      print(xmax, ymax)

      img = name + "_stairs.jpg"
      im_path = img_folder + img

      if os.path.isfile(im_path):
        print(img) 
        image = cv2.imread(im_path)
        image = cv2.resize(image, (w,h))
        # copy = image.copy()
        # cv2.rectangle(image, (xmin, ymin), (xmax,ymax), (0,0,255), 2)
        # cv2.imshow(img, image)
        cropped = image[ymin:ymax, xmin:xmax]
        # cv2.imshow(img+"CROPPED", cropped)
        # cv2.waitKey(0)
        # cv2.destroyWindow(img)
        # cv2.destroyWindow(img+"CROPPED")

        images.append( (name, cropped) )
        hmean += h
        wmean += w

  # Calculate mean image size
  hmean = int(hmean / len(images))
  wmean = int(wmean / len(images))
  print("Hmean wmean",hmean, wmean)

  for img in images:
    if (abs(img[1].shape[0] - hmean)/hmean < .6) or (abs(img[1].shape[1] - wmean)/wmean < .6):
      resized = cv2.resize(img[1], (wmean, hmean))# width=wmean, height=hmean)
      print(resized.shape[0], resized.shape[1])
      cv2.imwrite(dest_folder+img[0]+"_stairs.jpg", resized)
    else:
      print("DID NOT SAVE:", img[1].shape[0], img[1].shape[1])
  return 0



BASE_DIR = "/home/elrondhubbard/Documents/ImageNetScrape/"
IMAGE_DIR = BASE_DIR + "images/"
BOX_DIR = BASE_DIR + "annotation/n04314914/"
URLMAPS_DIR = BASE_DIR + "urlmaps/"

pos_destfolder = BASE_DIR + "/images/stairs/positive_images/"
neg_destfolder = BASE_DIR + "/images/stairs/negative_images/"
bounded_destfolder = IMAGE_DIR + "stairs/bounded_images/"

sysnet_file = "sysnet_list.txt"


# populate_imagedict(sysnet_file)
# print(len(IMGNET_DICT))

# download_name_link("n04314914")
# download_images(stairs_file, pos_destfolder)
# download_random_images(urlmap_folder, neg_destfolder, 1000)
# download_all_sysnet_link(sysnet_file, urlmap_destfolder)

# crop_bounded(BOX_DIR, pos_destfolder, bounded_destfolder)