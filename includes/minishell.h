/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:23:09 by goisetsi          #+#    #+#             */
/*   Updated: 2016/12/15 15:33:31 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/dir.h>
# include <termcap.h>
# include <sys/stat.h>
# include <fcntl.h>
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"
# define SIZE 100
# define MAX_HASH 1027
# define STRSTR ft_strstr
# define SUB ft_strsub
# define FULL ft_full_word
# define QUOTES ft_rm_quotes
# define LENGTH ft_array_len
# define STD_INOUT ft_is_redirect_in_out
# define EQUAL ft_strequ
# define CONTAINS ft_contains
# define SEARCH ft_search_command
# define SPLIT ft_strsplit

typedef struct	s_search
{
	char		*prev_match;
	char		*results;
	int			fail;
}				t_search;

typedef struct		s_item
{
	char			*key;
	char			*value;
	struct s_item	*next;
}					t_hash_item;

typedef	struct 	s_search_hist
{
	char 		*haystack;
	char 		*needle;
	char 		*with;
	char 		*replace;
}				t_search_hist;

typedef struct	s_stack
{
	int			capacity;
	int			count;
	int			top;
	t_search	*search;
	int			ctrl_r;
	char		*list[4096];
	char		*paste;
	char		**envp;
	int			success;
	int			ret;
	int			counter;
}				t_stack;

typedef struct	s_comms
{
	char		**user_comm;
	char		*get_line;
}				t_cmd;

typedef struct	s_env
{
	char		**list;
	int			top;
	int			capacity;
	int			malloc_id;
}				t_env;

void			ft_cd(char **dir, t_env *envp);
char			*ft_pwd();
void			ft_echo(char *av, char **envp);
int				ft_end_with(char *str, char c);
int				ft_start_with(char *str, char c);
char			*ft_first_word(const char *s);
char			*ft_last_word(const char *s);
char			*ft_get_env(const char *env, char **env_list);
void			ft_ctrl_c_signal_handler(int signum);
void			ft_print_env(t_env *envp);
char			**ft_check_env(char **cmd, char **envp);
int				ft_array_len(char **arr);
int				ft_unsetenv(const char *env, t_env *envp, char **r);
int				ft_setenv(const char *env, const char *val, int ov, t_env *enp);
void			ft_set_envir(t_env *envp, char *str);
char			*ft_remove_qoutes(char *s);
char			*ft_rm_quotes(char *s);
char			**ft_check_env(char **cmd, char **envp);
void			ft_unsetting_env(char *names, t_env *envp);
char			*ft_build_exec(char **envp, char **split);
int				ft_is_execute(char *command);
void			ft_execute(char *cmd, char **l_cmd, char *line, char **envp);
void			ft_print_error(char *cmd, int errorno);
void			ft_advanced_com(char **cmd, char *line, t_env *envp, t_stack h);
int				ft_search_command(char *command);
void			ft_execute_commands(char **cmd, char *l, t_env *p, t_stack hi);
char			*ft_get_str(char **av);
int				ft_myputchar(int c);
void			ft_clear_screen(void);
int				ft_init_keyboard(struct termios *term, int *ac, char ***av);
int				ft_close_keyboard(struct termios *term);
int				ft_function_keys(char *key_pressed);
int				ft_character_keys(char *key_pressed);
int				ft_enter_and_edit_keys(char *key_pressed, int *pos, char *comm, t_stack *hist);
int				ft_navigation_keys(char *key_pressed, int *pos, char *comm);
void			ft_echo_off(char *s, struct termios *term);
char			*ft_build_comm(t_stack *hist, char *comm, char *buf, int pos);
int				ft_contains(char *str, char c);
void			ft_cursor(char *comm, int pos, t_stack *hist);
void			ft_process_buff(char **com, int pos, char c, t_stack *hist);
void			ft_create_stack(t_stack *hist, char **envp);
void			ft_push(t_stack *stack, char *hist);
char			*ft_up(t_stack *stack);
char			*ft_down(t_stack *stack);
char			*ft_keys_up_down(char *key_pressed, t_stack *hist, int *pos);
int				ft_up_down(char *key_pressed);
void			ft_display_hist(t_stack *hist, char **history, int i, int lim);
char			*ft_get_hist(char *history, t_stack hist, char *tmp, int i);
char			*prompt(t_cmd *command, t_stack *hist);
void			ft_signalhandle(int num);
void			ft_signal(void);
void			init_main(int *ac, char ***av);
void			manage_up_down(char **buf, char **com, t_stack *hist, int *pos);
void			ft_ctrl_l(char *comm, int pos, t_stack *hist);
void			ft_run_commands(char **com, char *line, t_env *env, t_stack hi);
void			ft_pro_cmd(t_cmd *c, t_env *en, struct termios *t, t_stack *hi);
void			free_cmd(t_cmd *cmd);
void			freecopy(char **copy);
void			ft_free_str(char *str, char *join);
void			free_stack(t_stack *stack);
void			freesplit(char **split);
int				ft_spaces_tabs(char *s);
void			ft_builtins(char **cmd, char *line, char **envp, char **sp);
void			ft_exit(char **cmd, char *get_line);
int				ft_user_dir(char *dir, char **envp);
char			**envp_cpy(char **envp);
t_env			*copy_envp(int capacity, char **envp);
void			free_envp(t_env *stack);
int				ft_push_env(t_env *stack, char *value);
int				ft_is_full(t_env *stack);
int				fork_pipes(int n[], char **cmd, char **envp, int i);
int				ft_file_redirection(char **red, char **envp, int arr[]);
int				ft_is_redirect(char **cmd);
int				ft_arrow_pos(char **cmd);
int				ft_ctrl_b_f(char *buf);
void			ft_move_word(char *cmd, int *pos, char *buf);
int				ft_is_file_descriptor_aggr(char **cmd);
int				ft_get_file_descriptor_pos(char **cmd);
int				ft_manage_file_descriptors(char **cmd);
int				ft_get_less_than(char **cmd);
int				ft_is_less_than(char **cmd);
int				ft_get_here_doc_pos(char **cmd, char *doc);
int				ft_process_here_doc(char **cmd, int is_pipe);
int				ft_term_off(struct termios *term);
int				ft_term_on(struct termios *term);
void			ft_cmd_prompt();
int				ft_uneven(char *str);
void			ft_complete_cmd(t_cmd *cmd, struct termios *term);
int				ft_find_arrow(char **str);
void			ft_redirect_left_right(char **cmd);
void			ft_open_file(char *file_name, int arrow);
int				ft_enter_key(char **comm, int *pos, t_stack *hist);
int				ft_read_here_doc(int fd, char *s);
void			ft_remove_single_qoutes(t_cmd *cmd);
void			ft_export(char **cmd, t_env *envp);
void			ft_log_op(t_cmd *c, t_env *en, struct termios *t, t_stack *hi);
int				ft_is_logical(char *line);
void			ft_display_cmd(char *cmd, int pos);
void			ft_display_sp(int sp);
char			*ft_get_prev_hist(t_stack hist);
void			ft_bck_i_search(char *cmd, int pos, t_stack *hist);
void			ft_exclamation(char **comm, t_stack *hist, int *pos);
void			ft_man_search_replace(char **cmd, int *pos, t_stack hist);
char			*ft_search_replace(t_search_hist s, int i, int j, int k);
void			ft_clear_hist(t_stack *hist);
void			ft_display_bck_i_search(char *cmd, int pos, t_stack *hist, char *search);
void			ft_copy_n_paste(char **cmd, char *buf, int *pos, t_stack *hist);
int				ft_is_copy_n_paste(char *buf);
void			ft_intermidiate(char **comm, int *pos, t_stack *hist, char *buf);
void			free_list(t_env *stack);
void			ft_print_results(char **prefix, int *pos);
void			ft_autocomplete(char **str, int *pos, char **envp);
void			ft_display_list(t_list *head);
int				ft_is_cmd(char *line);
int				ft_list_size(t_list *begin_list);
t_list			*ft_search_binaries(t_list *head, char *needle);
t_list			*ft_search_system(t_list *head, char *needle);
t_list			*ft_auto_environ(t_list *head, char **envp, char *needle);
t_list			*prepend(t_list* head, char *content);
int				ft_in_array(char **av, int len, char *needle);
int				ft_str_has(char *str, char s[]);
char			*ft_get_dirname(char **needle);
int				ft_is_redirect_in_out(char **cmd);

#endif
