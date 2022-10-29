# System-Programming
## SIC

&nbsp;opcode(8)&nbsp;&nbsp;&nbsp;&nbsp;X(1)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;address(15)  
<--------->&nbsp;&nbsp;&nbsp;<->&nbsp;&nbsp;&nbsp;<--------------->  
&nbsp;&nbsp;xxxx xxxx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;x&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xxxxxxxxxxxxxxx  


## SIC/XE 

&nbsp;opcode(6)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ni&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xbpe&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;address(12)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;extend(8)  

<--------->&nbsp;&nbsp;&nbsp;<-->&nbsp;&nbsp;&nbsp;<---->&nbsp;&nbsp;&nbsp;<------------------>&nbsp;|&nbsp;<----------->  

&nbsp;&nbsp;xxxx&nbsp;&nbsp;&nbsp;xx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xxxx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xxxx&nbsp;&nbsp;&nbsp;&nbsp;xxxx&nbsp;&nbsp;&nbsp;&nbsp;xxxx&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;xxxx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xxxx  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<--------->  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;xx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ni  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00  (0)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;01&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00  (4)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00  (8)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00  (c)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&ensp;ni  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11  (Simple mode)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10  (Indirect mode)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;01  (Immediate mode)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00  (Register mode)
  
opcode 的16進位尾數只有0、4、8、c 四種，因為後兩bit是給ni的，所以轉換為object code 時，只要把opcode加上n和i組合所代表的0、1、2、3就好
