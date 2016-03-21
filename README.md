                          THE DECRYPTER
  
  
  This program is based on 3 files : the main, the child, the great child.
  
  The main (Main.c) will browse the folder (which contains encrypt files), he will create a child process for each files (mini-projet.c),
  this child process will create other child processes (fils.c) in order to test all the decryption methods possible (25).
  
  If the child process finds the name that you're seeking for, it will stop and print you in which file and with which method it was found.
           
           
                      
  To execute : ' ./main "CodeMessages" $name ' $name: the name that you are seeking
  
  Example: ./main "CodeMessages" CHOPIN
  
  => The program will search the name CHOPIN in the 73 files by using 25 methods of decryption 
     The program will tell you in which file it is and with which method it found.
     
  Other name to try: 'DUBOIS','GAMORY','GUIBERT'   
