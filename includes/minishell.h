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
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct	s_stack
{
	int			capacity;
	int			size;
	int			hist_count;
	char		**list;
}				t_stack;

typedef struct	s_comms
{
	char		**user_comm;
	char		*get_line;
}				t_cmd;

void			ft_cd(char **dir, char **envp);
char			*ft_pwd();
void			ft_echo(char *av, char **envp);
int				ft_end_with(char *str, char c);
int				ft_start_with(char *str, char c);
char			*ft_first_word(const char *s);
char			*ft_last_word(const char *s);
char			*ft_get_env(const char *env, char **env_list);
void			ft_ctrl_c_signal_handler(int signum);
void			ft_print_env(char **envp);
char			**ft_check_env(char **cmd, char **envp);
int				ft_array_len(char **arr);
int				ft_unsetenv(const char *env, char **envp);
int				ft_setenv(const char *env, const char *val, int ov, char **enp);
void			ft_set_envir(char **envp, char *str);
char			*ft_remove_qoutes(char *s);
char			*ft_rm_quotes(char *s);
void			ft_print_env(char **envp);
char			**ft_check_env(char **cmd, char **envp);
void			ft_unsetting_env(char *names, char **envp);
char			*ft_build_exec(char **envp, char **split);
int				ft_is_execute(char *command);
void			ft_execute(char *cmd, char **l_cmd, char *line, char **envp);
void			ft_print_error(char *erro);
void			ft_advanced_com(char **cmd, char *line, char **envp, t_stack h);
int				ft_search_command(char *command);
void			ft_execute_commands(char **cmd, char *l, char **p, t_stack hi);
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
int				fork_pipes(int n, char **cmd, char **envp);
int				ft_contains(char *str, char c);
void			ft_cursor(char *comm, int pos);
void			ft_process_buff(char **com, int pos, char c);
void			ft_create_stack(t_stack *stack, int size);
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
void			ft_run_commands(char **com, char *line, char **env, t_stack hi);
void			ft_pro_cmd(t_cmd *c, char **en, struct termios *t, t_stack *hi);
void free_cmd(t_cmd *cmd);
void	freecopy(char **copy);
void	ft_free_str(char *str, char *join);
void free_stack(t_stack *stack);
void	freesplit(char **split);

#endif
