#This script builds a Linux Distribution including kernel for the Raspberry Pi
sudo apt install git g++ make python tar gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm

cd ~/
#git clone git://git.yoctoproject.org/linux-yocto
#git clone git://git.yoctoproject.org/yocto-docs
git clone git://git.yoctoproject.org/poky
#The Yocto project was formed from the poky project, so the source tree still uses the poky name.
cd poky/
#meta source projects are added to the poky source tree, mainly from the yocto source tree.
git clone git://git.yoctoproject.org/meta
git clone git://git.yoctoproject.org/meta-poky
git clone git://git.yoctoproject.org/meta-yocto-bsp
git clone git://git.yoctoproject.org/meta-raspberrypi
#The meta-openembedded source tree is separate to the poky source tree, however I have placed this within the poky source tree.
git clone git://github.com/openembedded/meta-openembedded

#Use the source command with the oe-init-build-env file to create the build directory, in this case rpi-build.
source oe-init-build-env rpi-build

#After using bitbake, bitbake recommanded to build the core-image-base as the first image I built was deprecated.
bitbake core-image-base
