#!/bin/bash

# Rebuild AppImage from source
echo "Do you want to rebuild your AppImage? It MIGHT TAKE TIME? [y / n]"
read do_appimage
if [[ $do_appimage == y* ]]; then
    export LD_LIBRARY_PATH=$PWD/LeddarLibs:$HOME/Qt/5.9.4/gcc_64/lib
    sudo ldconfig
    echo $LD_LIBRARY_PATH
    ./linuxdeployqt-continuous-x86_64.AppImage build-leddargui-Desktop_Qt_5_9_4_GCC_64bit-Release/leddargui -qmake=$HOME/Qt/5.9.4/gcc_64/bin/qmake -bundle-non-qt-libs -verbose=2 -appimage
fi


# Deletes all old files, including sound and Leddar Libs,
# and copies in all needed files from the main directory

# Remove old AppImage and move new one to directory
rm build_deploy/SenseAbleGui-x86_64.AppImage
mv SenseAbleGui-x86_64.AppImage build_deploy/


# Optional Tar and Zip type y
echo "Type y if you want to tar and feather your AppImage"
read do_tar

if [[ $do_tar == y* ]]; then
    tar -zcvf sense-able-deploy.tar.gz build_deploy/
fi

