/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:45:13 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/07 21:23:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../mylib/ft_printf/includes/ft_printf.h"
# include "../mylib/get_next_line/includes/get_next_line.h"
# include "../mylib/libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define ANSI_COLOR_RESET "\033[0m"
# define ANSI_COLOR_GREEN "\033[0;32m"
# define ANSI_COLOR_RED "\033[0;31m"

typedef enum e_file_type{
	UNSET,
	EXECUTABLE,
	DONE,
	OUT,
	OUT_APPEND,
	IN,
	IN_APPEND,
}	t_file_type;

typedef struct s_ast_node{
	t_token_type		type;
	t_file_type			file_type;
	char				**value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env{
	char		**env;
	t_ast_node	*tree;
	int			exit_code;
}	t_env;

typedef struct s_execution_organiser{
	int	current_pipe;
	int	input_fd;
	int	output_fd;
	int	input_file_count;
	int	output_file_count;
	int	pipes_count;
	int	has_in_file;
	int	has_out_file;
	int	is_redir_pipe;
	int	heredoc;
	int	child_count;
	int	heredoc_second;
}	t_execution_organiser;

extern int	g_signal_num;

typedef struct s_ll_node
{
	char				c;
	struct s_ll_node	*next;
}	t_ll_node;

typedef struct s_env_node
{
	char				*str;
	struct s_env_node	*next;
}	t_env_node;

int			count_tokens(char *s, int *i);
t_node		*tokenize_input_mem(char *input);

char		*get_path(char *cmd, t_env *my_env);
int			check_qoutes(t_node *ll);

void		free_token_ll(t_node **ll);
void		free_ast_tree(t_ast_node *node);
void		free_mtrxc(char **m);
int			check_errors(t_node *ll);

t_ast_node	*create_ast_node(t_token_type type);
int			count_command_args(t_node *token);
void		fill_command_args(t_ast_node **command, t_node **tokens, int count);

t_ast_node	*parse_input(t_node **tokens);
t_ast_node	*create_file_node(t_node	*temp);
t_ast_node	*parse_redir(t_node	**tokens);

void		generate_ast_diagram(t_ast_node *root);
int			is_special(char *s);
int			is_redir(t_token_type type);

void		execute_commands(t_ast_node *head, t_env *my_env, int *result);
void		execute_ast(t_ast_node	*node, t_env *my_env);
void		init_organiser(t_execution_organiser *org, int reset_all);
void		init_counts(t_ast_node *head, t_execution_organiser *org);
void		init_file_types(t_ast_node	*head);
int			is_builtin_command(char **cmd);
int			execute_pipe(t_ast_node *head, t_execution_organiser *org,
				t_env *my_env, int *fd);
int			execute_redir(t_ast_node *head, t_execution_organiser *org,
				t_env *my_env, int *fd);
int			execute_command(char **cmd, t_execution_organiser *org,
				t_env *my_env, int *fd);

char		*get_file_path(char *file, t_env *my_env, char *env_var, int mode);
void		do_file_path_checks(char *path, char *file, int *failed);
int			display_file_path_errors(int failed, char *file);
char		*get_command_path(char **cmd, t_env *my_env, int mode);
void		close_pipes_helper(int fd, int fd_2);
int			wait_for_children(int failed, t_execution_organiser *org);
void		change_fds_child(t_execution_organiser *org, int *fd, int *new_fd);
void		change_fds_parent(t_execution_organiser *org, int *fd, int *new_fd);
int			open_redir_file(t_ast_node *head, t_execution_organiser *org,
				t_env *my_env, int failed);
int			here_doc(char *delim, t_execution_organiser *org, t_env *my_env);

int			do_builtin_cmd(char **input, t_env *myenv);
int			ft_cd(char **input, t_env *my_env);
int 		cd_back(t_env *myenv);
void	cd_error_display(char *dir);
void		update_current_pwd(t_env *myenv, int add_dots);
void		ft_echo(char **input);
void		ft_free_env(t_env **myenv);
t_env		*init_env(char **env);
int			ft_env(char **input, t_env *my_env);
int			ft_exit(char **input, t_env *my_env);
int			ft_export(char **input, t_env *myenv);
int			ft_pwd(t_env *env);
int			ft_unset(char **input, t_env *myenv);

int			start_builtin_execution_simple(char **cmd,
				t_execution_organiser *org, t_env *my_env, int *fd);
int			add_or_update_to_env(char *var, char *value, t_env *myenv);
void		update_and_display_exitcode(int exitcode, t_env *my_env);
int			do_builtin_cmd_parent(char **input, t_env *myenv);
int			do_command(char **cmd, t_execution_organiser *org,
				t_env *my_env, int *fd);
int			do_command_redir(char **cmd, t_execution_organiser *org,
				t_env *my_env, int *fd);

void		traverse_and_clean_tree(t_ast_node *head, t_env *my_env);

void		add_to_str(char c, t_ll_node **lst);
void		free_char_ll(t_ll_node **start);

void		setup_signals(void);
void		ctrl_c_pressed(int signal_num);
void		ctrl_c_pressed_child(int signal_number);
void		search_and_add_var(t_ll_node **lst, char *str,
				int *j, t_env *myenv);
void		do_command_helper(t_execution_organiser *org, int *new_fd,
				int *fd);
void		do_command_helper_2(char **cmd, t_env *my_env);
int			is_builtin_command_fork(char **cmd);
int			check_var_validity(char *var, char *value);

char		*remove_qoutes_str(char *str, int single_qoute_count,
				int double_qoute_count, int i);
void		get_var_heredoc(char *str, t_env *myenv, int *j, int out_f);
int			get_var_start_heredoc(char *str, int *j, int out_f);
void		sort_print_env(t_env *myenv);
int			var_exists(char	*str, t_env *myenv);

#endif