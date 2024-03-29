# Clock on 7-segment display LED
Project of a watch built on seven-segment displays using DS1307 serial RTC.

<p align="center">
  <img src="https://user-images.githubusercontent.com/64035334/220825995-58353248-7b1d-4539-8323-0319cb96e4bf.jpg" />
</p>


### Atmega pins overview:
<p align="center">
  <img src="https://user-images.githubusercontent.com/64035334/193014544-33eb8d25-002a-4cb7-9b20-8f425de7f5ff.jpg" />
</p>

### Schematic

#### First board - Atmega:

<p align="center">
  <img src="https://user-images.githubusercontent.com/64035334/193219013-a98c1056-7544-40e6-b1e2-a49060cf8c54.png" />
</p>

<p align="center">
<img src="https://user-images.githubusercontent.com/64035334/207265761-430660c3-486c-4750-b449-0832adcb6867.png" width="415" /> 
<img src="https://user-images.githubusercontent.com/64035334/207265714-403169b8-97d6-47a9-961d-cb809c91139e.png" width="400" />
<img src="https://user-images.githubusercontent.com/64035334/207266001-b9a8a29e-795e-406c-ac90-51ceb02f5aa0.png" height = "400" /> 

</p>




#### Second board - display:

<p align="center">
  <img src="https://user-images.githubusercontent.com/64035334/184557712-5e35c11a-a0cd-49bf-8e09-801e6a3c12e4.png" />
</p>

<p align="center">
<img src="https://user-images.githubusercontent.com/64035334/207269999-5803082f-61d8-4b3a-b332-a5f0696da0c8.png" width="400" /> 
<img src="https://user-images.githubusercontent.com/64035334/207269906-6e840c21-5c43-41b0-80a2-a107bd99900f.png" width="405" />
<img src="https://user-images.githubusercontent.com/64035334/207270160-6f644425-2c82-4792-b7ff-7cdc02690556.png" height = "400" /> 
</p>

<p align="center">
 <br />
<br />
</p>

## Execute:
<p align="center">
<img src="https://user-images.githubusercontent.com/64035334/210881535-f9fa1313-9acb-405e-ba0e-74ddf90f0e56.jpg" width="400" /> 
<img src="https://user-images.githubusercontent.com/64035334/214227344-b8cc08bc-c8b8-4a87-be07-ed943cef91ad.jpg" width="400" /> 
<img src="https://user-images.githubusercontent.com/64035334/214227397-7b039e9c-ac05-496e-af27-afe3c7ef8fe0.jpg" width="600" /> 
</p>

# Program:

## MAX7219:

communication via SPI,
<p align="center">
<img src="https://user-images.githubusercontent.com/64035334/214368843-cd3c8615-da3c-43d6-9ec2-3b1b50546827.png" " /> 
</p>
D0 - D7 set led 
D11-D10 addres of single digit
                                                                                                                  
<p align="center">
<img src="https://user-images.githubusercontent.com/64035334/214369046-f5e609af-61c3-478e-bf77-c136767d7245.png" " /> 
</p>



## DS1307 

Data format communication I2C

<p align="center">
<img src="https://user-images.githubusercontent.com/64035334/217756307-3467a691-80b5-49f3-9d42-1f1c0bd24b91.png" " /> 
<img src="https://user-images.githubusercontent.com/64035334/217759509-43fc8ddc-53f0-4072-85f0-b2b6fdc08c99.png" " /> 
<img src="https://user-images.githubusercontent.com/64035334/217760035-be41251c-3220-46ba-a650-a472a01b9592.png" " /> 
<img src="https://user-images.githubusercontent.com/64035334/217760091-6417082f-b249-4cb1-a939-5a9248767146.png" " /> 
</p>
