#define _GNU_SOURCE 

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

#include "answer10.h" 

#define TRUE 1
#define FALSE 0

struct LocationNode{ 
  
  int loc_id;
  long bus_offset; 
  long review_offset; 
  struct LocationNode * next; 

}; 

struct BusinessNode{ 
 
  char *name; 
  struct LocationNode * head; 
  struct BusinessNode * left; 
  struct BusinessNode * right; 
 

};

struct YelpDataBST { 
  struct BusinessNode * root; 
  FILE * bus_path; 
  FILE * rev_path; 
  const char * bus_path_string; 
  const char * rev_path_string; 
};

char * * explode(const char * str, const char * delims, int * arrLen)
{
  int ind; 
  * arrLen = 1;
  char * temp;
  int index1 = 0; // array index
  int str_len = strlen(str);
  for(ind = 0; ind < str_len ; ind++)
    {
      // printf("[%d] ind = %d\n", str_len, ind);
      if(strchr(delims,str[ind]) != NULL)
	{
          (*arrLen)++;
	}
    }
  char * * arr1; // 2D array 
  arr1 = malloc(sizeof(char *) * (*arrLen));
  int row; 
  ind = 0; 
  int strlength = 0;
  int startLeft = 0; 
  int startRight = 0;
  for(row = 0; row < (*arrLen); row++) 
    {
      while((strchr(delims,str[ind]) == NULL)&& (str[ind] != '\0'))
	{
          strlength++;
          ind++;
	}
          temp = malloc(sizeof(char) * (strlength+1));
          temp[0] = '\0';
            startLeft = startRight;
           startRight = ind + 1;  
	   strncpy(temp,&(str[startLeft]),strlength);
          temp[strlength] = '\0';
          arr1[index1] = temp; 
          index1++; 
          strlength = 0; 
          ind++;
    }
  return (char * *)(arr1);
}
struct LocationNode * Loc_create_node( long bus_offset, long rev_offset, int locID)
{
  struct LocationNode * node = malloc(sizeof(struct LocationNode)); 
  node->bus_offset = bus_offset; 
  node->review_offset = rev_offset; 
  node->next = NULL;
  node->loc_id = locID;
  return node;
}
struct BusinessNode * Bus_create_node(char * name, long bus_offset, long rev_offset, int locID) 
{ 
  struct BusinessNode * node = malloc(sizeof(struct BusinessNode)); 
  node->head = Loc_create_node( bus_offset, rev_offset,locID);  
  node->name = strdup(name); 
  node->left = NULL; 
  node->right = NULL; 
  return node;
} 

void addLocation(struct LocationNode * loc, struct LocationNode * list) 
{ 
  if(list == NULL) 
    { 
      return; 
    } 
  while(list->next != NULL) 
    { 
      list = list->next;
    } 
  list->next = loc;
} 
struct BusinessNode * tree_insert(struct BusinessNode * node, struct BusinessNode * root)
{
  if(root == NULL) 
    { 
      return node;
    }
  if(strcmp(node->name,root->name) == 0) 
    {
      // function to add location to list 
      addLocation(node->head, root->head);
      free(node->name);
      free(node);
    } 
  else if(strcmp((node->name),root->name) < 0) 
    { 
      root->left = tree_insert (node,root->left);
    } 
  else 
    {
      root->right = tree_insert (node,root->right);
    } 

  return root;
}

void free_attributes(char * * strArr, int len)
{
   int ind = 0;
if( strArr != NULL)
  {
    for(ind = 0; ind < len; ind++)
    {
      free(strArr[ind]);
    }
    free(strArr);
  }
} 
long getreviewoffset( FILE * fpr, int wanted_loc_id) 
{ 
  // sets the first value as the first offset in the file 
  // cursor in the file moves to the end of the line 
  long offset = ftell(fpr);
  long temp = offset;
  char * * temp_array = NULL;
  char * buffer = NULL;
  size_t buflen = 0;
  int len;
  int quit = 0;
  while(quit == 0)
  {
    if(getline(&buffer, &buflen, fpr) != -1)
      { 
	temp_array = explode(buffer, "\t", &len);
	int loc_id = atoi(temp_array[0]);
	free_attributes(temp_array, len);
	if(loc_id == wanted_loc_id)
	  {
	    temp = offset;
	    quit = 1;
      }
	else if(loc_id > wanted_loc_id)
	  {
	    //the location id does not exit
	    temp = -1;
	    quit = 1;
            fseek(fpr, offset, SEEK_SET);
	  }
	offset = ftell(fpr);
      }
    else 
      { 
	quit = 1;
      }
  }
  free(buffer);
  return temp;
 
} 
struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{ 
  FILE * fpbus = fopen(businesses_path, "r"); 
  FILE * fprev = fopen(reviews_path, "r"); 
  char * buff = NULL;
  size_t len = 0; 
  long offset = 0; 
  long rev_offset = 0; 
  int n; 
  struct BusinessNode * root = NULL; 
  char * * attributes; 
  if(fpbus == NULL) 
    { 
      return NULL; 
    } 
  if(fpbus == NULL) 
    { 
      return NULL; 
    } 
   offset = ftell(fpbus); 
  while(getline(&buff, &len, fpbus) != -1)
    { 
      attributes = explode(buff,"\t", &n); 
      rev_offset = getreviewoffset(fprev, atoi(attributes[0]));
      struct BusinessNode * node = Bus_create_node(attributes[1],offset, rev_offset,atoi(attributes[0]));
      root = tree_insert(node, root); 
      free_attributes(attributes,n);       
      offset = ftell(fpbus); 
    } 

      fclose(fpbus); 
      fclose(fprev); 
      free(buff);
      struct YelpDataBST * yelp = malloc(sizeof(struct YelpDataBST)); 
      yelp->root = root; 
      yelp->bus_path = fpbus;
      yelp->rev_path = fprev; 
      yelp->bus_path_string = businesses_path;
      yelp->rev_path_string = reviews_path; 
      
  return yelp;    
} 



struct BusinessNode * tree_search_name(char * name, struct BusinessNode * root)
{ 
  if(root == NULL) 
    { 
      return NULL;
    } 
  if(strcmp(name, root->name) == 0)
  {
    return root;
  } 
  if(strcmp(name, root->name) < 0 ) 
    { 
      return tree_search_name(name, root->left);
    } 
  return tree_search_name(name, root->right);
}

int count_loc( struct LocationNode * loc) 
{ 
  int count = 0; 
  while(loc != NULL) 
    { 
      count++;
      loc = loc->next;
    }  
  return count;
} 

int filter_locations( char * state, char * zip_code, char * wanted_state, char * wanted_zip_code) 
{ 
  // do the attributes match 
  // return 1 or 0;
  if(wanted_zip_code == NULL && wanted_state == NULL) 
    { 
      return 1;
    } 
  else if(wanted_zip_code == NULL) 
    {
      if(strcasecmp(state, wanted_state) == 0)
	{ 
	  return 1;
	}
      //return 0;
    } 
  else if(wanted_state == NULL) 
    {
      if(strcasecmp(zip_code, wanted_zip_code) == 0)
	{ 
	  return 1;
	}
      // return 0;
    }
  else if(strcasecmp(state, wanted_state) == 0)
    {
      if(strcmp(zip_code, wanted_zip_code) == 0) 
	{ 
	  return 1;
	} 
      // return 0;
    }
  return 0;
} 

void addFilteredLocation(struct  Location * locations, char * * address, int * count) 
 { 
    locations[*count].address = strdup(address[2]);
    locations[*count].city = strdup(address[3]);
    if(address[4] != NULL)
        locations[*count].state = strdup(address[4]);
    else 
      locations[*count].state = NULL;
    if(address[5] != NULL) 
        locations[*count].zip_code = strdup(address[5]);
    else 
        locations[*count].zip_code = NULL;
    (*count)++;
 }  

long get_location_offset(struct LocationNode * location, uint32_t i, uint32_t num_locations)
{
   while(i != 0)
   {
     i--;
     location = location->next;
   }
   
   return location->bus_offset;
}
//counts for specific location
//function call
//	  count_review_offset(fp_rev,locations[counter],atoi(address[0]),&review_num);

int cmpReview(void * rev, void *rev2 )
{ 
  struct Review * review = (struct Review *)(rev);
  struct Review * review2 = (struct Review *)(rev2);  
  
  uint32_t stars1 = review->stars;
  uint32_t stars2 = review2->stars;
  
    if ( stars1 > stars2) 
    { 
       return -1;
    }  
    if(stars1 == stars2) 
    {
      if(strcasecmp(review->text,review2->text) <0)
	{
	  return -1;
	}
      if(strcasecmp(review->text,review2->text) == 0)
	{
	  return 0;
	}
      return 1;

    } 
    return 1; 

} 
void sort_reviews(struct Review * reviews, int num_reviews) 
{ 
   if( reviews != NULL) 
   {
     qsort(reviews,num_reviews,sizeof(struct Review), (__compar_fn_t)cmpReview); 
   } 

} 
int cmpLocation(void * loc, void * loc2) 
{ 
  struct Location * location = (struct Location *)(loc); 
  struct Location * location2 = (struct Location *)(loc2); 

    char * state  = location->state; 
    char * state2= location2->state; 	
    
    char * city = location->city; 
    char * city2 = location2->city;
  
    char * address = location->address; 
    char * address2 = location2->address; 
    int t = 0;
    if(strcasecmp(state,state2) < 0) 
    {
      //free(location); 
      //free(location2);
      t= -1; 
    } 
    if(strcasecmp(state,state2) == 0)
    { 
       if(strcasecmp(address,address2) < 0) 
	  {
            t= -1; 
          }  
        if(strcasecmp(address,address2) == 0) 
	  { 
            if(strcasecmp(city,city2) < 0) 
	      {
		t= -1; 
	      }  
	    if(strcasecmp(city,city2) == 0) 
	      { 
		t= 0;
	      } 
	    t= 1;
	  } 
	t= 1;
    } 
    t= 1;
    
    return t;
} 
void sort_locations(struct Location  * locations, int num_loc)
{ 
   if(locations != NULL) 
   {
	qsort(locations, num_loc, sizeof(struct Location),(__compar_fn_t)cmpLocation); 
   } 
}  

void count_review_offset(FILE * fp_rev, struct Location * loc, int loc_id, long rev_offset, int * review_num)
{
  char * buffer = NULL; 
  size_t buflen = 0;
  char * * review;
  uint32_t num_reviews_loc = 0;
  int n = 0;
  if(fp_rev == NULL) 
    { 
      return;
    } 
  fseek(fp_rev, rev_offset, SEEK_SET);

    while(TRUE) {
      if(getline(&buffer, &buflen, fp_rev) == -1)
	break; // reached the end of the file
      review = explode(buffer, "\t", &n);     
      int rev_loc_id = atoi(review[0]);
      free_attributes(review, n);
      if(loc_id == rev_loc_id)
	num_reviews_loc += 1;
      else
	break; // we're done
    }

    *review_num += num_reviews_loc;    
    loc->num_reviews = num_reviews_loc;

  free(buffer);
}
//adds all reviews from specific location

void  getReviews( FILE * fp_rev, struct Location * location,long rev_offset, uint32_t num_reviews)
  {
   char * buffer = NULL; 
  char * * review;
  size_t buflen = 0;
  int n = 0;
  int rev_iter;
  if(fp_rev == NULL) 
    { 
      return;
    } 

   struct Review * reviews = malloc(num_reviews*sizeof(struct Review));
   fseek(fp_rev, rev_offset, SEEK_SET);
   for(rev_iter = 0; rev_iter < num_reviews; rev_iter++)
   {
      if(getline(&buffer, &buflen, fp_rev) == -1)
	break; // reached the end of the file
      review = explode(buffer, "\t", &n);
      reviews[rev_iter].stars = (uint8_t)(atoi(review[1]));
      reviews[rev_iter].text = strdup(review[5]);
      free_attributes(review, n);
    
    }
    sort_reviews(reviews,(int) (num_reviews)) ;

        location->reviews = reviews;
	//free(reviews);
	//free(review);
  free(buffer);
}

struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{
  FILE * fp_bus = fopen(bst->bus_path_string, "r"); 
  FILE * fp_rev = fopen(bst->rev_path_string, "r"); 
  long bus_offset; 
  char * * address;
  char * buffer = NULL;
  int n; 
  size_t buflen = 0; 
  uint32_t iter = 0;
  int filter;
  int counter = 0;
  int review_num = 0; 
  
  if ( bst == NULL) 
    { 
      return NULL;
    } 
  if( fp_bus == NULL) 
    {
      //failed to open the file 
      fp_bus =NULL; 
    } 
  if(fp_rev == NULL) 
    { 
      // failed to open the file 
      fp_rev = NULL; 
    } 
  
  struct BusinessNode* bus = tree_search_name(name, bst->root); 
  struct Business * node = malloc(sizeof(struct Business)); 
  int num_locations = count_loc(bus->head); 
  struct Location * locations = malloc(num_locations*(sizeof(struct Location))); 
  struct LocationNode * itr = bus->head;

   for(iter =0; iter < num_locations; iter++) 
    { 
      bus_offset = itr->bus_offset; //get_location_offset(itr, iter, num_locations);
      fseek(fp_bus, bus_offset, SEEK_SET);
      getline(&buffer, &buflen, fp_bus);
      address = explode(buffer, "\t", &n);
      filter = filter_locations(address[4],address[5], state, zip_code);
      if(filter) 
	{ 
	  count_review_offset(fp_rev, &locations[counter], atoi(address[0]), itr->review_offset, &review_num);
          getReviews(fp_rev,&locations[counter], itr->review_offset,locations[counter].num_reviews);
	  addFilteredLocation(locations, address, &counter);
	} 
      free_attributes(address, n);
      itr = itr->next; // increment the iterator
    } 
   
  fclose(fp_bus);
  fclose(fp_rev);
  free(buffer);
  
  node->name = name; 
  node->num_locations= counter;
  sort_locations(locations, counter); 
  node->locations = locations; 
  return node; 
}


void destroy_tree(struct BusinessNode * root)
{
  if(root == NULL) 
    { 
      return; 
    } 
  destroy_tree(root -> left);
  destroy_tree(root ->right); 
  free(root->name);
  struct LocationNode * list = root->head; 
  struct LocationNode * temp = list;
  while(list != NULL) 
    {
      // printf("%ld %ld\n",list->bus_offset,list->review_offset);
      temp = list;
      list = list->next;
      free(temp);  
    }
  free(root); 
}

void destroy_business_bst(struct YelpDataBST* bst)
{
  if (bst == NULL) 
    { 
      return; 
    }
  destroy_tree(bst->root); 
  free(bst); 
  
}
 
void destroy_reviews(struct Location * locs, int num_loc) 
{
   struct Review * reviews;
   int i; 
   int iter;
   int num_reviews = 0;
   for(i = 0; i < num_loc; i++)
   {
	num_reviews = locs[i].num_reviews;
        reviews = locs[i].reviews;
   
      for(iter = 0;iter < num_reviews; iter++) 
        {
          free(reviews[iter].text);
	}
     free(reviews); 
   }
}
void destroy_location_list(struct Location * list, int num )
{ 
  if(list == NULL) 
    { 
      return;
    }
  int counter = 0; 
  while(counter < num) 
    {
      free(list[counter].address);
      free(list[counter].city);
      free(list[counter].state);
      free(list[counter].zip_code);
      // destroy_reviews(list[counter].reviews,list[counter].num_reviews); 
      counter++;  
    }
  destroy_reviews(list, num);
  free(list);
} 

void destroy_business_result(struct Business* b)
{
  if(b == NULL) 
    { 
      return ;
    } 
  destroy_location_list(b->locations, b->num_locations);
  //free(b->locations);
  free(b);
}
