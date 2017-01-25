## The Decrypter
  
  <img src='https://github.com/xchopin/The-Decrypter/blob/master/preview.png'/>

  This program is based on 3 files : the main, the child, the great child.
  
  The main (Main.c) will browse the folder (which contains encrypt files), it will create a child process (mini-projet.c) for each files ,
  this child process will create other child processes (fils.c) in order to test all the decryption methods possible (25 maximum).
  
  If the child process finds the name that you're seeking for, it will stop and print for you in which file and with which method it was found.
           
           
                      
### Run the program :
```bash
./main "CodeMessages" $name
```  

$name: the name that you are seeking  (don't forget to compile before...)
  

### Example:

```bash
./main "CodeMessages" CHOPIN
```    
  => The program will search the name CHOPIN in the 73 files by using 25 methods of decryption 
     The program will tell you in which file it is and with which method it found.
     
  Other names to try: 'DUBOIS','GAMORY','GUIBERT'   
  

