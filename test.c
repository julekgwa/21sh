#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listDir(char* path){
DIR* dir;
struct dirent *ent;
  if((dir=opendir(path)) != NULL){
    while (( ent = readdir(dir)) != NULL){
      if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0  && strcmp(ent->d_name, "..") != 0){
        printf("%s\n", ent->d_name);
        listDir(ent->d_name);
      }
    }
    closedir(dir);
  }
  else
    printf("%s\n", "Error");
}
void main(){
  listDir(".");
}