//POPULATE DUPLICATE ARRAY//

   int compReturn = -99;
   int dupeA = 0;
   int dupeB = 0;
   int dupeCounter = 0;
   int dupeCheck = 0;
   int dupeCheckCount = 0;
   int dupeFlag = 0;
   
   //compares seqMaster[dupeA] --->>> seqMaster[dupeB]
   while(dupeA < lineCount){
      dupeB = 0;
      
      while(dupeB < lineCount){
         dupeCheckCount = 0;
         dupeFlag = 0;
         compReturn = strncmp(seqMaster[dupeA], seqMaster[dupeB], (STRING_LENGTH));
       
         //if duplicate is found, this will copy it into the duplicate array
         //UNLESS: it is already present in the array/comparing to itself (dupeA == dupeB)
         if((compReturn == 0) && (dupeA != dupeB)){
            
            //this loop looks for duplicates in the duplicates array (ugh)
            while(dupeCheckCount<dupeCounter){
               dupeCheck = strncmp(seqMaster[dupeB], seqDuplicate[dupeCheckCount], (STRING_LENGTH));
               dupeCheckCount++;
               
               //flags duplicates in duplicate array so that they are not copied twice
               if(dupeCheck==0){
                  dupeFlag = 1;
               }
            }         
            //if duplicate of duplicate is not present in dupe array, copies string over
            if(dupeFlag !=1){
               strncpy(seqDuplicate[dupeCounter], seqMaster[dupeB], (STRING_LENGTH) );
               dupeCounter++;
            }
         }
         dupeCheck = 0;
         dupeB++;
      }
      dupeA++;
   }
