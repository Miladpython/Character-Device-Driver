**Simple Character Device Driver**

This project shows how Linux user-space communicates with kernel-space using a character device driver.

**Project Structure**

## Project Structure


  <img width="1536" height="1024" alt="project" src="https://github.com/user-attachments/assets/c8c5895b-17cf-42cc-aa3e-023c3d491cf9" />


## Build

make

**Load Driver**
sudo insmod src/mychardev.ko
dmesg | tail

**Create Device Node**
sudo mknod /dev/mychardev c <major> 0
sudo chmod 666 /dev/mychardev


Get major number from dmesg

**Run User Program**
./user_app

**Unload Driver**
sudo rmmod mychardev
