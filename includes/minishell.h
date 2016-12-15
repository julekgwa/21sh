/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:23:09 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:23:15 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
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
# define QUOTES ft_rm_quotes

typedef struct	s_stack
{
	int			capacity;
	int			count;
	int			top;
	char		*list[4096];
}				t_stack;

typedef struct	s_comms
{
	char		**user_comm;
	char		*get_line;
}				t_cmd;

typedef struct 	s_env
{
	char 		**list;
	int 		top;
	int 		capacity;
	int 		malloc_id;
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
int				ft_enter_and_edit_keys(char *key_pressed, int *pos, char *comm);
int				ft_navigation_keys(char *key_pressed, int *pos, char *comm);
void			ft_echo_off(char *s, struct termios *term);
char			*ft_build_comm(t_stack *hist, char *comm, char *buf, int pos);
int				ft_contains(char *str, char c);
void			ft_cursor(char *comm, int pos);
void			ft_process_buff(char **com, int pos, char c);
void			ft_create_stack(t_stack *hist);
void			ft_push(t_stack *stack, char *hist);
char			*ft_up(t_stack *stack);
char			*ft_down(t_stack *stack);
char			*ft_keys_up_down(char *key_pressed, t_stack *hist, int *pos);
int				ft_up_down(char *key_pressed);
void			ft_display_hist(t_stack hist);
void			ft_get_hist(char *history, t_stack hist);
char			*prompt(t_cmd *command, t_stack *hist);
void			ft_signalhandle(int num);
void			ft_signal(void);
void			init_main(int *ac, char ***av);
void			manage_up_down(char **buf, char **com, t_stack *hist, int *pos);
void			ft_ctrl_l(char *comm, int pos);
void			ft_run_commands(char **com, char *line, t_env *env, t_stack hi);
void			ft_pro_cmd(t_cmd *c, t_env *en, struct termios *t, t_stack *hi);
void 			free_cmd(t_cmd *cmd);
void			freecopy(char **copy);
void			ft_free_str(char *str, char *join);
void 			free_stack(t_stack *stack);
void			freesplit(char **split);
int				ft_spaces_tabs(char *s);
void			ft_builtins(char **user_comm, char *get_line, char **envp, char **sp);
void			ft_exit(char **cmd, char *get_line);
int				ft_user_dir(char *dir, char **envp);
char			**envp_cpy(char **envp);
t_env 			*copy_envp(int capacity, char **envp);
void 			free_envp(t_env *stack);
int  			ft_push_env(t_env *stack, char *value);
int 			ft_is_full(t_env *stack);
int				fork_pipes(int n, char **cmd, char **envp, int i);
int				ft_file_redirection(char **red, char **envp);
int				ft_is_redirect(char **cmd);
int				ft_arrow_pos(char **cmd);
int				ft_ctrl_b_f(char *buf);
void			ft_move_word(char *cmd, int *pos, char *buf);
int				ft_is_file_descriptor_aggr(char **cmd);
int				ft_get_file_descriptor_pos(char **cmd);
int				ft_manage_file_descriptors(char **cmd);
int				ft_get_less_than(char **cmd);
int				ft_is_less_than(char **cmd);
int				ft_get_double_less_than_pos(char **cmd);
int				ft_manage_double_less_than(char **cmd);

#endif
