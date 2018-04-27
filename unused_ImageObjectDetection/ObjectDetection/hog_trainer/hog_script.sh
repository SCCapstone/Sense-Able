#!/bin/bash

    # {
    #     "{help h|     | show help message}"
    #     "{pd    |     | path of directory contains possitive images}"
    #     "{nd    |     | path of directory contains negative images}"
    #     "{td    |     | path of directory contains test images}"
    #     "{tv    |     | test video file name}"
    #     "{dw    |     | width of the detector}"
    #     "{dh    |     | height of the detector}"
    #     "{d     |false| train twice}"
    #     "{t     |false| test a trained detector}"
    #     "{v     |false| visualize training steps}"
    #     "{fn    |my_detector.yml| file name of trained SVM}"
    # }

echo Hello, World.

pd="../data/resized/stairs/bounded_images/"
nd="../data/resized/stairs/samp_negative/"
td="../data/resized/stairs/test/"
dw="224"
dh="224"
d=true
v=true
fn="my_detector.yml"
t=true

echo $pd
echo $nd
echo $td
echo $dw
echo $dh

./HogTrainer -pd=$pd -nd=$nd -td=$td -dw=$dw -dh=$dh -v=$v -fn=$fn