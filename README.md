# PPG Project details:

`This is the repository which contains PPG project documents, microcontroller firmware code`.

| Supported Targets | FPB-RA4E1 | 
| :----------------- | :--------- |
</center>

##### "FPB-RA4E1 Quick start guide" [click here](https://www.renesas.com/en/document/qsg/fpb-ra4e1-quick-start-guide?r=1527296#:~:text=The%20FPB%2DRA4E1%20Fast%20Prototyping,make%20further%20investments%20in%20tools.)
</center>

##### "FPB-RA4E1 User manual" [click here](https://www.renesas.com/en/document/mat/fpb-ra4e1-users-manual?srsltid=AfmBOorcaggMb13ZcnLC2UZd9g_1g280orFuA-2et-hcn7GL4Gg3oa5H)
</clean>

##### "FPB-RA4E1 Example projects user guide" [click here](https://github.com/renesas/ra-fsp-examples/blob/master/example_projects/Example%20Project%20Usage%20Guide.pdf)
</br>

## Hardware detail:
This example can be executed on `RENESAS FPBRA4E1(R7FA4E10D2CFM)`, the only required using i2c interface with `MAX86150` extranl sensor.
>[!IMPORTANT]
>#### "Checkout about MAX86150" [Click here](https://github.com/Protocentral/protocentral_max86150_ecg_ppg/blob/master/README.md)
<clean>

 #### Connection:
 |MAX86150 pin label| RA4E1 Connection  |Pin Function      |
 |:-----------------: |:---------------------:|:------------------:|
 | SDA              | SDA                  |  Serial Data     |
 | SCL              | SCL                  |  Serial Clock    |
 | 3.3V             | 3.3V                 |  Power           |
 | GND              | GND                  |  GND             |
 | INT              | --                   |  Interrupt        |
 
</br>

## Software detail:
1)In this example  `configuration of iic_master` is important to communicate with max86150 sensore as showing above `pin 
  configuration` in harware details.
  </center>
  
2)checkout how to setup the iic in the e2studio. 
</center>

`i) pin configuration as show in the below picture` 
![picture](./e2studio/pictures/Configure_RA4E1.png)
</br>

`ii)iic configuration as show in the below picture `
![picture](./e2studio/pictures/iic_stacks.png)
</br>

`iii) stacks properties`
![picture](./e2studio/pictures/stacks_properties.png)



## IDE Information & Documents :

#### "Checkout e2studio downlonds" [Click here](https://www.renesas.com/en/software-tool/e-studio?srsltid=AfmBOoofsyZ-vZtebnAy63cVHOU4tqkWEnhXESOGg8qhTQyPTHtpYvmC)

