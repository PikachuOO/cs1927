
//MODIFY THIS FUNCTION TO
//Update the size variable in the node
//Do not insert duplicates
static link insertR (link currentLink, Item item) { 

   if(currentLink == emptyTree){
      return NEW(item,emptyTree, emptyTree, 1 ); 
   
   }else if( key(item) != key(currentLink->item)){
      
      if(less( key(item),  key(currentLink->item))){
         currentLink->left = insertR(currentLink->left,item);
         
      }else if(greater( key(item),  key(currentLink->item))){
         currentLink->right = insertR(currentLink->right, item);
      }
      currentLink->size = currentLink->right->size+currentLink->left->size +1;
   }
   
   return currentLink;
}

