# AVR_CAN_Driver

in this repo I'm trying to implement a boot loader using CAN bus but with 8-bit microcontroller 
as far as we Know the important and the advantages of using CAN bus as the communication method between ECUs provide a prioritized message ,the arbitration method in CAN allow the message with high priority Identifier to continuous sending  and also message oriented not address oriented 
so for this major features of CAN over other serial communications CAN now is widely used in automotive and medical and so on 
can also have a lot of development in recent years and we can see CANFD is a new version of can and provide less overhead it can send up to 64 byte per message with high rate up to 10Mbps
because of all the above and more I build this project 

at the same time also in automotive the boot loader is much and much important so update the firmware over the air give us ability to fix bugs with easy way without any need to any external tool 
or go to agency 

if we return to the structure of this project we can see the following files :
 
we have first MCP2515 driver this chip allow us to add CAN peripheral to our MCUs this driver can use blocking mode or through ISR as you like 

secondly 
after receive the message and store it in EEPROM we set an flag in the end of the EEPROM if mark that we ready to flash a new image 
then the boot driver parse the image and check the validity of the image ,flash the received image in flash then jump to the application . 

finally 
in application I put a condition that allow the user to force jump directly to the boot mode 

hint I use CAN1 in STM32 to send the firmware 
