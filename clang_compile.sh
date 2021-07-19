#!/bin/bash

BOLD='\033[1m'
GRN='\033[01;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
RED='\033[01;31m'
RST='\033[0m'
echo "Cloning dependencies if they don't exist...."

if [ ! -d clang ]
then
git clone --depth=1 https://github.com/techyminati/android_prebuilts_clang_host_linux-x86_clang-5484270 clang

fi

if [ ! -d gcc32 ]
then
git clone --depth=1 https://github.com/KudProject/arm-linux-androideabi-4.9 gcc32
fi

if [ ! -d gcc ]
then
git clone --depth=1 https://github.com/KudProject/aarch64-linux-android-4.9 gcc
fi

if [ ! -d AnyKernel ]
then
git clone https://gitlab.com/Baibhab34/AnyKernel3.git -b rm1 --depth=1 AnyKernel
fi

echo "Done"


KERNEL_DIR=$(pwd)
IMAGE="${KERNEL_DIR}/out/arch/arm64/boot/Image.gz-dtb"
TANGGAL=$(date +"%Y%m%d-%H")
BRANCH="$(git rev-parse --abbrev-ref HEAD)"
PATH="${KERNEL_DIR}/clang/bin:${KERNEL_DIR}/gcc/bin:${KERNEL_DIR}/gcc32/bin:${PATH}"
export KBUILD_COMPILER_STRING="$(${KERNEL_DIR}/clang/bin/clang --version | head -n 1 | perl -pe 's/\(http.*?\)//gs' | sed -e 's/  */ /g')"
export ARCH=arm64
export KBUILD_BUILD_USER=devil
export KBUILD_BUILD_HOST=hell

# Compile plox
function compile() {

    echo -e "${CYAN}"
    make -j$(nproc) O=out ARCH=arm64 oppo6771_17065_defconfig
    make -j$(nproc) O=out \
                    ARCH=arm64 \
                    CC=clang \
                    CLANG_TRIPLE=aarch64-linux-gnu- \
                    CROSS_COMPILE=aarch64-linux-android- \
                    CROSS_COMPILE_ARM32=arm-linux-androideabi-
   echo -e "${RST}"
SUCCESS=$?
	if [ $SUCCESS -eq 0 ]
        	then
		echo -e "${GRN}"
		echo "------------------------------------------------------------"
		echo "Compilation successful..."
        	echo "Image.gz-dt can be found at out/arch/arm64/boot/Image.gz-dtb"
    		cp out/arch/arm64/boot/Image.gz-dtb AnyKernel
		echo  "------------------------------------------------------------"
		echo -e "${RST}"
	else
		echo -e "${RED}"
                echo "------------------------------------------------------------"
		echo "Compilation failed..check build logs for errors"
                echo "------------------------------------------------------------"
		echo -e "${RST}"
	fi

}
# Zipping
function zipping() {
    echo -e "${YELLOW}"
    echo "Creating a flashable zip....."
    cd AnyKernel || exit 1
    zip -r9 Hentai-お兄ちゃん-CPH1859-${TANGGAL}.zip * > /dev/null 2>&1
    cd ..
    echo "Zip stored at AnyKernel/Hentai-お兄ちゃん-CPH1859-${TANGGAL}.zip"
    echo -e "${RST}"
}
compile

if [ $SUCCESS -eq 0 ]
then
        mkdir -p AnyKernel/modules/vendor/lib/modules
	cp -r out/drivers/misc/mediatek/connectivity/bt/mt66xx/legacy/bt_drv.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/connectivity/common/wmt_drv.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/connectivity/fmradio/fmradio_drv.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/connectivity/gps/gps_drv.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/connectivity/wlan/adaptor/wmt_chrdev_wifi.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/connectivity/wlan/core/gen3/wlan_drv_gen3.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/met/met.ko AnyKernel/modules/vendor/lib/modules
        cp -r out/drivers/misc/mediatek/performance/fpsgo_cus/fpsgo.ko AnyKernel/modules/vendor/lib/modules
	zipping
fi
