#To be run on the Raspbain Operating System a Linux distribution for the Raspberry Pi
sudo apt install git
sudo leafpad /etc/apt/sources.list
sudo apt update
sudo apt install bc
sudo git clone --depth=1 https://github.com/raspberrypi/linux /usr/src/4.14.91/
sudo ln -s /usr/src/4.14.91/ /lib/modules/4.14.91
cd /lib/modules/4.14.91/
KERNEL=kernel7
sudo make bcm2709_defconfig #sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig
sudo make -j4 zImage dtbs #sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs 
sudo make modules_install
sudo cp arch/arm/boot/dts/*.dtb /boot/
sudo cp arch/arm/boot/dts/overlays/README /boot/overlays
sudo cp arch/arm/boot/zImage /boot/$KERNEL.img
