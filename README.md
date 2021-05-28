# 2021_DKU_OS


This is a place for studying Operaing System in Dankook University.
- Professor : Jongmoo Choi
- Assistant : Hojin Shin (Email : ghwls03s@gmail.com)
- 2021 DKU Operating System Course Information [link](http://embedded.dankook.ac.kr/~choijm/course/course.html)


## Download Environment
Virtual Machine Platform: VirtualBox 6.1.18

[VirtualBox Download Link](https://www.virtualbox.org/wiki/Downloads)

Windows Subsystem for Linux Install Guide (WSL)

[WSL Install Guide Link](https://docs.microsoft.com/ko-KR/windows/wsl/install-win10#step-4---download-the-linux-kernel-update-package)

Operating System: Ubuntu 20.04

This environment is based on VirtualBox 6.1.18
If image execution is not possible, we recommend reinstalling VirtualBox 5.2 version.

[Virtual Box 5.2 Link](https://www.virtualbox.org/wiki/Download_Old_Builds_5_2)

## Clone Git Repository
git clone https://github.com/DKU-EmbeddedSystem-Lab/2021_DKU_OS.git

If you get an error there are no commands, install git with following command :

    sudo apt-get install git

## Lab0

lab0 contains information about installing a virtual machine and Ubuntu.

Set the environment according to the documentation.

The documentation for lab0 is at the link below.

The OS image to use for preferences is also on the link below.

Documentation for conducting the assignment can be found at following link :

[Lab0 Documentation Link](https://drive.google.com/file/d/10FFkWXZnCZTb8Qs0jqQRQrgq2UN5of3H/view?usp=sharing)

DKU OS Image Download Link [Link](https://drive.google.com/file/d/1RI9B_5tmvlTtv15TOlvlnBew2Fi4A7T2/view?usp=sharing)

Root password : 1234

### DKU OS Image rename : DKU_OS_2021 -> ubuntu 20.04

### If you have an error, you must check VirtualBox version check(6.1.18). If not, you reinstall VirtualBox.


## Lab1
If you want to proceed to Lab1, go to command below :

    cd lab1_sched

    make

    ./lab1_sched

Documentation for conducting the assignment can be found at following link :

[Lab1 Documentation Link](https://drive.google.com/file/d/11xK4F7bR6TyK34gRpZ9UQ1ylDWEQA6Px/view)

## Lab2
If you want to proceed to Lab2, go to command below :

    cd lab2_sync
    
    make all
    
    ./lab2_sync -c=100 -q=1

Usage for lab2_sync :

    Usage for ./lab2_sync : 
        -c: Total number of vehicles produced, must be bigger than 0 ( e.g. 100 )
        -q: RoundRobin Time Quantum, must be bigger than 0 ( e.g. 1, 4 ) 

    Example : 
        #sudo ./lab2_sync -c=100 -q=1 
        #sudo ./lab2_sync -c=10000 -q=4 

See the documentation for details.

Documentation for conducting the assignment can be found at following link :

[Lab2 Documentation Link](https://drive.google.com/file/d/1gq-h-EdTCiDq_Fh94GjMPzbYOIcl8gDF/view?usp=sharing)

## Lab3

If you want for proceed to Lab3, go to command below :

    cd lab3_filesystem

    make

    insmod ramdisk.ko

    mkfs.ext2 /dev/ramdisk
  
    mkdir mnt

    mount /dev/ramdisk ./mnt

    ./create.sh
  
    ./apt mnt/A/BC 13 A/BC-13        //A, B, C is your last 3 digit of you student ID : 32XXXABC

Then you can proceed Lab3

If you want to proceed to Lab3-Bounus, go to command below:

    umount /dev/ramdisk
  
    rmmod ramdisk
  
    insmod ramdisk.ko
  
    cd os_ext2        //Change the source code
  
    make
  
    insmod os_ext2.ko
  
    mkfs.ext2 /dev/ramdisk
  
    mount -t os_ext /dev/ramdisk ../mnt
  
    dmesg | grep os_ext2

See the documentation for details.

[Lab3 Documentation Link]()
