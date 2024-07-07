/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:44:56 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/05 13:00:57 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_loop(char *input, t_env *my_env,
			t_node	*tokens, t_ast_node *commands)
{
	int			exec_result;

	exec_result = 0;
	input = readline("Minishell > ");
	if (!input)
		ft_exit(NULL, my_env);
	if (!ft_str_is_space(input) && input[0] != ':'
		&& input[0] != '!')
	{
		add_history(input);
		tokens = tokenize_input_mem(input);
		if (!tokens)
			exec_result = 258;
		commands = parse_input(&tokens);
		if (commands)
		{
			my_env->tree = commands;
			execute_commands(commands, my_env, &exec_result);
		}
		free_ast_tree(commands);
		free(input);
	}
	update_and_display_exitcode(exec_result, my_env);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_node		*tokens;
	t_ast_node	*commands;
	t_env		*my_env;

	my_env = init_env(env);
	setup_signals();
	(void)argc;
	(void)argv;
	tokens = NULL;
	commands = NULL;
	input = NULL;
	while (1)
	{
		execution_loop(input, my_env, tokens, commands);
	}
	free_mtrxc(my_env->env);
	free(my_env);
	return (0);
}
