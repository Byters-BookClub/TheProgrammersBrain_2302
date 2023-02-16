#ifndef BUILTIN_H
# define BUILTIN_H

int	ft_echo(t_token *command);
int	ft_export(t_token *command);
int	ft_unset(t_token *command);
int	ft_env(t_token *command);
int	ft_pwd(t_token *command);
int	ft_cd(t_token *command);
int	ft_exit(t_token *command);

#endif
