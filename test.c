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
}hhh
skkks
kkks
kkks
kks
hello world
jdjjd
ldlld
kdkkd
kkkkd
djdj
491
21sh
21sh.fr.pdf
author
file
ft_auto_misc.o
ft_auto_search.o
ft_auto_utils.o
ft_bck_i_search.o
ft_cd.o
ft_cmd_utils.o
ft_commands.o
ft_ctrl_c_signal_handler.o
ft_ctrl_keyboard.o
ft_ctrl_terminal.o
ft_cut.o
ft_echo.o
ft_env.o
ft_env_utils.o
ft_export.o
ft_free.o
ft_get_data.o
ft_here_doc.o
ft_here_doc_utils.o
ft_history.o
ft_hist_utils.o
ft_logical_op.o
ft_manage_buff.o
ft_manage_hist.o
ft_manage_pipes.o
ft_more_utils.o
ft_parenthesis.o
ft_parenthesis_utils.o
ft_redirection.o
ft_redirection_utils.o
ft_signals.o
ft_term_utils.o
ft_utils.o
includes
libft
main.o
Makefile
nbproject
README.md
src
test.c
TODO
hello
peopel
ppeo
oooe
pppe
lllsl
lslls[D
ksks
hello
hekki
ge
kk
llx
last
